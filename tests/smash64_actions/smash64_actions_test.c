#include "game_smash64_actions.h"
#include "game_smash64_fighter_profile.h"
#include "mods/smash64/ssb_ported/pikachu_locomotion.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int failures;
static int target_hits;
static int solid_mode;
static int solid_wall;
static int target_strip;
static int perimeter_mode;
static int large_perimeter_mode;
static int floating_wall_mode;
static int hud_boundary_mode;
static int target_box;
static double target_left, target_right, target_top, target_bottom;
static int attachment_calls;

static int resolve_attachment(uint32_t source_joint,
                              double fighter_world_x,
                              double fighter_foot_y,
                              double *world_x, double *screen_y)
{
    ++attachment_calls;
    if (source_joint != 11) return 0;
    *world_x = fighter_world_x;
    *screen_y = fighter_foot_y;
    return 1;
}

static int source_self_contact(uint32_t kind, double action_x,
                               double action_y, double fighter_left,
                               double fighter_right, double fighter_top,
                               double fighter_bottom)
{
    (void)fighter_top;
    if (kind != PIKACHU_PROJECTILE_THUNDER) return -1;
    return smash64_pikachu_thunder_source_contact(
        action_x, action_y, fighter_left, fighter_right, fighter_bottom);
}

static void put_u32(uint8_t **cursor, uint32_t value)
{
    (*cursor)[0] = (uint8_t)value;
    (*cursor)[1] = (uint8_t)(value >> 8);
    (*cursor)[2] = (uint8_t)(value >> 16);
    (*cursor)[3] = (uint8_t)(value >> 24);
    *cursor += 4;
}

static void put_f32(uint8_t **cursor, float value)
{
    uint32_t bits;
    memcpy(&bits, &value, sizeof(bits));
    put_u32(cursor, bits);
}

#define CHECK(x) do { if (!(x)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); \
    ++failures; \
} } while (0)

static int solid_at(double x, double y)
{
    return (hud_boundary_mode && y < 32.0) ||
           (solid_mode && y >= 100.0) ||
           (solid_wall && x >= 70.0 && x < 71.0) ||
           (perimeter_mode &&
            (y >= 12.0 || (x >= 12.0 && x < 20.0 && y >= 4.0))) ||
           (large_perimeter_mode &&
            (y >= 208.0 ||
             (x >= 196.0 && x < 228.0 && y >= 176.0))) ||
           (floating_wall_mode &&
            x >= 196.0 && x < 228.0 && y >= 176.0 && y < 192.0);
}

static int defeat_target(double l, double r, double t, double b)
{
    if (target_box && l < target_right && r > target_left &&
        t < target_bottom && b > target_top) {
        target_box = 0;
        return 1;
    }
    if (target_strip && l < 71.0 && r > 70.0 && t < 81.0 && b > 79.0)
        return 1;
    if (!target_hits) return 0;
    --target_hits;
    return 1;
}

static ForeignActionEvent spawn(uint32_t id, uint32_t flags)
{
    ForeignActionEvent e;
    memset(&e, 0, sizeof(e));
    e.instance_id = id;
    e.kind = 7;
    e.command = FOREIGN_ACTION_SPAWN;
    e.flags = flags;
    e.offset_y = 100.0;
    e.velocity_x = 40.0;
    e.velocity_y = -40.0;
    e.width = 100.0;
    e.height = 100.0;
    e.damage = 10;
    e.lifetime_ticks = 20;
    return e;
}

