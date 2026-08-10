#pragma once

#define SMASH64_PIKACHU_ID "super-mario-bros.smash64.pikachu"

#include "../ssb_ported/pikachu_locomotion.h"

/* Registers the generic controller and its versioned private state callbacks. */
int smash64_pikachu_register(void);
/* Controller-local event/projectile interface until the SMB host ABI consumes it. */
const PikachuMotion *smash64_pikachu_last_motion(void);
void smash64_pikachu_thunder_self_contact(void);
