/* s3k_sound_board.c -- see s3k_sound_board.h. */
#include "s3k_sound_board.h"

#include "sn76489.h"
#include "ym2612.h"
#include "z80.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NTSC_MCLK       53693175ull
#define MCLK_PER_Z80    15u
#define MCLK_PER_PSG    240u      /* MCLK/15 input clock, /16 inside the PSG */
#define MCLK_PER_YM     1008u     /* MCLK/7 chip clock, 144 clocks a sample  */
#define MCLK_PER_FRAME  896040ull /* 262 lines of 3420 MCLK                  */
/* The VDP holds the Z80's /INT for about one line from the start of V-blank. */
#define MCLK_INT_HOLD   3420u

/* SndDrvInit's Kos_Decomp sources in the verified lock-on image. */
#define S3K_Z80_DRIVER_OFF       0x0F6960u   /* Z80_SoundDriver     */
#define S3K_Z80_DRIVER_DATA_OFF  0x0F7760u   /* Z80_SoundDriverData */
#define Z80_DRIVER_DATA_ADDR     0x1300u     /* z80_SoundDriverPointers */

/* Z80 RAM variables of the S&K driver (zDataStart $1C00). */
#define Z80_MUSIC_NUMBER   0x1C0Au
#define Z80_SFX_NUMBER0    0x1C0Bu
#define Z80_SFX_NUMBER1    0x1C0Cu
#define Z80_TRACKS_START   0x1C40u   /* 9 song tracks, then 7 SFX tracks */
#define Z80_TRACK_LEN      0x30u
#define Z80_TRACK_COUNT    16u

/* jgenesis-equivalent mixing: the YM2612 at full scale, the PSG 7 dB below,
 * both through the Model 1 VA2 low-pass. OUTPUT_GAIN sets the Genesis mix
 * against SMB1's NES audio: a full-volume PSG square lands near a full-volume
 * NES pulse. */
#define LOWPASS_HZ   3390.0
#define DC_BLOCK_HZ  5.0
#define PSG_LEVEL    0.44668359215096315
#define OUTPUT_GAIN  1.5
/* The YM2612's DAC offset steps in at power-on; run this long silently so the
 * DC blocker has settled before anything is heard. */
#define PREROLL_FRAMES 30

#define WRITE_LOG_CAP 16384u
#define FIFO_CAP      16384u

typedef struct ChipWrite {
    uint64_t mclk;
    uint8_t chip;
    uint8_t port;
    uint8_t data;
} ChipWrite;

typedef struct OnePole {
    double b0, b1, a1;
    double x1, y1;
} OnePole;

typedef struct DcBlock {
    double r;
    double x1, y1;
} DcBlock;

struct S3KSoundBoard {
    const uint8_t *rom;
    size_t rom_size;
    int rate;
    int loaded;

    Z80 cpu;
    uint8_t ram[0x2000];
    uint16_t bank;          /* 9-bit window register: 68k address bank << 15 */
    GenesisYM2612 *ym;
    SN76489 psg;

    uint64_t frame_start;   /* MCLK */
    ChipWrite writes[WRITE_LOG_CAP];
    unsigned write_count;

    uint64_t ym_next, psg_next;
    uint64_t out_index;
    uint64_t out_origin;
    double ym_prev, ym_cur;
    uint64_t ym_cur_time;
    double psg_sum, psg_last;
    unsigned psg_n;
    OnePole ym_lp_l, ym_lp_r, psg_lp;
    DcBlock ym_dc_l, ym_dc_r, psg_dc;

    int16_t fifo[FIFO_CAP];
    unsigned fifo_head, fifo_count;

    S3KSoundWriteFn observer;
    void *observer_user;
};

/* ------------------------------------------------------------ Kosinski */

/* Kos_Decomp. Returns the decompressed size, or -1 on overrun. */
static long kosinski_decompress(const uint8_t *src, size_t avail,
                                uint8_t *dst, size_t cap)
{
    size_t p = 0, out = 0;
    unsigned desc, bits;

#define KOS_BYTE() (p < avail ? src[p++] : 0)
#define KOS_BIT(v) do {                                         \
        (v) = desc & 1u;                                        \
        desc >>= 1;                                             \
        if (--bits == 0) {                                      \
            desc = KOS_BYTE();                                  \
            desc |= (unsigned)KOS_BYTE() << 8;                  \
            bits = 16;                                          \
        }                                                       \
    } while (0)

    desc = KOS_BYTE();
    desc |= (unsigned)KOS_BYTE() << 8;
    bits = 16;
    for (;;) {
        unsigned bit, count;
        long offset;

        if (p >= avail) return -1;
        KOS_BIT(bit);
        if (bit) {
            if (out >= cap) return -1;
            dst[out++] = KOS_BYTE();
            continue;
        }
        KOS_BIT(bit);
        if (bit) {
            const unsigned lo = KOS_BYTE();
            const unsigned hi = KOS_BYTE();
            offset = (long)(((hi & 0xF8u) << 5) | lo) - 0x2000;
            count = hi & 7u;
            if (count == 0) {
                const unsigned c = KOS_BYTE();
                if (c == 0) break;
                if (c == 1) continue;
                count = c + 1u;
            } else {
                count += 2u;
            }
        } else {
            unsigned b1, b2;
            KOS_BIT(b1);
            KOS_BIT(b2);
            count = ((b1 << 1) | b2) + 2u;
            offset = (long)KOS_BYTE() - 0x100;
        }
        for (unsigned i = 0; i < count; ++i) {
            if (out >= cap || (long)out + offset < 0) return -1;
            dst[out] = dst[(long)out + offset];
            out++;
        }
    }
