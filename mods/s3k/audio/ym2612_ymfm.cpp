/* ym2612_ymfm.cpp -- see ym2612.h. */
#include "ym2612.h"

#include "third_party/ymfm/ymfm_opn.h"

#include <new>

struct GenesisYM2612 {
    ymfm::ymfm_interface intf;
    ymfm::ym2612 chip;

    GenesisYM2612() : chip(intf) {}
};

extern "C" GenesisYM2612 *genesis_ym2612_create(void)
{
    GenesisYM2612 *ym = new (std::nothrow) GenesisYM2612();
    if (ym) ym->chip.reset();
    return ym;
}

extern "C" void genesis_ym2612_destroy(GenesisYM2612 *ym)
{
    delete ym;
}

extern "C" void genesis_ym2612_reset(GenesisYM2612 *ym)
{
    if (ym) ym->chip.reset();
}

extern "C" void genesis_ym2612_write(GenesisYM2612 *ym, uint8_t port, uint8_t data)
{
    if (ym) ym->chip.write(port & 3u, data);
}

extern "C" uint8_t genesis_ym2612_read_status(GenesisYM2612 *ym)
{
    return ym ? ym->chip.read_status() : 0;
}

extern "C" void genesis_ym2612_generate(GenesisYM2612 *ym, int32_t *left,
                                        int32_t *right)
{
    ymfm::ym2612::output_data out;
    if (!ym) {
        *left = *right = 0;
        return;
    }
    ym->chip.generate(&out, 1);
    *left = out.data[0];
    *right = out.data[1];
}
