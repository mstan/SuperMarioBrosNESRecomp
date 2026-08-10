#include "game_smash64_actions.h"

#include <math.h>
#include <string.h>

static Smash64ActionSlot s_slots[SMASH64_ACTION_SLOT_CAPACITY];
static ForeignActionFeedback s_feedback_pending;

static int overlap(double a0, double a1, double b0, double b1)
{
    return a0 < b1 && b0 < a1;
}

static void feedback(uint32_t instance_id, uint32_t flags)
{
    uint32_t i;
    for (i = 0; i < s_feedback_pending.count; ++i) {
        if (s_feedback_pending.events[i].instance_id == instance_id) {
            s_feedback_pending.events[i].flags |= flags;
            return;
        }
    }
    if (s_feedback_pending.count >= FOREIGN_ACTION_FEEDBACK_CAPACITY) return;
    i = s_feedback_pending.count++;
    s_feedback_pending.events[i].instance_id = instance_id;
    s_feedback_pending.events[i].flags = flags;
}

static Smash64ActionSlot *find_slot(uint32_t instance_id)
{
    int i;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i)
        if (s_slots[i].active && s_slots[i].instance_id == instance_id)
            return &s_slots[i];
    return NULL;
}

static Smash64ActionSlot *free_slot(void)
{
    int i;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i)
        if (!s_slots[i].active) return &s_slots[i];
    return NULL;
}

void smash64_actions_clear(void)
{
    memset(s_slots, 0, sizeof(s_slots));
    memset(&s_feedback_pending, 0, sizeof(s_feedback_pending));
}

void smash64_actions_apply_commands(const ForeignActionEvents *events,
                                    double fighter_world_x,
                                    double fighter_foot_y,
                                    double facing,
                                    double units_to_px)
{
    uint32_t i, count;
    if (!events) return;
    count = events->count > FOREIGN_ACTION_EVENT_CAPACITY
                ? FOREIGN_ACTION_EVENT_CAPACITY : events->count;
    for (i = 0; i < count; ++i) {
        const ForeignActionEvent *e = &events->events[i];
        Smash64ActionSlot *slot;
        if (e->command == FOREIGN_ACTION_CANCEL_ALL) {
            smash64_actions_clear();
            continue;
        }
        slot = find_slot(e->instance_id);
        if (e->command == FOREIGN_ACTION_CANCEL) {
            if (slot) slot->active = 0;
            continue;
        }
        if (e->command != FOREIGN_ACTION_SPAWN || e->instance_id == 0 ||
            e->width <= 0.0 || e->height <= 0.0 ||
            !isfinite(e->offset_x) || !isfinite(e->offset_y) ||
            !isfinite(e->velocity_x) || !isfinite(e->velocity_y))
            continue;
        if (!slot) slot = free_slot();
        if (!slot) continue;
        memset(slot, 0, sizeof(*slot));
        slot->active = 1;
        slot->instance_id = e->instance_id;
        slot->kind = e->kind;
        slot->flags = e->flags;
        slot->x = fighter_world_x + facing * e->offset_x * units_to_px;
        slot->y = (e->flags & FOREIGN_ACTION_SELF_CONTACT)
                      ? 32.0
                      : fighter_foot_y - e->offset_y * units_to_px;
        slot->vx = facing * e->velocity_x * units_to_px;
        slot->vy = -e->velocity_y * units_to_px;
        slot->width = e->width * units_to_px;
        slot->height = e->height * units_to_px;
        slot->damage = e->damage;
        slot->lifetime = e->lifetime_ticks ? e->lifetime_ticks : 180;
    }
}

