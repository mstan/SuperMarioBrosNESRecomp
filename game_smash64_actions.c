#include "game_smash64_actions.h"

#include <float.h>
#include <math.h>
#include <string.h>

static Smash64ActionSlot s_slots[SMASH64_ACTION_SLOT_CAPACITY];
static ForeignActionFeedback s_feedback_pending;

#define SMASH64_ACTION_MAX_SPEED_PX 256.0
#define SMASH64_ACTION_MAX_EXTENT_PX 1024.0
#define SMASH64_ACTION_MAX_LIFETIME 3600u
#define SMASH64_ACTION_SAVE_SURFACE_SHIFT 28u
#define SMASH64_ACTION_SAVE_SURFACE_MASK  (7u << SMASH64_ACTION_SAVE_SURFACE_SHIFT)
#define SMASH64_ACTION_SAVE_CONSUMED      0x80000000u
#define SMASH64_ACTION_SAVE_SURFACE_ANIM_SHIFT 24u
#define SMASH64_ACTION_SAVE_SURFACE_ANIM_MASK  (0xFu << SMASH64_ACTION_SAVE_SURFACE_ANIM_SHIFT)
#define SMASH64_ACTION_SAVE_FLAGS_MASK    0x00FFFFFFu
#define SMASH64_ACTION_SURFACE_ANIM_TICKS 15u

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

static int action_solid(const Smash64ActionHost *host,
                        const Smash64ActionSlot *action,
                        double center_x, double center_y)
{
    const double half_width = action->width * 0.5;
    const double half_height = action->height * 0.5;
    const int downward_self_contact_above_hud =
        (action->flags & FOREIGN_ACTION_SELF_CONTACT) &&
        action->vy > 0.0 &&
        center_y - half_height < 32.0;

#define ACTION_SOLID_PROBE(px, py) \
    (downward_self_contact_above_hud && (py) < 32.0 \
         ? 0 : host->solid_at((px), (py)))

    /* Thunder begins above the visible playfield and falls through the HUD
     * boundary. Ignore each probe only while that probe is still above row32;
     * the first body point entering gameplay regains ordinary terrain policy. */
    return ACTION_SOLID_PROBE(center_x, center_y) ||
           ACTION_SOLID_PROBE(center_x - half_width,
                              center_y - half_height) ||
           ACTION_SOLID_PROBE(center_x + half_width,
                              center_y - half_height) ||
           ACTION_SOLID_PROBE(center_x - half_width,
                              center_y + half_height) ||
           ACTION_SOLID_PROBE(center_x + half_width,
                              center_y + half_height);
#undef ACTION_SOLID_PROBE
}

static void surface_normal_xy(uint32_t normal, double *x, double *y)
{
    *x = 0.0;
    *y = 0.0;
    if (normal == SMASH64_ACTION_SURFACE_DOWN) *y = 1.0;
    else if (normal == SMASH64_ACTION_SURFACE_RIGHT) *x = 1.0;
    else if (normal == SMASH64_ACTION_SURFACE_UP) *y = -1.0;
    else if (normal == SMASH64_ACTION_SURFACE_LEFT) *x = -1.0;
}

static uint32_t surface_normal_from_xy(double x, double y)
{
    if (x > 0.0) return SMASH64_ACTION_SURFACE_RIGHT;
    if (x < 0.0) return SMASH64_ACTION_SURFACE_LEFT;
    if (y > 0.0) return SMASH64_ACTION_SURFACE_DOWN;
    if (y < 0.0) return SMASH64_ACTION_SURFACE_UP;
    return SMASH64_ACTION_SURFACE_NONE;
}

static void action_set_surface_normal(Smash64ActionSlot *action,
                                      uint32_t normal)
{
    if (action->surface_normal == normal) return;
    action->surface_normal = normal;
    /* wpPikachuThunderJoltGroundAddAnim reattaches its AnimJoint at every
     * floor/wall segment, so its independent 0.5-frame source clock begins
     * at zero on every concave or convex turn. */
    action->surface_anim_age = 0u;
}

static void action_advance_surface_anim(Smash64ActionSlot *action)
{
    if (!(action->flags & FOREIGN_ACTION_FOLLOW_SURFACES) ||
        action->surface_normal == SMASH64_ACTION_SURFACE_NONE)
        return;
    action->surface_anim_age++;
    if (action->surface_anim_age >= SMASH64_ACTION_SURFACE_ANIM_TICKS)
        action->surface_anim_age = 0u;
}

