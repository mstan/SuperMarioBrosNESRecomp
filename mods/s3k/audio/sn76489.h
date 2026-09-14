/*
 * sn76489.h -- the Sega variant of the TI SN76489 PSG in the Genesis.
 *
 * Three 10-bit square-wave tone channels and a noise channel with a 16-bit
 * shift register tapped at bits 0 and 3. The host clocks sn76489_clock() once
 * per PSG input clock (the Z80 clock on the Genesis); the chip divides that by
 * 16 internally. Output is unipolar, as the chip's is: each channel is 0 or
 * its volume, 2 dB per attenuation step with 15 silent, averaged over the four.
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SN76489 {
    uint16_t tone[3];
    uint16_t counter[3];
    uint8_t  square_high[3];
    uint8_t  attenuation[4];
    uint8_t  noise_control;    /* bit 2 white noise, bits 1-0 shift rate */
    uint16_t noise_counter;
    uint8_t  noise_divider_high;
    uint16_t lfsr;
    uint8_t  noise_out;        /* last bit shifted out of the register */
    uint8_t  latched;         /* register 0-7 selected by the last latch byte */
    uint8_t  divider;
} SN76489;

void sn76489_reset(SN76489 *psg);
void sn76489_write(SN76489 *psg, uint8_t value);

/* Advance the internal /16 divider by one input clock; the channels step when
 * it wraps. */
void sn76489_clock_internal(SN76489 *psg);

/* Advance straight to the next internal step (16 input clocks). */
void sn76489_step(SN76489 *psg);

/* Current output in [0, 1]. */
double sn76489_output(const SN76489 *psg);

#ifdef __cplusplus
}
#endif
