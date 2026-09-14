/* sn76489.c -- see sn76489.h. */
#include "sn76489.h"

#include <math.h>

#define LFSR_SEED 0x8000u

void sn76489_reset(SN76489 *psg)
{
    for (int i = 0; i < 3; ++i) {
        psg->tone[i] = 0;
        psg->counter[i] = 1;
        psg->square_high[i] = 0;
    }
    for (int i = 0; i < 4; ++i) psg->attenuation[i] = 0x0F;
    psg->noise_control = 0;
    psg->noise_counter = 0;
    psg->noise_divider_high = 0;
    psg->lfsr = LFSR_SEED;
    psg->noise_out = 0;
    psg->latched = 0;
    psg->divider = 16;
}

void sn76489_write(SN76489 *psg, uint8_t value)
{
    uint8_t reg;
    if (value & 0x80) {
        psg->latched = (uint8_t)((value >> 4) & 7);
        reg = psg->latched;
        /* A latch byte carries the low four data bits. */
        if (reg & 1) {
            psg->attenuation[reg >> 1] = (uint8_t)(value & 0x0F);
        } else if (reg == 6) {
            psg->noise_control = (uint8_t)(value & 0x07);
            psg->lfsr = LFSR_SEED;
        } else {
            psg->tone[reg >> 1] =
                (uint16_t)((psg->tone[reg >> 1] & 0x3F0u) | (value & 0x0Fu));
        }
        return;
    }
    /* A data byte: the high six tone bits, or the low bits of the other
     * registers again. */
    reg = psg->latched;
    if (reg & 1) {
        psg->attenuation[reg >> 1] = (uint8_t)(value & 0x0F);
    } else if (reg == 6) {
        psg->noise_control = (uint8_t)(value & 0x07);
        psg->lfsr = LFSR_SEED;
    } else {
        psg->tone[reg >> 1] =
            (uint16_t)((psg->tone[reg >> 1] & 0x00Fu) | ((value & 0x3Fu) << 4));
    }
}

void sn76489_step(SN76489 *psg)
{
    for (int i = 0; i < 3; ++i) {
        if (--psg->counter[i] == 0) {
            /* A tone of 0 reloads as 1. */
            psg->counter[i] = psg->tone[i] ? psg->tone[i] : 1;
            psg->square_high[i] ^= 1;
        }
    }
    if (psg->noise_counter) psg->noise_counter--;
    if (psg->noise_counter == 0) {
        static const uint16_t k_rates[3] = { 0x10, 0x20, 0x40 };
        const uint8_t rate = psg->noise_control & 3;
        psg->noise_counter = rate == 3 ? psg->tone[2] : k_rates[rate];
        psg->noise_divider_high ^= 1;
        if (psg->noise_divider_high) {
            /* The channel outputs the bit shifted out of position 0. */
            psg->noise_out = (uint8_t)(psg->lfsr & 1u);
            const uint16_t feedback = (psg->noise_control & 0x04)
                ? (uint16_t)((psg->lfsr ^ (psg->lfsr >> 3)) & 1u)
                : (uint16_t)(psg->lfsr & 1u);
            psg->lfsr = (uint16_t)((psg->lfsr >> 1) | (feedback << 15));
        }
    }
}

void sn76489_clock_internal(SN76489 *psg)
{
    if (--psg->divider == 0) {
        psg->divider = 16;
        sn76489_step(psg);
    }
}

double sn76489_output(const SN76489 *psg)
{
    static double k_volume[16];
    static int k_ready;
    double sum = 0.0;

    if (!k_ready) {
        for (int i = 0; i < 15; ++i) k_volume[i] = pow(10.0, -0.1 * i);
        k_volume[15] = 0.0;
        k_ready = 1;
    }
    for (int i = 0; i < 3; ++i)
        if (psg->square_high[i]) sum += k_volume[psg->attenuation[i]];
    if (psg->noise_out) sum += k_volume[psg->attenuation[3]];
    return sum / 4.0;
}