#undef KOS_BIT
#undef KOS_BYTE
    return (long)out;
}

/* ------------------------------------------------------------- filters */

static void one_pole_lowpass(OnePole *f, double cutoff, double rate)
{
    const double k = tan(3.141592653589793 * cutoff / rate);
    f->b0 = k / (1.0 + k);
    f->b1 = f->b0;
    f->a1 = (k - 1.0) / (k + 1.0);
    f->x1 = f->y1 = 0.0;
}

static double one_pole_run(OnePole *f, double x)
{
    const double y = f->b0 * x + f->b1 * f->x1 - f->a1 * f->y1;
    f->x1 = x;
    f->y1 = y;
    return y;
}

static void dc_block_init(DcBlock *f, double cutoff, double rate)
{
    f->r = exp(-2.0 * 3.141592653589793 * cutoff / rate);
    f->x1 = f->y1 = 0.0;
}

static double dc_block_run(DcBlock *f, double x)
{
    const double y = x - f->x1 + f->r * f->y1;
    f->x1 = x;
    f->y1 = y;
    return y;
}

/* ------------------------------------------------------------ Z80 bus */

static uint64_t z80_now(const S3KSoundBoard *b)
{
    return b->cpu.cycles * MCLK_PER_Z80;
}

static void log_write(S3KSoundBoard *b, uint8_t chip, uint8_t port, uint8_t data)
{
    const uint64_t now = z80_now(b);
    if (b->observer) b->observer(b->observer_user, now, chip, port, data);
    if (b->write_count < WRITE_LOG_CAP) {
        ChipWrite *w = &b->writes[b->write_count++];
        w->mclk = now;
        w->chip = chip;
        w->port = port;
        w->data = data;
    }
}

static uint8_t bus_read(void *user, uint16_t addr)
{
    S3KSoundBoard *b = (S3KSoundBoard *)user;
    if (addr < 0x4000) return b->ram[addr & 0x1FFF];
    if (addr < 0x6000) return genesis_ym2612_read_status(b->ym);
    if (addr >= 0x8000) {
        const size_t m68k = ((size_t)b->bank << 15) | (addr & 0x7FFFu);
        return m68k < b->rom_size ? b->rom[m68k] : 0xFF;
    }
    return 0xFF;
}

static void bus_write(void *user, uint16_t addr, uint8_t v)
{
    S3KSoundBoard *b = (S3KSoundBoard *)user;
    if (addr < 0x4000) {
        b->ram[addr & 0x1FFF] = v;
    } else if (addr < 0x6000) {
        log_write(b, 0, (uint8_t)(addr & 3u), v);
    } else if (addr < 0x6100) {
        /* Each write shifts bit 0 into the top of the 9-bit bank register. */
        b->bank = (uint16_t)(((b->bank >> 1) | ((v & 1u) << 8)) & 0x1FFu);
    } else if (addr >= 0x7F10 && addr < 0x7F18 && (addr & 1u)) {
        log_write(b, 1, 0, v);
    }
    /* Writes into the 68000 window land on ROM and are ignored. */
}

/* ------------------------------------------------------------- render */

static void apply_write(S3KSoundBoard *b, const ChipWrite *w)
{
    if (w->chip == 0) genesis_ym2612_write(b->ym, w->port, w->data);
    else sn76489_write(&b->psg, w->data);
}

static void fifo_push(S3KSoundBoard *b, int16_t s)
{
    if (b->fifo_count == FIFO_CAP) {
        b->fifo_head = (b->fifo_head + 1u) % FIFO_CAP;
        b->fifo_count--;
    }
    b->fifo[(b->fifo_head + b->fifo_count) % FIFO_CAP] = s;
    b->fifo_count++;
}

