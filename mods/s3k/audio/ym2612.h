/*
 * ym2612.h -- C interface to ymfm's YM2612 (OPN2) for the Genesis sound board.
 *
 * ymfm (third_party/ymfm, BSD-3-Clause) models the chip, including its 9-bit
 * DAC discontinuity. One generated sample corresponds to 144 chip clocks
 * (the NTSC Genesis runs it at master clock / 7, so 53267 Hz).
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GenesisYM2612 GenesisYM2612;

GenesisYM2612 *genesis_ym2612_create(void);
void genesis_ym2612_destroy(GenesisYM2612 *chip);
void genesis_ym2612_reset(GenesisYM2612 *chip);
/* port 0/1 = part I address/data, 2/3 = part II address/data. */
void genesis_ym2612_write(GenesisYM2612 *chip, uint8_t port, uint8_t data);
uint8_t genesis_ym2612_read_status(GenesisYM2612 *chip);
/* Generate one sample; outputs are roughly signed 16-bit full scale. */
void genesis_ym2612_generate(GenesisYM2612 *chip, int32_t *left, int32_t *right);

#ifdef __cplusplus
}
#endif
