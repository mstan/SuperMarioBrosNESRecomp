#pragma once

#define METROID_SAMUS_CONTROLLER_ID "super-mario-bros.metroid.samus"

typedef enum MetroidSamusMoveState {
    METROID_SAMUS_STAND = 100,
    METROID_SAMUS_RUN,
    METROID_SAMUS_JUMP,
    METROID_SAMUS_SPIN,
    METROID_SAMUS_MORPH,
    METROID_SAMUS_ROLL,
    METROID_SAMUS_HURT
} MetroidSamusMoveState;

int metroid_samus_controller_register(void);
int metroid_samus_is_morphed(void);
int metroid_samus_is_spinning(void);
void metroid_samus_force_morph(void);
void metroid_samus_bomb_jump(void);
