#pragma once

#include "foreign_controller.h"

#include <stdint.h>

#define SMASH64_ACTION_SLOT_CAPACITY 8
/* Version 3 compact record: 4-byte header, eight 56-byte active slots, and
 * four 8-byte feedback events. This stays below the mod hook's 512-byte
 * payload ceiling without enlarging that engine-wide safety bound. */
#define SMASH64_ACTION_SERIALIZED_MAX 484

typedef enum Smash64ActionSurfaceNormal {
    SMASH64_ACTION_SURFACE_NONE = 0,
    SMASH64_ACTION_SURFACE_DOWN = 1,
    SMASH64_ACTION_SURFACE_RIGHT = 2,
    SMASH64_ACTION_SURFACE_UP = 3,
    SMASH64_ACTION_SURFACE_LEFT = 4,
} Smash64ActionSurfaceNormal;

typedef struct Smash64ActionSlot {
    uint32_t active;
    uint32_t instance_id;
    uint32_t kind;
    uint32_t flags;
    uint32_t surface_normal;
    double x;
    double y;
    double vx;
    double vy;
    double width;
    double height;
    int32_t damage;
    uint32_t age;
    uint32_t lifetime;
    uint32_t target_consumed;
} Smash64ActionSlot;

typedef struct Smash64ActionSave {
    Smash64ActionSlot slots[SMASH64_ACTION_SLOT_CAPACITY];
    ForeignActionFeedback feedback_pending;
} Smash64ActionSave;

typedef struct Smash64ActionHost {
    int (*solid_at)(double world_x, double screen_y);
    int (*defeat_target)(double left, double right,
                         double top, double bottom);
    double fighter_left;
    double fighter_right;
    double fighter_top;
    double fighter_bottom;
} Smash64ActionHost;

void smash64_actions_clear(void);
void smash64_actions_apply_commands(const ForeignActionEvents *events,
                                    double fighter_world_x,
                                    double fighter_foot_y,
                                    double facing,
                                    double units_to_px);
void smash64_actions_step(const Smash64ActionHost *host);
void smash64_actions_drain_feedback(ForeignActionFeedback *out);

void smash64_actions_save(Smash64ActionSave *out);
int smash64_actions_restore(const Smash64ActionSave *saved);
int smash64_actions_serialize(uint8_t *buf, int capacity);
int smash64_actions_deserialize(const uint8_t *buf, int length);

int smash64_actions_snapshot(Smash64ActionSlot *out, int capacity);

/* True when an action of this opaque controller-defined kind is alive. Hosts
 * use this for presentation that must follow a serialized action's actual
 * lifetime (for example, a looping projectile sound), rather than the
 * one-tick spawn notification. */
int smash64_actions_has_active_kind(uint32_t kind);
