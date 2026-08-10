#include "game_smash64_actions.h"

#include <stdio.h>
#include <string.h>

static int failures;
static int target_hits;
static int solid_mode;

#define CHECK(x) do { if (!(x)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); \
    ++failures; \
} } while (0)

static int solid_at(double x, double y)
{
    (void)x;
    return solid_mode && y >= 100.0;
}

static int defeat_target(double l, double r, double t, double b)
{
    (void)l; (void)r; (void)t; (void)b;
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
    smash64_actions_apply_commands(&commands, 50.0, 120.0, 1.0, 0.08);
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    CHECK(slots[0].x == 50.0);
    CHECK(slots[0].y == 112.0);
    target_hits = 1;
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].instance_id == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_TARGET);

    commands.events[0] = spawn(2, FOREIGN_ACTION_SELF_CONTACT);
    smash64_actions_apply_commands(&commands, 8.0, 120.0, 1.0, 0.08);
    smash64_actions_step(&host);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);
    smash64_actions_drain_feedback(&feedback);
    CHECK(feedback.count == 1);
    CHECK(feedback.events[0].flags & FOREIGN_ACTION_HIT_SELF);

    commands.events[0] = spawn(3, 0);
    smash64_actions_apply_commands(&commands, 50.0, 120.0, 1.0, 0.08);
    smash64_actions_save(&saved);
    smash64_actions_clear();
    CHECK(smash64_actions_restore(&saved));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);
    bad = saved;
    bad.slots[0].width = -1.0;
    CHECK(!smash64_actions_restore(&bad));
    CHECK(smash64_actions_snapshot(slots, 8) == 1);

    commands.events[0].command = FOREIGN_ACTION_CANCEL_ALL;
    smash64_actions_apply_commands(&commands, 0, 0, 1, .08);
    CHECK(smash64_actions_snapshot(slots, 8) == 0);

    if (failures) return 1;
    puts("smash64_actions_test: PASS");
    return 0;
}