static int action_has_support(const Smash64ActionHost *host,
                              const Smash64ActionSlot *action,
                              double center_x, double center_y)
{
    double nx, ny, tx = 0.0, ty = 0.0;
    const double half_width = action->width * 0.5;
    const double half_height = action->height * 0.5;
    double support_x, support_y;
    surface_normal_xy(action->surface_normal, &nx, &ny);
    if (nx == 0.0 && ny == 0.0) return 0;
    /* A swept action parks at the last nonsolid substep, which can leave its
     * edge almost two pixels shy of the integer tile boundary (one fractional
     * remainder plus the next <=1px step). Probe through that bounded gap or
     * a floor-attached Jolt immediately misclassifies level ground as a convex
     * edge and turns downward through the floor. */
    support_x = center_x + nx * (half_width + 2.0);
    support_y = center_y + ny * (half_height + 2.0);
    if (host->solid_at(support_x, support_y)) return 1;

    /* At a convex corner the crawler's center has not reached the new
     * surface yet: its leading edge rounds the corner first. Probe that edge
     * in the current tangent direction as well as the center. A center-only
     * query made an 8px Jolt climb a pipe, turn onto its top for one tick,
     * then immediately mistake the near edge for the far edge and turn back
     * down the same wall. */
    if (action->vx > 0.0) tx = 1.0;
    else if (action->vx < 0.0) tx = -1.0;
    else if (action->vy > 0.0) ty = 1.0;
    else if (action->vy < 0.0) ty = -1.0;
    return host->solid_at(
        support_x + tx * (half_width + 2.0),
        support_y + ty * (half_height + 2.0));
}

static int action_forward_solid(const Smash64ActionHost *host,
                                const Smash64ActionSlot *action,
                                double center_x, double center_y)
{
    const double half_width = action->width * 0.5;
    const double half_height = action->height * 0.5;
    double normal_x = 0.0, normal_y = 0.0;
    if (action->surface_normal != SMASH64_ACTION_SURFACE_NONE)
        surface_normal_xy(action->surface_normal, &normal_x, &normal_y);
    if (action->vx != 0.0) {
        const double x = center_x + (action->vx > 0.0 ? 1.0 : -1.0) *
                                      (half_width + 0.75);
        if (action->surface_normal != SMASH64_ACTION_SURFACE_NONE)
            return host->solid_at(x, center_y) ||
                   host->solid_at(x,
                                  center_y - normal_y *
                                                   half_height * 0.75);
        return host->solid_at(x, center_y) ||
               host->solid_at(x, center_y - half_height * 0.75) ||
               host->solid_at(x, center_y + half_height * 0.75);
    }
    if (action->vy != 0.0) {
        const double y = center_y + (action->vy > 0.0 ? 1.0 : -1.0) *
                                      (half_height + 0.75);
        if (action->surface_normal != SMASH64_ACTION_SURFACE_NONE)
            return host->solid_at(center_x, y) ||
                   host->solid_at(center_x - normal_x *
                                                   half_width * 0.75,
                                  y);
        return host->solid_at(center_x, y) ||
               host->solid_at(center_x - half_width * 0.75, y) ||
               host->solid_at(center_x + half_width * 0.75, y);
    }
    return 0;
}

static uint32_t surface_feedback_flag(uint32_t normal)
{
    if (normal == SMASH64_ACTION_SURFACE_DOWN)
        return FOREIGN_ACTION_HIT_FLOOR;
    if (normal == SMASH64_ACTION_SURFACE_UP)
        return FOREIGN_ACTION_HIT_CEILING;
    return FOREIGN_ACTION_HIT_WALL;
}

static void action_bounds(const Smash64ActionSlot *action,
                          double center_x, double center_y,
                          double *left, double *right,
                          double *top, double *bottom)
{
    *left = center_x - action->width * 0.5;
    *right = center_x + action->width * 0.5;
    *top = center_y - action->height * 0.5;
    *bottom = center_y + action->height * 0.5;
}

