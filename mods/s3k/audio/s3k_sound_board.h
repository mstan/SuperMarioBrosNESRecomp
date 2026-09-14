/*
 * s3k_sound_board.h -- the Genesis sound hardware running Sonic 3 & Knuckles'
 * own sound driver.
 *
 * Nothing about S3K's sounds is re-authored here. At reset the board does
 * what SndDrvInit does on a real console: Kosinski-decompress the Z80 SMPS
 * driver and its data tables out of the owner ROM into Z80 RAM and start the
 * Z80. Every NTSC frame the VDP's V-int drives the driver, which reads the
 * sound data through the Z80's 68000 bank window and programs the YM2612
 * (ymfm) and the SN76489 PSG. A request is exactly Play_SFX / Play_Music:
 * a byte in the driver's M68K input variables.
 *
 * Time is kept in master-clock units (NTSC MCLK 53693175 Hz), in which every
 * Genesis clock is an integer: Z80 cycle 15, PSG step 240, YM2612 sample 1008,
 * frame 896040 (262 lines x 3420). Output is mono at the requested rate after
 * the Model 1 VA2 3390 Hz low-pass and DC removal.
 */
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct S3KSoundBoard S3KSoundBoard;

/* Chip write observer, for diagnostics: chip 0 = YM2612 (port 0-3), 1 = PSG. */
typedef void (*S3KSoundWriteFn)(void *user, uint64_t mclk, int chip,
                                uint8_t port, uint8_t data);

/* `rom` is the verified S3&K lock-on image and must outlive the board. */
S3KSoundBoard *s3k_sound_board_create(const uint8_t *rom, size_t rom_size,
                                      int output_rate);
void s3k_sound_board_destroy(S3KSoundBoard *board);

/* SndDrvInit: reload the driver, reset the chips and silence the output.
 * Returns 0 if the ROM does not hold the expected driver. */
int s3k_sound_board_reset(S3KSoundBoard *board);

/* Play_SFX / Play_Music. */
void s3k_sound_board_play_sfx(S3KSoundBoard *board, uint8_t id);
void s3k_sound_board_play_music(S3KSoundBoard *board, uint8_t id);

/* Produce `count` mono samples, running Genesis frames as needed. */
void s3k_sound_board_render(S3KSoundBoard *board, int16_t *out, int count);

/* True while any SFX or music track is playing. */
int s3k_sound_board_busy(const S3KSoundBoard *board);

void s3k_sound_board_set_write_observer(S3KSoundBoard *board,
                                        S3KSoundWriteFn fn, void *user);

/* Z80 RAM, for diagnostics. */
const uint8_t *s3k_sound_board_z80_ram(const S3KSoundBoard *board);

#ifdef __cplusplus
}
#endif
