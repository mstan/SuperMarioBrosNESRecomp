#pragma once

#include "foreign_controller.h"

#include <stdint.h>

#define SMASH64_ACTION_SLOT_CAPACITY 8

typedef struct Smash64ActionSlot {
    uint32_t active;
    uint32_t instance_id;
    uint32_t kind;
    uint32_t flags;
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

int smash64_actions_snapshot(Smash64ActionSlot *out, int capacity);