static int action_hits_self(const Smash64ActionHost *host,
                            const Smash64ActionSlot *action,
                            double center_x, double center_y)
{
    double left, right, top, bottom;
    int authored;
    if (!(action->flags & FOREIGN_ACTION_SELF_CONTACT)) return 0;
    if (host->self_contact) {
        authored = host->self_contact(
            action->kind, center_x, center_y, host->fighter_left,
            host->fighter_right, host->fighter_top, host->fighter_bottom);
        if (authored >= 0) return authored != 0;
    }
    action_bounds(action, center_x, center_y,
                  &left, &right, &top, &bottom);
    return overlap(left, right, host->fighter_left, host->fighter_right) &&
           overlap(top, bottom, host->fighter_top, host->fighter_bottom);
}

static int action_hits_target(const Smash64ActionHost *host,
                              const Smash64ActionSlot *action,
                              double center_x, double center_y)
{
    double left, right, top, bottom;
    if (!(action->flags & FOREIGN_ACTION_HOSTILE) || action->target_consumed)
        return 0;
    action_bounds(action, center_x, center_y,
                  &left, &right, &top, &bottom);
    return host->defeat_target(left, right, top, bottom);
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
                                    double units_to_px,
                                    Smash64ActionAttachmentResolver
                                        resolve_attachment)
{
    uint32_t i, count;
    if (!events || !isfinite(fighter_world_x) || !isfinite(fighter_foot_y) ||
        !isfinite(facing) || !isfinite(units_to_px) ||
        units_to_px <= 0.0 || units_to_px > 1.0)
        return;
    count = events->count > FOREIGN_ACTION_EVENT_CAPACITY
                ? FOREIGN_ACTION_EVENT_CAPACITY : events->count;
    for (i = 0; i < count; ++i) {
        const ForeignActionEvent *e = &events->events[i];
        Smash64ActionSlot *slot;
        double origin_x = fighter_world_x;
        double origin_y = fighter_foot_y;
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
        if (e->source_joint != 0 &&
            (!resolve_attachment ||
             !resolve_attachment(e->source_joint, fighter_world_x,
                                 fighter_foot_y, &origin_x, &origin_y) ||
             !isfinite(origin_x) || !isfinite(origin_y))) {
            feedback(e->instance_id, FOREIGN_ACTION_EXPIRED);
            continue;
        }
        if (!slot) slot = free_slot();
        if (!slot) {
            feedback(e->instance_id, FOREIGN_ACTION_EXPIRED);
            continue;
        }
        memset(slot, 0, sizeof(*slot));
        slot->active = 1;
        slot->instance_id = e->instance_id;
        slot->kind = e->kind;
        slot->flags = e->flags;
        slot->source_joint = e->source_joint;
        slot->x = origin_x + facing * e->offset_x * units_to_px;
        slot->y = (e->flags & FOREIGN_ACTION_SELF_CONTACT)
                      ? 32.0 - e->offset_y * units_to_px
                      : origin_y - e->offset_y * units_to_px;
        slot->vx = facing * e->velocity_x * units_to_px;
        slot->vy = -e->velocity_y * units_to_px;
        slot->surface_speed = e->surface_velocity * units_to_px;
        slot->width = e->width * units_to_px;
        slot->height = e->height * units_to_px;
        slot->damage = e->damage;
        slot->lifetime = e->lifetime_ticks ? e->lifetime_ticks : 180;
        if (!isfinite(slot->x) || !isfinite(slot->y) ||
            !isfinite(slot->vx) || !isfinite(slot->vy) ||
            !isfinite(slot->surface_speed) ||
            !isfinite(slot->width) || !isfinite(slot->height) ||
            fabs(slot->vx) > SMASH64_ACTION_MAX_SPEED_PX ||
            fabs(slot->vy) > SMASH64_ACTION_MAX_SPEED_PX ||
            slot->surface_speed < 0.0 ||
            slot->surface_speed > SMASH64_ACTION_MAX_SPEED_PX ||
            slot->width <= 0.0 || slot->height <= 0.0 ||
            slot->width > SMASH64_ACTION_MAX_EXTENT_PX ||
            slot->height > SMASH64_ACTION_MAX_EXTENT_PX ||
            slot->lifetime > SMASH64_ACTION_MAX_LIFETIME) {
            memset(slot, 0, sizeof(*slot));
        }
    }
}

