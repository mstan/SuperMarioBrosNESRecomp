#pragma once

#define ZELDA2_LINK_CONTROLLER_ID "super-mario-bros.zelda2.link"
#define ZELDA2_LINK_ACTION_SWORD_BEAM 0x5A020001u
#define ZELDA2_LINK_AUDIO_SWORD_BEAM 0x5A02A001u

typedef enum Zelda2LinkMoveState {
    ZELDA2_LINK_STAND = 200,
    ZELDA2_LINK_WALK,
    ZELDA2_LINK_CROUCH,
    ZELDA2_LINK_JUMP,
    ZELDA2_LINK_FALL,
    ZELDA2_LINK_SLASH_START,
    ZELDA2_LINK_SLASH_ACTIVE,
    ZELDA2_LINK_SLASH_RECOVER,
    ZELDA2_LINK_CROUCH_SLASH,
    ZELDA2_LINK_UPSTAB,
    ZELDA2_LINK_DOWNSTAB
} Zelda2LinkMoveState;

int zelda2_link_controller_register(void);
void zelda2_link_set_fire_power(int enabled);
int zelda2_link_fire_powered(void);
int zelda2_link_is_crouching(void);
int zelda2_link_sword_active(void);
