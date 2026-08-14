#pragma once

#define S3K_SONIC_CONTROLLER_ID "super-mario-bros.s3k.sonic"

#define S3K_SONIC_AUDIO_JUMP        0x53334B01u
#define S3K_SONIC_AUDIO_ROLL        0x53334B02u
#define S3K_SONIC_AUDIO_SPINDASH    0x53334B03u
#define S3K_SONIC_AUDIO_DASH        0x53334B04u
#define S3K_SONIC_AUDIO_FIRE_DASH   0x53334B05u

typedef enum S3KSonicMoveState {
    S3K_SONIC_STAND = 300,
    S3K_SONIC_WALK,
    S3K_SONIC_RUN,
    S3K_SONIC_SKID,
    S3K_SONIC_CROUCH,
    S3K_SONIC_SPINDASH,
    S3K_SONIC_ROLL,
    S3K_SONIC_JUMP,
    S3K_SONIC_FALL,
    S3K_SONIC_FIRE_DASH
} S3KSonicMoveState;

int s3k_sonic_controller_register(void);
int s3k_sonic_is_ball(void);
int s3k_sonic_breaks_side_blocks(void);
int s3k_sonic_is_crouching(void);
int s3k_sonic_has_fire_shield(void);
void s3k_sonic_set_fire_shield(int enabled);
unsigned s3k_sonic_anim_frame(void);