static uint64_t out_time(const S3KSoundBoard *b, uint64_t index)
{
    return b->out_origin + index * NTSC_MCLK / (uint64_t)b->rate;
}

/* Clock both chips and emit output samples up to (not including) `until`. */
static void render_until(S3KSoundBoard *b, uint64_t until)
{
    unsigned wi = 0;

    for (;;) {
        const uint64_t t_out = out_time(b, b->out_index);
        uint64_t t = b->ym_next;
        if (b->psg_next < t) t = b->psg_next;
        if (t_out < t) t = t_out;
        if (t >= until) break;

        while (wi < b->write_count && b->writes[wi].mclk <= t)
            apply_write(b, &b->writes[wi++]);

        if (t == b->ym_next) {
            int32_t l, r;
            genesis_ym2612_generate(b->ym, &l, &r);
            b->ym_prev = b->ym_cur;
            b->ym_cur = 0.5 * (one_pole_run(&b->ym_lp_l,
                                            dc_block_run(&b->ym_dc_l, l / 32768.0)) +
                               one_pole_run(&b->ym_lp_r,
                                            dc_block_run(&b->ym_dc_r, r / 32768.0)));
            b->ym_cur_time = t;
            b->ym_next += MCLK_PER_YM;
        }
        if (t == b->psg_next) {
            double v;
            sn76489_step(&b->psg);
            v = one_pole_run(&b->psg_lp,
                             dc_block_run(&b->psg_dc, sn76489_output(&b->psg)));
            b->psg_sum += v;
            b->psg_n++;
            b->psg_next += MCLK_PER_PSG;
        }
        if (t == t_out) {
            /* The YM2612 is interpolated one of its samples behind; the PSG,
             * clocked four times faster than the output, is box-averaged over
             * the output interval. */
            const double alpha = (double)(t - b->ym_cur_time) / MCLK_PER_YM;
            const double ym = b->ym_prev + (b->ym_cur - b->ym_prev) * alpha;
            double psg, mix;
            if (b->psg_n) {
                b->psg_last = b->psg_sum / b->psg_n;
                b->psg_sum = 0.0;
                b->psg_n = 0;
            }
            psg = b->psg_last;
            mix = (ym + psg * PSG_LEVEL) * OUTPUT_GAIN * 32767.0;
            if (mix > 32767.0) mix = 32767.0;
            if (mix < -32768.0) mix = -32768.0;
            fifo_push(b, (int16_t)lrint(mix));
            b->out_index++;
        }
    }
    while (wi < b->write_count) apply_write(b, &b->writes[wi++]);
    b->write_count = 0;
}

static void run_frame(S3KSoundBoard *b)
{
    const uint64_t frame_end = b->frame_start + MCLK_PER_FRAME;
    const uint64_t int_end = b->frame_start + MCLK_INT_HOLD;

    b->cpu.int_line = 1;
    while (z80_now(b) < frame_end) {
        const uint8_t iff_before = b->cpu.iff1;
        if (b->cpu.int_line && z80_now(b) >= int_end) b->cpu.int_line = 0;
        z80_step(&b->cpu);
        if (b->cpu.int_line && iff_before && !b->cpu.iff1 && b->cpu.pc == 0x0038)
            b->cpu.int_line = 0;   /* acknowledged */
    }
    b->cpu.int_line = 0;
    render_until(b, frame_end);
    b->frame_start = frame_end;
}

/* ----------------------------------------------------------------- API */

S3KSoundBoard *s3k_sound_board_create(const uint8_t *rom, size_t rom_size,
                                      int output_rate)
{
    S3KSoundBoard *b;
    if (!rom || output_rate <= 0) return NULL;
    b = (S3KSoundBoard *)calloc(1, sizeof(*b));
    if (!b) return NULL;
    b->rom = rom;
    b->rom_size = rom_size;
    b->rate = output_rate;
    b->ym = genesis_ym2612_create();
    if (!b->ym) {
        free(b);
        return NULL;
    }
    if (!s3k_sound_board_reset(b)) {
        s3k_sound_board_destroy(b);
        return NULL;
    }
    return b;
}

void s3k_sound_board_destroy(S3KSoundBoard *b)
{
    if (!b) return;
    genesis_ym2612_destroy(b->ym);
    free(b);
}