void smash64_actions_step(const Smash64ActionHost *host)
{
    int i;
    if (!host || !host->solid_at || !host->defeat_target) return;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i) {
        Smash64ActionSlot *a = &s_slots[i];
        double left, right, top, bottom;
        double nx, ny;
        int solid;
        if (!a->active) continue;
        if (a->age >= a->lifetime) {
            feedback(a->instance_id, FOREIGN_ACTION_EXPIRED);
            a->active = 0;
            continue;
        }

        left = a->x - a->width * 0.5;
        right = a->x + a->width * 0.5;
        top = a->y - a->height * 0.5;
        bottom = a->y + a->height * 0.5;
        if ((a->flags & FOREIGN_ACTION_SELF_CONTACT) &&
            overlap(left, right, host->fighter_left, host->fighter_right) &&
            overlap(top, bottom, host->fighter_top, host->fighter_bottom)) {
            feedback(a->instance_id, FOREIGN_ACTION_HIT_SELF);
            a->active = 0;
            continue;
        }
        if ((a->flags & FOREIGN_ACTION_HOSTILE) && !a->target_consumed &&
            host->defeat_target(left, right, top, bottom)) {
            a->target_consumed = 1;
            feedback(a->instance_id, FOREIGN_ACTION_HIT_TARGET);
            a->active = 0;
            continue;
        }

        /* Spawn frame is observable at the authored origin. Movement starts
         * on the following host tick. */
        if (a->age++ == 0) continue;
        nx = a->x + a->vx;
        ny = a->y + a->vy;
        solid = host->solid_at(nx, ny);
        if (!solid) {
            a->x = nx;
            a->y = ny;
            continue;
        }

        if (a->flags & FOREIGN_ACTION_FOLLOW_SURFACES) {
            const double speed = hypot(a->vx, a->vy);
            if (a->vy > 0.0) {
                a->vy = 0.0;
                a->vx = (a->vx < 0.0 ? -1.0 : 1.0) * speed;
                feedback(a->instance_id, FOREIGN_ACTION_HIT_FLOOR);
            } else if (a->vx != 0.0) {
                a->vx = 0.0;
                a->vy = -speed;
                feedback(a->instance_id, FOREIGN_ACTION_HIT_WALL);
            } else {
                feedback(a->instance_id,
                         FOREIGN_ACTION_HIT_CEILING | FOREIGN_ACTION_EXPIRED);
                a->active = 0;
            }
        } else {
            uint32_t hit_flag = a->vy > 0.0 ? FOREIGN_ACTION_HIT_FLOOR
                                : a->vy < 0.0 ? FOREIGN_ACTION_HIT_CEILING
                                             : FOREIGN_ACTION_HIT_WALL;
            feedback(a->instance_id, hit_flag | FOREIGN_ACTION_EXPIRED);
            a->active = 0;
        }
    }
}

void smash64_actions_drain_feedback(ForeignActionFeedback *out)
{
    if (out) *out = s_feedback_pending;
    memset(&s_feedback_pending, 0, sizeof(s_feedback_pending));
}

void smash64_actions_save(Smash64ActionSave *out)
{
    if (!out) return;
    memcpy(out->slots, s_slots, sizeof(s_slots));
    out->feedback_pending = s_feedback_pending;
}

int smash64_actions_restore(const Smash64ActionSave *saved)
{
    int i;
    if (!saved || saved->feedback_pending.count >
                      FOREIGN_ACTION_FEEDBACK_CAPACITY)
        return 0;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i) {
        const Smash64ActionSlot *a = &saved->slots[i];
        if (a->active > 1 || a->age > a->lifetime ||
            !isfinite(a->x) || !isfinite(a->y) ||
            !isfinite(a->vx) || !isfinite(a->vy) ||
            !isfinite(a->width) || !isfinite(a->height) ||
            a->width < 0.0 || a->height < 0.0)
            return 0;
    }
    memcpy(s_slots, saved->slots, sizeof(s_slots));
    s_feedback_pending = saved->feedback_pending;
    return 1;
}

int smash64_actions_snapshot(Smash64ActionSlot *out, int capacity)
{
    int i, count = 0;
    if (!out || capacity <= 0) return 0;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY && count < capacity; ++i)
        if (s_slots[i].active) out[count++] = s_slots[i];
    return count;
}