void smash64_actions_step(const Smash64ActionHost *host)
{
    int i;
    if (!host || !host->solid_at || !host->defeat_target) return;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i) {
        Smash64ActionSlot *a = &s_slots[i];
        double nx, ny, step_x, step_y;
        int solid, steps, step, followed_turn;
        if (!a->active) continue;
        if (a->age >= a->lifetime) {
            feedback(a->instance_id, FOREIGN_ACTION_EXPIRED);
            a->active = 0;
            continue;
        }

        if (action_hits_self(host, a, a->x, a->y)) {
            feedback(a->instance_id, FOREIGN_ACTION_HIT_SELF);
            a->active = 0;
            continue;
        }
        if (action_hits_target(host, a, a->x, a->y)) {
            a->target_consumed = 1;
            feedback(a->instance_id, FOREIGN_ACTION_HIT_TARGET);
            if (!(a->flags & FOREIGN_ACTION_PERSIST_AFTER_TARGET)) {
                a->active = 0;
                continue;
            }
        }

        /* Spawn frame is observable at the authored origin. Movement starts
         * on the following host tick. */
        if (a->age++ == 0) continue;
        action_advance_surface_anim(a);
        steps = (int)ceil(fmax(fabs(a->vx), fabs(a->vy)));
        if (steps < 1) steps = 1;
        step_x = a->vx / (double)steps;
        step_y = a->vy / (double)steps;
        nx = a->x;
        ny = a->y;
        solid = 0;
        followed_turn = 0;
        for (step = 0; step < steps; ++step) {
            const double candidate_x = nx + step_x;
            const double candidate_y = ny + step_y;

            if ((a->flags & FOREIGN_ACTION_FOLLOW_SURFACES) &&
                a->surface_normal != SMASH64_ACTION_SURFACE_NONE) {
                if (action_forward_solid(host, a,
                                         candidate_x, candidate_y)) {
                    double normal_x, normal_y;
                    const double tangent_x = a->vx > 0.0 ? 1.0 :
                                             a->vx < 0.0 ? -1.0 : 0.0;
                    const double tangent_y = a->vy > 0.0 ? 1.0 :
                                             a->vy < 0.0 ? -1.0 : 0.0;
                    const double speed = hypot(a->vx, a->vy);
                    surface_normal_xy(a->surface_normal,
                                      &normal_x, &normal_y);
                    action_set_surface_normal(
                        a, surface_normal_from_xy(tangent_x, tangent_y));
                    a->vx = -normal_x * speed;
                    a->vy = -normal_y * speed;
                    feedback(a->instance_id,
                             surface_feedback_flag(a->surface_normal));
                    followed_turn = 1;
                    break;
                }
                nx = candidate_x;
                ny = candidate_y;
                if (action_hits_self(host, a, nx, ny)) {
                    feedback(a->instance_id, FOREIGN_ACTION_HIT_SELF);
                    a->active = 0;
                    break;
                }
                if (action_hits_target(host, a, nx, ny)) {
                    a->target_consumed = 1;
                    feedback(a->instance_id, FOREIGN_ACTION_HIT_TARGET);
                    if (!(a->flags &
                          FOREIGN_ACTION_PERSIST_AFTER_TARGET)) {
                        a->active = 0;
                        break;
                    }
                }
                if (!action_has_support(host, a, nx, ny)) {
                    double normal_x, normal_y;
                    const double tangent_x = a->vx > 0.0 ? 1.0 :
                                             a->vx < 0.0 ? -1.0 : 0.0;
                    const double tangent_y = a->vy > 0.0 ? 1.0 :
                                             a->vy < 0.0 ? -1.0 : 0.0;
                    const double speed = hypot(a->vx, a->vy);
                    surface_normal_xy(a->surface_normal,
                                      &normal_x, &normal_y);
                    a->vx = normal_x * speed;
                    a->vy = normal_y * speed;
                    action_set_surface_normal(
                        a, surface_normal_from_xy(-tangent_x, -tangent_y));
                    /* Smash 64 Thunder Jolt owns floor and left/right wall
                     * line states, but no ceiling line state. Reaching the
                     * unsupported bottom of a floating wall must expire
                     * instead of inventing an underside-crawling move. */
                    if (a->surface_normal == SMASH64_ACTION_SURFACE_UP) {
                        feedback(a->instance_id, FOREIGN_ACTION_EXPIRED);
                        a->active = 0;
                        break;
                    }
                    followed_turn = 1;
                    break;
                }
                continue;
            }
            if (action_solid(host, a, candidate_x, candidate_y)) {
                solid = 1;
                break;
            }
            if (action_hits_self(host, a, candidate_x, candidate_y)) {
                feedback(a->instance_id, FOREIGN_ACTION_HIT_SELF);
                a->active = 0;
                break;
            }
            if (action_hits_target(host, a, candidate_x, candidate_y)) {
                a->target_consumed = 1;
                feedback(a->instance_id, FOREIGN_ACTION_HIT_TARGET);
                if (!(a->flags & FOREIGN_ACTION_PERSIST_AFTER_TARGET)) {
                    a->active = 0;
                    break;
                }
            }
            nx = candidate_x;
            ny = candidate_y;
        }
        if (!a->active) continue;
        if (followed_turn) {
            a->x = nx;
            a->y = ny;
            continue;
        }
        if (!solid) {
            a->x = nx;
            a->y = ny;
            continue;
        }

        /* Preserve the motion up to the last safe substep before reflecting
         * a surface-following action. This keeps its path continuous without
         * ever placing its box inside a solid tile. */
        a->x = nx;
        a->y = ny;

        if (a->flags & FOREIGN_ACTION_FOLLOW_SURFACES) {
            const double speed =
                (a->flags & FOREIGN_ACTION_SURFACE_SPEED) &&
                a->surface_speed > 0.0
                    ? a->surface_speed : hypot(a->vx, a->vy);
            const int blocked_x =
                action_solid(host, a, nx + step_x, ny);
            const int blocked_y =
                action_solid(host, a, nx, ny + step_y);
            if (blocked_y && !blocked_x) {
                action_set_surface_normal(
                    a, step_y > 0.0 ? SMASH64_ACTION_SURFACE_DOWN
                                    : SMASH64_ACTION_SURFACE_UP);
                a->vy = 0.0;
                a->vx = (a->vx < 0.0 ? -1.0 : 1.0) * speed;
            } else if (blocked_x || step_x != 0.0) {
                action_set_surface_normal(
                    a, step_x > 0.0 ? SMASH64_ACTION_SURFACE_RIGHT
                                    : SMASH64_ACTION_SURFACE_LEFT);
                a->vx = 0.0;
                a->vy = (a->vy != 0.0 ? (a->vy < 0.0 ? -1.0 : 1.0)
                                      : -1.0) * speed;
            } else {
                feedback(a->instance_id,
                         FOREIGN_ACTION_HIT_CEILING | FOREIGN_ACTION_EXPIRED);
                a->active = 0;
                continue;
            }
            /* Smash 64's attached Thunder Jolt has floor, left-wall and
             * right-wall line states only. An airborne Jolt striking a
             * ceiling therefore dies instead of inventing an underside line
             * state. The same rule already applies at a later convex turn. */
            if (a->surface_normal == SMASH64_ACTION_SURFACE_UP) {
                feedback(a->instance_id,
                         FOREIGN_ACTION_HIT_CEILING |
                         FOREIGN_ACTION_EXPIRED);
                a->active = 0;
                continue;
            }
            feedback(a->instance_id,
                     surface_feedback_flag(a->surface_normal));
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
            a->surface_anim_age >= SMASH64_ACTION_SURFACE_ANIM_TICKS ||
            !isfinite(a->x) || !isfinite(a->y) ||
            !isfinite(a->vx) || !isfinite(a->vy) ||
            !isfinite(a->surface_speed) ||
            !isfinite(a->width) || !isfinite(a->height) ||
            a->width < 0.0 || a->height < 0.0 ||
            fabs(a->vx) > SMASH64_ACTION_MAX_SPEED_PX ||
            fabs(a->vy) > SMASH64_ACTION_MAX_SPEED_PX ||
            a->surface_speed < 0.0 ||
            a->surface_speed > SMASH64_ACTION_MAX_SPEED_PX ||
            a->width > SMASH64_ACTION_MAX_EXTENT_PX ||
            a->height > SMASH64_ACTION_MAX_EXTENT_PX ||
            a->lifetime > SMASH64_ACTION_MAX_LIFETIME ||
            a->surface_normal > SMASH64_ACTION_SURFACE_LEFT ||
            (!(a->flags & FOREIGN_ACTION_FOLLOW_SURFACES) &&
             (a->surface_normal != SMASH64_ACTION_SURFACE_NONE ||
              a->surface_anim_age != 0u)) ||
            (a->active && a->lifetime == 0))
            return 0;
    }
    memcpy(s_slots, saved->slots, sizeof(s_slots));
    s_feedback_pending = saved->feedback_pending;
    return 1;
}