int s3k_sound_board_reset(S3KSoundBoard *b)
{
    long driver_len, data_len;
    const double ym_rate = (double)NTSC_MCLK / MCLK_PER_YM;
    const double psg_rate = (double)NTSC_MCLK / MCLK_PER_PSG;

    if (!b) return 0;
    b->loaded = 0;
    memset(b->ram, 0, sizeof(b->ram));
    if (b->rom_size <= S3K_Z80_DRIVER_DATA_OFF) return 0;
    driver_len = kosinski_decompress(b->rom + S3K_Z80_DRIVER_OFF,
                                     b->rom_size - S3K_Z80_DRIVER_OFF,
                                     b->ram, Z80_DRIVER_DATA_ADDR);
    data_len = kosinski_decompress(b->rom + S3K_Z80_DRIVER_DATA_OFF,
                                   b->rom_size - S3K_Z80_DRIVER_DATA_OFF,
                                   b->ram + Z80_DRIVER_DATA_ADDR,
                                   0x1C00u - Z80_DRIVER_DATA_ADDR);
    /* The driver begins di / di / im 1 / jp zInitAudioDriver. */
    if (driver_len <= 0 || data_len <= 0 ||
        memcmp(b->ram, "\xF3\xF3\xED\x56\xC3", 5) != 0)
        return 0;
    /* Z80_DefaultVariables are all zero; NTSC leaves zPalFlag clear. */

    memset(&b->cpu, 0, sizeof(b->cpu));
    b->cpu.user = b;
    b->cpu.read = bus_read;
    b->cpu.write = bus_write;
    z80_reset(&b->cpu);
    b->bank = 0;
    genesis_ym2612_reset(b->ym);
    sn76489_reset(&b->psg);

    b->frame_start = 0;
    b->write_count = 0;
    b->ym_next = 0;
    b->psg_next = 0;
    b->out_index = 0;
    b->out_origin = 0;
    b->ym_prev = b->ym_cur = 0.0;
    b->ym_cur_time = 0;
    b->psg_sum = b->psg_last = 0.0;
    b->psg_n = 0;
    one_pole_lowpass(&b->ym_lp_l, LOWPASS_HZ, ym_rate);
    one_pole_lowpass(&b->ym_lp_r, LOWPASS_HZ, ym_rate);
    one_pole_lowpass(&b->psg_lp, LOWPASS_HZ, psg_rate);
    dc_block_init(&b->ym_dc_l, DC_BLOCK_HZ, ym_rate);
    dc_block_init(&b->ym_dc_r, DC_BLOCK_HZ, ym_rate);
    dc_block_init(&b->psg_dc, DC_BLOCK_HZ, psg_rate);
    b->fifo_head = b->fifo_count = 0;
    b->loaded = 1;
    for (int i = 0; i < PREROLL_FRAMES; ++i) run_frame(b);
    b->fifo_head = b->fifo_count = 0;
    return 1;
}

void s3k_sound_board_play_sfx(S3KSoundBoard *b, uint8_t id)
{
    uint8_t *slot0, *slot1;
    if (!b || !b->loaded || !id) return;
    slot0 = &b->ram[Z80_SFX_NUMBER0];
    slot1 = &b->ram[Z80_SFX_NUMBER1];
    /* Play_SFX: a repeat of slot 0 is dropped, an empty slot 0 is filled,
     * otherwise slot 1 takes (and replaces) the request. */
    if (*slot0 == id) return;
    if (*slot0 == 0) *slot0 = id;
    else *slot1 = id;
}

void s3k_sound_board_play_music(S3KSoundBoard *b, uint8_t id)
{
    if (!b || !b->loaded) return;
    b->ram[Z80_MUSIC_NUMBER] = id;
}

void s3k_sound_board_render(S3KSoundBoard *b, int16_t *out, int count)
{
    int i = 0;
    if (!out || count <= 0) return;
    if (!b || !b->loaded) {
        memset(out, 0, (size_t)count * sizeof(*out));
        return;
    }
    while (b->fifo_count < (unsigned)count) {
        const unsigned before = b->fifo_count;
        run_frame(b);
        if (b->fifo_count == before && b->fifo_count == FIFO_CAP) break;
    }
    for (; i < count && b->fifo_count; ++i) {
        out[i] = b->fifo[b->fifo_head];
        b->fifo_head = (b->fifo_head + 1u) % FIFO_CAP;
        b->fifo_count--;
    }
    for (; i < count; ++i) out[i] = 0;
}

int s3k_sound_board_busy(const S3KSoundBoard *b)
{
    if (!b || !b->loaded) return 0;
    for (unsigned t = 0; t < Z80_TRACK_COUNT; ++t)
        if (b->ram[Z80_TRACKS_START + t * Z80_TRACK_LEN] & 0x80) return 1;
    return 0;
}

void s3k_sound_board_set_write_observer(S3KSoundBoard *b, S3KSoundWriteFn fn,
                                        void *user)
{
    if (!b) return;
    b->observer = fn;
    b->observer_user = user;
}

const uint8_t *s3k_sound_board_z80_ram(const S3KSoundBoard *b)
{
    return b ? b->ram : NULL;
}