int main(void)
{
    ForeignActionEvents commands;
    ForeignActionFeedback feedback;
    Smash64ActionHost host;
    Smash64ActionSave saved, bad;
    Smash64ActionSlot slots[8];
    uint8_t compact[SMASH64_ACTION_SERIALIZED_MAX];
    int compact_len;

    memset(&host, 0, sizeof(host));
    host.solid_at = solid_at;
    host.defeat_target = defeat_target;
    host.fighter_left = 0.0;
    host.fighter_right = 16.0;
    host.fighter_top = 0.0;
    host.fighter_bottom = 32.0;

    smash64_actions_clear();
    memset(&commands, 0, sizeof(commands));
    commands.count = 1;
    commands.events[0] = spawn(1, FOREIGN_ACTION_HOSTILE |
                                  FOREIGN_ACTION_FOLLOW_SURFACES);
    smash64_actions_apply_commands(&commands, 50.0, 120.0, 1.0, 0.08, NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(smash64_actions_has_active_kind(7));
    CHECK(!smash64_actions_has_active_kind(8));
    CHECK(slots[0].x == 50.0);
    CHECK(slots[0].y == 112.0);
    target_hits = 1;
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    CHECK(!smash64_actions_has_active_kind(7));
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_TARGET);

    commands.events[0] = spawn(2, FOREIGN_ACTION_SELF_CONTACT);
    smash64_actions_apply_commands(&commands, 8.0, 120.0, 1.0, 0.08, NULL);
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_SELF);

    commands.events[0] = spawn(3, 0);
    smash64_actions_apply_commands(&commands, 50.0, 120.0, 1.0, 0.08, NULL);
    smash64_actions_save(&saved);
    smash64_actions_clear();
    CHECK(smash64_actions_restore(&saved));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    bad = saved;
    bad.slots[0].width = -1.0;
    CHECK(!smash64_actions_restore(&bad));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    bad = saved;
    bad.slots[0].vx = 1.0e300;
    CHECK(!smash64_actions_restore(&bad));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    bad = saved;
    bad.slots[0].surface_speed = -1.0;
    CHECK(!smash64_actions_restore(&bad));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);

    smash64_actions_clear();
    commands.events[0] = spawn(4, 0);
    smash64_actions_apply_commands(&commands, 50.0, 120.0, -1.0, 0.08,
                                   NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].vx < 0.0);
    smash64_actions_clear();
    commands.events[0] = spawn(5, FOREIGN_ACTION_ORIENTED_VELOCITY);
    commands.events[0].velocity_x = 40.0;
    smash64_actions_apply_commands(&commands, 50.0, 120.0, -1.0, 0.08,
                                   NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].vx > 0.0);
    smash64_actions_clear();
    CHECK(smash64_actions_restore(&saved));

    compact_len = smash64_actions_serialize(compact, sizeof(compact));
    CHECK(compact_len > 0);
    CHECK(compact_len <= 512);
    smash64_actions_clear();
    CHECK(smash64_actions_deserialize(compact, compact_len));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].instance_id == 3);
    CHECK(slots[0].x == 50.0);
    CHECK(slots[0].y == 112.0);
    CHECK(!smash64_actions_deserialize(compact, compact_len - 1));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    compact[0] = 99;
    CHECK(!smash64_actions_deserialize(compact, compact_len));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    compact[0] = 4;

    /* Version 3 records remain loadable. They lacked attachment identity and
     * a distinct attached speed, so migration deliberately preserves their
     * current magnitude rather than reinterpreting an opaque kind. */
    {
        uint8_t legacy[60] = { 3, 1, 0, 0 };
        uint8_t *p = legacy + 4;
        put_u32(&p, 77); /* instance */
        put_u32(&p, 7);  /* kind */
        put_u32(&p, FOREIGN_ACTION_FOLLOW_SURFACES);
        put_u32(&p, SMASH64_ACTION_SURFACE_DOWN);
        put_f32(&p, 10.0f);
        put_f32(&p, 20.0f);
        put_f32(&p, 3.0f);
        put_f32(&p, 4.0f);
        put_f32(&p, 8.0f);
        put_f32(&p, 8.0f);
        put_u32(&p, 10);
        put_u32(&p, 2);
        put_u32(&p, 100);
        put_u32(&p, 0);
        CHECK(p == legacy + sizeof(legacy));
        CHECK(smash64_actions_deserialize(legacy, sizeof(legacy)));
        CHECK(smash64_actions_snapshot(slots, 8) == 1);
        CHECK(slots[0].source_joint == 0);
        CHECK(slots[0].surface_speed == 5.0);
    }

    /* Source Thunder Jolt is an airborne 40-unit action until first contact,
     * then becomes a 55-unit floor/L/R-wall line action while carrying the
     * same 100-tick lifetime and joint-11 identity. */
    smash64_actions_clear();
    commands.events[0] = spawn(78, FOREIGN_ACTION_FOLLOW_SURFACES |
                                   FOREIGN_ACTION_SURFACE_SPEED);
    commands.events[0].source_joint = 11;
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 28.284271;
    commands.events[0].velocity_y = -28.284271;
    commands.events[0].surface_velocity = 55.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    solid_mode = 1;
    attachment_calls = 0;
    smash64_actions_apply_commands(&commands, 50.0, 92.0, 1.0, 0.08,
                                   resolve_attachment);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(attachment_calls == 1);
    CHECK(slots[0].source_joint == 11);
    CHECK(slots[0].x == 50.0 && slots[0].y == 92.0);
    CHECK(fabs(hypot(slots[0].vx, slots[0].vy) - 3.2) < 0.0001);
    smash64_actions_step(&host); /* authored spawn frame */
    {
        int i;
        for (i = 0; i < 4; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal != SMASH64_ACTION_SURFACE_NONE)
                break;
        }
        CHECK(i < 4);
    }
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN);
    CHECK(fabs(hypot(slots[0].vx, slots[0].vy) - 4.4) < 0.0001);
    CHECK(slots[0].lifetime == 100);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_FLOOR);
    compact_len = smash64_actions_serialize(compact, sizeof(compact));
    CHECK(compact_len == 60 && compact[0] == 5);
    smash64_actions_clear();
    CHECK(smash64_actions_deserialize(compact, compact_len));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].source_joint == 11);
    CHECK(fabs(slots[0].surface_speed - 4.4) < 0.0001);
    solid_mode = 0;

    /* A non-root source attachment must never silently become the fighter
     * root or index an unchecked joint. Missing/invalid resolvers fail the
     * spawn closed and leave no persistent action behind. */
    smash64_actions_clear();
    commands.events[0].instance_id = 79;
    smash64_actions_apply_commands(&commands, 50.0, 92.0, 1.0, 0.08, NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 79);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);
    commands.events[0].source_joint = 12;
    smash64_actions_apply_commands(&commands, 50.0, 92.0, 1.0, 0.08,
                                   resolve_attachment);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 79);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);

    /* Slot exhaustion is also a rejected persistent spawn, not silence. */
    smash64_actions_clear();
    for (int slot_index = 0;
         slot_index < SMASH64_ACTION_SLOT_CAPACITY;
         ++slot_index) {
        commands.events[0] = spawn(100u + (uint32_t)slot_index, 0);
        commands.events[0].offset_y = 0.0;
        smash64_actions_apply_commands(&commands, 50.0, 92.0, 1.0, 0.08,
                                       NULL);
    }
    CHECK(smash64_actions_snapshot(slots, 8) == 8);
    commands.events[0] = spawn(108u, 0);
    commands.events[0].offset_y = 0.0;
    smash64_actions_apply_commands(&commands, 50.0, 92.0, 1.0, 0.08, NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 8);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 108u);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);

    /* A fast Thunder-sized action must sweep every crossed pixel and its
     * bounds, rather than tunneling through a one-pixel wall. */
    smash64_actions_clear();
    commands.events[0] = spawn(4, FOREIGN_ACTION_DESTROY_ON_SOLID);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 500.0;
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 1.0;
    commands.events[0].height = 1.0;
    solid_wall = 1;
    smash64_actions_apply_commands(&commands, 50.0, 80.0, 1.0, 0.08, NULL);
    smash64_actions_step(&host); /* authored spawn frame */
    smash64_actions_step(&host);
    solid_wall = 0;
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_WALL);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);

    /* Enemy and self contacts use the same swept path, so Thunder cannot
     * jump across Pikachu and Jolt cannot jump across a narrow target. */
    smash64_actions_clear();
    commands.events[0] = spawn(5, FOREIGN_ACTION_HOSTILE);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 500.0;
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 1.0;
    commands.events[0].height = 1.0;
    target_strip = 1;
    smash64_actions_apply_commands(&commands, 50.0, 80.0, 1.0, 0.08, NULL);
    smash64_actions_step(&host);
    smash64_actions_step(&host);
    target_strip = 0;
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_TARGET);

    /* A surface-following Jolt must retain its attached side across convex
     * and concave corners: floor -> left wall -> top -> right wall -> floor. */
    smash64_actions_clear();
    memset(&commands, 0, sizeof(commands));
    commands.count = 1;
    commands.events[0] = spawn(8, FOREIGN_ACTION_FOLLOW_SURFACES);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 12.5; /* one host pixel */
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 12.5;
    commands.events[0].height = 12.5;
    commands.events[0].lifetime_ticks = 100;
    perimeter_mode = 1;
    smash64_actions_apply_commands(&commands, 4.0, 10.5, 1.0, 0.08, NULL);
    {
        int i, saw_left_wall = 0, saw_top = 0, saw_right_wall = 0;
        uint32_t previous_surface = SMASH64_ACTION_SURFACE_NONE;
        int surface_restarts = 0;
        for (i = 0; i < 80; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal != previous_surface) {
                /* Both convex forward blocks and concave support losses
                 * reattach GroundAddAnim at its source frame zero. */
                CHECK(slots[0].surface_anim_age == 0u);
                previous_surface = slots[0].surface_normal;
                ++surface_restarts;
            }
            if (slots[0].surface_normal == SMASH64_ACTION_SURFACE_RIGHT &&
                slots[0].vy < 0.0)
                saw_left_wall = 1;
            if (saw_left_wall &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN &&
                slots[0].vx > 0.0)
                saw_top = 1;
            if (saw_top &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_LEFT &&
                slots[0].vy > 0.0)
                saw_right_wall = 1;
        }
        CHECK(saw_left_wall && saw_top && saw_right_wall);
        CHECK(surface_restarts >= 4);
        CHECK(slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN);
        CHECK(slots[0].vx > 0.0 && slots[0].vy == 0.0);
        compact_len = smash64_actions_serialize(compact, sizeof(compact));
        CHECK(compact_len > 0 && compact_len <= 512);
        smash64_actions_clear();
        CHECK(smash64_actions_deserialize(compact, compact_len));
        CHECK(smash64_actions_snapshot(slots, 8) == 1);
        CHECK(slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN);
    }

    /* Once attached to a wall, the swept candidate still owns enemy contact.
     * Put a narrow target one pixel ahead so the tick-start overlap misses it
     * and only the attached movement branch can consume it. */
    smash64_actions_clear();
    commands.events[0] = spawn(9, FOREIGN_ACTION_HOSTILE |
                                  FOREIGN_ACTION_FOLLOW_SURFACES);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 12.5;
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 12.5;
    commands.events[0].height = 12.5;
    commands.events[0].lifetime_ticks = 100;
    smash64_actions_apply_commands(&commands, 4.0, 10.5, 1.0, 0.08, NULL);
    {
        int i;
        for (i = 0; i < 30; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal == SMASH64_ACTION_SURFACE_RIGHT &&
                slots[0].vy < 0.0)
                break;
        }
        CHECK(i < 30);
        target_left = slots[0].x - 0.25;
        target_right = slots[0].x + 0.25;
        target_top = slots[0].y - 1.5;
        target_bottom = slots[0].y - 1.0;
        target_box = 1;
        smash64_actions_step(&host);
        CHECK(smash64_actions_snapshot(slots, 8) == 0);
        smash64_actions_drain_feedback(&feedback);
        CHECK(feedback.count == 1);
        CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_TARGET);
        CHECK(target_box == 0);
    }
    perimeter_mode = 0;

    /* Ground Jolt's owner motion is a 15-host-tick, 0.5-source-frame clock:
     * 0, .5, ... 7.0, then a fresh segment frame 0 (never a drifting action
     * lifetime modulo). */
    smash64_actions_clear();
    commands.events[0] = spawn(91, FOREIGN_ACTION_FOLLOW_SURFACES);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 25.0;
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    solid_mode = 1;
    smash64_actions_apply_commands(&commands, 50.0, 96.0, 1.0, 0.08, NULL);
    smash64_actions_save(&saved);
    /* Begin on an already attached floor segment. This directly exercises
     * the persistent action slot the renderer snapshots, not a transient
     * presentation proxy. */
    saved.slots[0].surface_normal = SMASH64_ACTION_SURFACE_DOWN;
    saved.slots[0].surface_anim_age = 0u;
    saved.slots[0].age = 1u;
    CHECK(smash64_actions_restore(&saved));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == 0u);
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == 1u); /* presentation frame 0.5 */
    {
        int i;
        for (i = 0; i < 13; ++i) smash64_actions_step(&host);
    }
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == 14u); /* presentation frame 7.0 */
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == 0u); /* reset before source frame 7.5 */
    compact_len = smash64_actions_serialize(compact, sizeof(compact));
    CHECK(compact_len > 0 && compact_len <= 512 && compact[0] == 5u);
    smash64_actions_clear();
    CHECK(smash64_actions_deserialize(compact, compact_len));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == 0u);
    /* v4 has no packed surface clock; migration derives a bounded phase from
     * its retained action age rather than accepting a stale/unbounded value. */
    compact[0] = 4u;
    compact[15] &= 0xF0u; /* first slot packed flags byte: clear v5 age nibble */
    smash64_actions_clear();
    CHECK(smash64_actions_deserialize(compact, compact_len));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].surface_anim_age == slots[0].age % 15u);
    solid_mode = 0;

    /* Use the actual 8x8 Jolt box, 2.26px/tick speed, 32px-wide pipe, and
     * SMB floor/pipe rows. Small point-like fixtures can conceal a corner
     * deadlock where the body reaches the top edge but never clears the wall
     * far enough to begin the across-pipe leg. */
    smash64_actions_clear();
    commands.events[0] = spawn(10, FOREIGN_ACTION_FOLLOW_SURFACES |
                                   FOREIGN_ACTION_SURFACE_SPEED);
    commands.events[0].offset_y = 70.0;
    commands.events[0].velocity_x = 28.284271;
    commands.events[0].velocity_y = -28.284271;
    commands.events[0].source_joint = 11;
    commands.events[0].surface_velocity = 55.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    large_perimeter_mode = 1;
    smash64_actions_apply_commands(&commands, 124.8, 208.0, 1.0, 0.08,
                                   resolve_attachment);
    {
        int i, saw_left_wall = 0, saw_top = 0, saw_right_wall = 0;
        for (i = 0; i < 120; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal == SMASH64_ACTION_SURFACE_RIGHT &&
                slots[0].vy < 0.0)
                saw_left_wall = 1;
            if (saw_left_wall &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN &&
                slots[0].vx > 0.0)
                saw_top = 1;
            if (saw_top &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_LEFT &&
                slots[0].vy > 0.0)
                saw_right_wall = 1;
            if (saw_right_wall &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN &&
                slots[0].vx > 0.0)
                break;
        }
        CHECK(saw_left_wall && saw_top && saw_right_wall);
        CHECK(i < 120);
    }

    /* The same perimeter must mirror exactly when Pikachu faces left. */
    smash64_actions_clear();
    commands.events[0] = spawn(11, FOREIGN_ACTION_FOLLOW_SURFACES |
                                   FOREIGN_ACTION_SURFACE_SPEED);
    commands.events[0].offset_y = 70.0;
    commands.events[0].velocity_x = 28.284271;
    commands.events[0].velocity_y = -28.284271;
    commands.events[0].source_joint = 11;
    commands.events[0].surface_velocity = 55.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    smash64_actions_apply_commands(&commands, 300.0, 208.0, -1.0, 0.08,
                                   resolve_attachment);
    {
        int i, saw_right_wall = 0, saw_top = 0, saw_left_wall = 0;
        for (i = 0; i < 140; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal == SMASH64_ACTION_SURFACE_LEFT &&
                slots[0].vy < 0.0)
                saw_right_wall = 1;
            if (saw_right_wall &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN &&
                slots[0].vx < 0.0)
                saw_top = 1;
            if (saw_top &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_RIGHT &&
                slots[0].vy > 0.0)
                saw_left_wall = 1;
            if (saw_left_wall &&
                slots[0].surface_normal == SMASH64_ACTION_SURFACE_DOWN &&
                slots[0].vx < 0.0)
                break;
        }
        CHECK(saw_right_wall && saw_top && saw_left_wall);
        CHECK(i < 140);
    }

    /* Canonicalize a mid-wall compact record, then prove its future path is
     * deterministic rather than merely restoring an active bit. */
    smash64_actions_clear();
    commands.events[0] = spawn(12, FOREIGN_ACTION_FOLLOW_SURFACES |
                                   FOREIGN_ACTION_SURFACE_SPEED);
    commands.events[0].offset_y = 70.0;
    commands.events[0].velocity_x = 28.284271;
    commands.events[0].velocity_y = -28.284271;
    commands.events[0].source_joint = 11;
    commands.events[0].surface_velocity = 55.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    smash64_actions_apply_commands(&commands, 124.8, 208.0, 1.0, 0.08,
                                   resolve_attachment);
    {
        Smash64ActionSlot future_a, future_b;
        int i;
        for (i = 0; i < 60; ++i) {
            smash64_actions_step(&host);
            CHECK(smash64_actions_snapshot(slots, 8) == 1);
            if (slots[0].surface_normal == SMASH64_ACTION_SURFACE_RIGHT &&
                slots[0].vy < 0.0)
                break;
        }
        CHECK(i < 60);
        compact_len = smash64_actions_serialize(compact, sizeof(compact));
        CHECK(compact_len > 0 && compact_len <= 512);
        CHECK(smash64_actions_deserialize(compact, compact_len));
        for (i = 0; i < 16; ++i) smash64_actions_step(&host);
        CHECK(smash64_actions_snapshot(&future_a, 1) == 1);
        CHECK(smash64_actions_deserialize(compact, compact_len));
        for (i = 0; i < 16; ++i) smash64_actions_step(&host);
        CHECK(smash64_actions_snapshot(&future_b, 1) == 1);
        CHECK(future_a.x == future_b.x && future_a.y == future_b.y);
        CHECK(future_a.vx == future_b.vx && future_a.vy == future_b.vy);
        CHECK(future_a.surface_normal == future_b.surface_normal);
        CHECK(future_a.age == future_b.age);
    }
    large_perimeter_mode = 0;

    /* Smash's ground Jolt has floor and left/right-wall line states, but no
     * ceiling state. Descending past the unsupported bottom of a floating
     * wall must expire instead of crawling underneath it. */
    smash64_actions_clear();
    commands.events[0] = spawn(13, FOREIGN_ACTION_FOLLOW_SURFACES);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 0.0;
    commands.events[0].velocity_y = -40.0;
    commands.events[0].width = 100.0;
    commands.events[0].height = 100.0;
    commands.events[0].lifetime_ticks = 100;
    smash64_actions_apply_commands(&commands, 228.8, 184.0, 1.0, 0.08,
                                   NULL);
    smash64_actions_save(&saved);
    saved.slots[0].x = 228.8;
    saved.slots[0].y = 184.0;
    saved.slots[0].vx = 0.0;
    saved.slots[0].vy = 3.2;
    saved.slots[0].surface_normal = SMASH64_ACTION_SURFACE_LEFT;
    saved.slots[0].age = 1;
    CHECK(smash64_actions_restore(&saved));
    floating_wall_mode = 1;
    {
        int i, count = 1;
        for (i = 0; i < 20 && count == 1; ++i) {
            smash64_actions_step(&host);
            count = smash64_actions_snapshot(slots, 8);
        }
        CHECK(count == 0);
        smash64_actions_drain_feedback(&feedback);
        CHECK(feedback.count == 1);
        CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);
    }
    floating_wall_mode = 0;

    smash64_actions_clear();
    commands.events[0] = spawn(6, FOREIGN_ACTION_SELF_CONTACT);
    commands.events[0].offset_y = 0.0;
    commands.events[0].velocity_x = 500.0;
    commands.events[0].velocity_y = 0.0;
    commands.events[0].width = 1.0;
    commands.events[0].height = 1.0;
    host.fighter_left = 70.0;
    host.fighter_right = 71.0;
    host.fighter_top = 0.0;
    host.fighter_bottom = 64.0;
    smash64_actions_apply_commands(&commands, 50.0, 80.0, 1.0, 0.08, NULL);
    smash64_actions_step(&host);
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_SELF);

    /* A downward self-contact Thunder body is allowed to enter from above
     * the HUD, but the same geometry without SELF_CONTACT remains blocked. */
    smash64_actions_clear();
    memset(&commands, 0, sizeof(commands));
    commands.count = 1;
    commands.events[0] = spawn(7, FOREIGN_ACTION_SELF_CONTACT);
    commands.events[0].velocity_x = 0.0;
    commands.events[0].velocity_y = -450.0;
    commands.events[0].width = 300.0;
    commands.events[0].height = 300.0;
    hud_boundary_mode = 1;
    host.fighter_left = 200.0;
    host.fighter_right = 216.0;
    host.fighter_top = 176.0;
    host.fighter_bottom = 208.0;
    smash64_actions_apply_commands(&commands, 50.0, 208.0, 1.0, 0.08,
                                   NULL);
    smash64_actions_step(&host); /* authored spawn frame */
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].y > 32.0);

    smash64_actions_clear();
    commands.events[0].instance_id = 8;
    commands.events[0].flags = 0;
    smash64_actions_apply_commands(&commands, 50.0, 40.0, 1.0, 0.08, NULL);
    smash64_actions_step(&host);
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_EXPIRED);
    hud_boundary_mode = 0;

    /* Natural Thunder path: joint11 supplies X, stage-top minus 500 supplies
     * Y, the 40-tick head enters through the HUD, and source X/Y+225 strict
     * bounds generate SELF feedback before terrain destroys the action. */
    smash64_actions_clear();
    memset(&commands, 0, sizeof(commands));
    commands.count = 1;
    commands.events[0] = spawn(
        15, FOREIGN_ACTION_HOSTILE | FOREIGN_ACTION_SELF_CONTACT |
                FOREIGN_ACTION_DESTROY_ON_SOLID |
                FOREIGN_ACTION_PERSIST_AFTER_TARGET);
    commands.events[0].kind = PIKACHU_PROJECTILE_THUNDER;
    commands.events[0].source_joint = 11;
    commands.events[0].offset_y = 500.0;
    commands.events[0].velocity_x = 0.0;
    commands.events[0].velocity_y = -450.0;
    commands.events[0].width = 160.0;
    commands.events[0].height = 300.0;
    commands.events[0].lifetime_ticks = 40;
    host.fighter_left = 42.0;
    host.fighter_right = 58.0;
    host.fighter_top = 32.0;
    host.fighter_bottom = 64.0;
    host.self_contact = source_self_contact;
    hud_boundary_mode = 1;
    target_box = 1;
    target_left = 49.0;
    target_right = 51.0;
    target_top = -9.0;
    target_bottom = -7.0;
    smash64_actions_apply_commands(&commands, 50.0, 64.0, 1.0, 0.08,
                                   resolve_attachment);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].x == 50.0 && slots[0].y == -8.0);
    CHECK(slots[0].source_joint == 11 && slots[0].lifetime == 40);
    smash64_actions_step(&host); /* target hit does not consume Thunder */
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 15);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_TARGET);
    smash64_actions_step(&host); /* descending head reaches self bounds */
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(!(slots[0].flags & FOREIGN_ACTION_HOSTILE));
    CHECK(!(slots[0].flags & FOREIGN_ACTION_SELF_CONTACT));
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 15);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_SELF);
    host.self_contact = NULL;
    hud_boundary_mode = 0;

    commands.events[0].command = FOREIGN_ACTION_CANCEL_ALL;
    smash64_actions_apply_commands(&commands, 0, 0, 1, .08, NULL);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);

    if (failures) return 1;
    puts("smash64_actions_test: PASS");
    return 0;
}
