#ifndef GAME_SMASH64_ATTACK_POLICY_H
#define GAME_SMASH64_ATTACK_POLICY_H

#include <stdint.h>

/* SMB1 object/type IDs from symbols.sym. Keep this policy independent of the
 * generated runtime header so the adapter's target boundary can be exercised
 * by the standalone Falcon harness. */
enum {
    SMASH64_ENEMY_BULLET_BILL_FRENZY = 0x08,
    SMASH64_ENEMY_PODOBOO = 0x0C,
    SMASH64_ENEMY_FIRST_SPECIAL = 0x15
};

static inline int smash64_enemy_accepts_attack(uint8_t id, uint8_t state)
{
    if (state & 0x20) return 0; /* ShellOrBlockDefeat's defeated bit. */
    if (id == SMASH64_ENEMY_BULLET_BILL_FRENZY ||
        id == SMASH64_ENEMY_PODOBOO)
        return 0;
    /* Mirrors ChkOtherEnemies ($D78B): special objects and Bowser live at or
     * above $15 and retain their native interaction rules. */
    return id < SMASH64_ENEMY_FIRST_SPECIAL;
}

#endif
