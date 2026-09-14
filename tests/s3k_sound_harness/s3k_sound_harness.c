/*
 * s3k_sound_harness -- render Sonic 3 & Knuckles sounds through the emulated
 * Genesis sound board, outside the game.
 *
 *   s3k_sound_harness <s3k.bin> <out.wav> [log.csv] id[@frame] ...
 *
 * Each id (hex, e.g. 62 or 62@30) is requested with Play_SFX at the given
 * frame (default 10); ids below $33 go to Play_Music. Rendering continues
 * until every track has stopped for a second, or 30 seconds. The optional
 * CSV logs each chip write as mclk,chip,port,data.
 */
#include "mods/s3k/audio/s3k_sound_board.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RATE 44100
#define SAMPLES_PER_FRAME 735

typedef struct Request { unsigned id, frame; } Request;

static FILE *s_log;

static void observe(void *user, uint64_t mclk, int chip, uint8_t port, uint8_t data)
{
    (void)user;
    if (s_log)
        fprintf(s_log, "%llu,%d,%u,%02X\n", (unsigned long long)mclk, chip,
                (unsigned)port, (unsigned)data);
}

static void put_u32(FILE *f, uint32_t v)
{
    fputc((int)(v & 0xFF), f); fputc((int)((v >> 8) & 0xFF), f);
    fputc((int)((v >> 16) & 0xFF), f); fputc((int)((v >> 24) & 0xFF), f);
}

static void put_u16(FILE *f, uint16_t v)
{
    fputc(v & 0xFF, f); fputc((v >> 8) & 0xFF, f);
}

int main(int argc, char **argv)
{
    FILE *rf, *wf;
    uint8_t *rom;
    long size;
    S3KSoundBoard *board;
    Request req[32];
    int nreq = 0, first = 3;
    int16_t *pcm;
    size_t cap = (size_t)RATE * 30, total = 0;
    unsigned frame = 0, quiet_frames = 0;

    if (argc < 4) {
        fprintf(stderr, "usage: %s rom out.wav [log.csv] id[@frame]...\n", argv[0]);
        return 2;
    }
    if (strstr(argv[3], ".csv")) {
        s_log = fopen(argv[3], "w");
        first = 4;
    }
    for (int i = first; i < argc && nreq < 32; ++i) {
        char *at = strchr(argv[i], '@');
        req[nreq].id = (unsigned)strtoul(argv[i], NULL, 16);
        req[nreq].frame = at ? (unsigned)atoi(at + 1) : 10u;
        nreq++;
    }

    rf = fopen(argv[1], "rb");
    if (!rf) { fprintf(stderr, "cannot open rom\n"); return 1; }
    fseek(rf, 0, SEEK_END);
    size = ftell(rf);
    fseek(rf, 0, SEEK_SET);
    rom = (uint8_t *)malloc((size_t)size);
    if (!rom || fread(rom, 1, (size_t)size, rf) != (size_t)size) return 1;
    fclose(rf);

    board = s3k_sound_board_create(rom, (size_t)size, RATE);
    if (!board) { fprintf(stderr, "driver not found in rom\n"); return 1; }
    s3k_sound_board_set_write_observer(board, observe, NULL);
    {
        /* S3K_RAM_DUMP=<path>: the Z80 RAM SndDrvInit leaves, for running
         * the same driver on another Z80 implementation. */
        const char *dump = getenv("S3K_RAM_DUMP");
        if (dump && *dump) {
            FILE *df = fopen(dump, "wb");
            if (df) {
                fwrite(s3k_sound_board_z80_ram(board), 1, 0x2000, df);
                fclose(df);
            }
        }
    }
    pcm = (int16_t *)calloc(cap, sizeof(*pcm));

    while (total + SAMPLES_PER_FRAME <= cap) {
        int pending = 0;
        for (int i = 0; i < nreq; ++i) {
            if (req[i].frame == frame) {
                if (req[i].id < 0x33) s3k_sound_board_play_music(board, (uint8_t)req[i].id);
                else s3k_sound_board_play_sfx(board, (uint8_t)req[i].id);
            }
            if (req[i].frame >= frame) pending = 1;
        }
        s3k_sound_board_render(board, pcm + total, SAMPLES_PER_FRAME);
        total += SAMPLES_PER_FRAME;
        frame++;
        if (!pending && !s3k_sound_board_busy(board)) {
            if (++quiet_frames >= 60) break;
        } else {
            quiet_frames = 0;
        }
    }

    wf = fopen(argv[2], "wb");
    if (!wf) return 1;
    fwrite("RIFF", 1, 4, wf); put_u32(wf, (uint32_t)(36 + total * 2));
    fwrite("WAVEfmt ", 1, 8, wf); put_u32(wf, 16); put_u16(wf, 1); put_u16(wf, 1);
    put_u32(wf, RATE); put_u32(wf, RATE * 2); put_u16(wf, 2); put_u16(wf, 16);
    fwrite("data", 1, 4, wf); put_u32(wf, (uint32_t)(total * 2));
    fwrite(pcm, sizeof(int16_t), total, wf);
    fclose(wf);
    if (s_log) fclose(s_log);
    {
        long peak = 0;
        double sum = 0.0;
        for (size_t i = 0; i < total; ++i) {
            long v = labs((long)pcm[i]);
            if (v > peak) peak = v;
            sum += (double)pcm[i] * pcm[i];
        }
        printf("frames=%u samples=%zu peak=%ld rms=%.1f\n", frame, total, peak,
               total ? sqrt(sum / (double)total) : 0.0);
    }
    s3k_sound_board_destroy(board);
    free(pcm);
    free(rom);
    return 0;
}