static void compact_put_u32(uint8_t **cursor, uint32_t value)
{
    uint8_t *p = *cursor;
    p[0] = (uint8_t)value;
    p[1] = (uint8_t)(value >> 8);
    p[2] = (uint8_t)(value >> 16);
    p[3] = (uint8_t)(value >> 24);
    *cursor += 4;
}

static uint32_t compact_get_u32(const uint8_t **cursor)
{
    const uint8_t *p = *cursor;
    const uint32_t value = (uint32_t)p[0] |
                           ((uint32_t)p[1] << 8) |
                           ((uint32_t)p[2] << 16) |
                           ((uint32_t)p[3] << 24);
    *cursor += 4;
    return value;
}

static int compact_put_f32(uint8_t **cursor, double value)
{
    float narrowed;
    uint32_t bits;
    if (!isfinite(value) || fabs(value) > FLT_MAX) return 0;
    narrowed = (float)value;
    memcpy(&bits, &narrowed, sizeof(bits));
    compact_put_u32(cursor, bits);
    return 1;
}

static double compact_get_f32(const uint8_t **cursor)
{
    const uint32_t bits = compact_get_u32(cursor);
    float value;
    memcpy(&value, &bits, sizeof(value));
    return (double)value;
}

int smash64_actions_serialize(uint8_t *buf, int capacity)
{
    uint8_t *cursor;
    uint32_t active_count = 0;
    uint32_t i;
    int required;

    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i)
        if (s_slots[i].active) ++active_count;
    if (s_feedback_pending.count > FOREIGN_ACTION_FEEDBACK_CAPACITY) return -1;
    required = 4 + (int)active_count * 56 +
               (int)s_feedback_pending.count * 8;
    if (!buf || capacity < required || required > SMASH64_ACTION_SERIALIZED_MAX)
        return -1;

    buf[0] = 5;
    buf[1] = (uint8_t)active_count;
    buf[2] = (uint8_t)s_feedback_pending.count;
    buf[3] = 0;
    cursor = buf + 4;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i) {
        const Smash64ActionSlot *a = &s_slots[i];
        uint32_t damage_bits;
        int32_t damage = a->damage;
        if (!a->active) continue;
        compact_put_u32(&cursor, a->instance_id);
        compact_put_u32(&cursor, a->kind);
        compact_put_u32(&cursor,
                        (a->flags & SMASH64_ACTION_SAVE_FLAGS_MASK) |
                        ((a->surface_anim_age <<
                          SMASH64_ACTION_SAVE_SURFACE_ANIM_SHIFT) &
                         SMASH64_ACTION_SAVE_SURFACE_ANIM_MASK) |
                        ((a->surface_normal <<
                          SMASH64_ACTION_SAVE_SURFACE_SHIFT) &
                         SMASH64_ACTION_SAVE_SURFACE_MASK) |
                        (a->target_consumed
                             ? SMASH64_ACTION_SAVE_CONSUMED : 0u));
        compact_put_u32(&cursor, a->source_joint);
        if (!compact_put_f32(&cursor, a->x) ||
            !compact_put_f32(&cursor, a->y) ||
            !compact_put_f32(&cursor, a->vx) ||
            !compact_put_f32(&cursor, a->vy) ||
            !compact_put_f32(&cursor, a->width) ||
            !compact_put_f32(&cursor, a->height) ||
            !compact_put_f32(&cursor, a->surface_speed))
            return -1;
        memcpy(&damage_bits, &damage, sizeof(damage_bits));
        compact_put_u32(&cursor, damage_bits);
        compact_put_u32(&cursor, a->age);
        compact_put_u32(&cursor, a->lifetime);
    }
    for (i = 0; i < s_feedback_pending.count; ++i) {
        compact_put_u32(&cursor,
                        s_feedback_pending.events[i].instance_id);
        compact_put_u32(&cursor, s_feedback_pending.events[i].flags);
    }
    return required;
}

int smash64_actions_deserialize(const uint8_t *buf, int length)
{
    Smash64ActionSave saved;
    const uint8_t *cursor;
    uint32_t active_count, feedback_count, i;
    int required;

    if (!buf || length < 4 || (buf[0] != 3 && buf[0] != 4 && buf[0] != 5) ||
        buf[3] != 0)
        return 0;
    active_count = buf[1];
    feedback_count = buf[2];
    if (active_count > SMASH64_ACTION_SLOT_CAPACITY ||
        feedback_count > FOREIGN_ACTION_FEEDBACK_CAPACITY)
        return 0;
    required = 4 + (int)active_count * 56 + (int)feedback_count * 8;
    if (length != required || required > SMASH64_ACTION_SERIALIZED_MAX)
        return 0;

    memset(&saved, 0, sizeof(saved));
    cursor = buf + 4;
    for (i = 0; i < active_count; ++i) {
        Smash64ActionSlot *a = &saved.slots[i];
        uint32_t damage_bits;
        int32_t damage;
        a->active = 1;
        a->instance_id = compact_get_u32(&cursor);
        a->kind = compact_get_u32(&cursor);
        if (buf[0] == 4 || buf[0] == 5) {
            const uint32_t packed = compact_get_u32(&cursor);
            a->flags = packed & SMASH64_ACTION_SAVE_FLAGS_MASK;
            a->surface_normal =
                (packed & SMASH64_ACTION_SAVE_SURFACE_MASK) >>
                SMASH64_ACTION_SAVE_SURFACE_SHIFT;
            a->target_consumed =
                (packed & SMASH64_ACTION_SAVE_CONSUMED) != 0;
            a->source_joint = compact_get_u32(&cursor);
            if (buf[0] == 5)
                a->surface_anim_age =
                    (packed & SMASH64_ACTION_SAVE_SURFACE_ANIM_MASK) >>
                    SMASH64_ACTION_SAVE_SURFACE_ANIM_SHIFT;
        } else {
            a->flags = compact_get_u32(&cursor);
            a->surface_normal = compact_get_u32(&cursor);
        }
        a->x = compact_get_f32(&cursor);
        a->y = compact_get_f32(&cursor);
        a->vx = compact_get_f32(&cursor);
        a->vy = compact_get_f32(&cursor);
        a->width = compact_get_f32(&cursor);
        a->height = compact_get_f32(&cursor);
        if (buf[0] == 4 || buf[0] == 5)
            a->surface_speed = compact_get_f32(&cursor);
        damage_bits = compact_get_u32(&cursor);
        memcpy(&damage, &damage_bits, sizeof(damage));
        a->damage = damage;
        a->age = compact_get_u32(&cursor);
        a->lifetime = compact_get_u32(&cursor);
        if (buf[0] == 3) {
            a->target_consumed = compact_get_u32(&cursor);
            a->surface_speed = hypot(a->vx, a->vy);
        }
        if (buf[0] != 5 && (a->flags & FOREIGN_ACTION_FOLLOW_SURFACES))
            a->surface_anim_age = a->age % SMASH64_ACTION_SURFACE_ANIM_TICKS;
    }
    saved.feedback_pending.count = feedback_count;
    for (i = 0; i < feedback_count; ++i) {
        saved.feedback_pending.events[i].instance_id =
            compact_get_u32(&cursor);
        saved.feedback_pending.events[i].flags = compact_get_u32(&cursor);
    }
    return smash64_actions_restore(&saved);
}

int smash64_actions_snapshot(Smash64ActionSlot *out, int capacity)
{
    int i, count = 0;
    if (!out || capacity <= 0) return 0;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY && count < capacity; ++i)
        if (s_slots[i].active) out[count++] = s_slots[i];
    return count;
}

int smash64_actions_has_active_kind(uint32_t kind)
{
    int i;
    if (kind == 0) return 0;
    for (i = 0; i < SMASH64_ACTION_SLOT_CAPACITY; ++i) {
        if (s_slots[i].active && s_slots[i].kind == kind)
            return 1;
    }
    return 0;
}
