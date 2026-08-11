/* Pikachu's publishable ForeignController bridge. Game-specific collision,
 * rendering, and audio mapping intentionally remain outside this file. */
#include "pikachu.h"

#include "foreign_controller.h"

#include <limits.h>
#include <string.h>

/* The sole mutable fighter instance behind the generic controller ABI. */
static PikachuFighter s_fighter;

static int pk_uses_generic_locomotion_clock(int state)
{
    switch (state) {
    case PK_GROUND_WAIT:
    case PK_WALK:
    case PK_DASH:
    case PK_RUN:
    case PK_JUMP_GROUND:
    case PK_JUMP_AERIAL:
    case PK_AIR_FALL:
    case PK_AIR_FALL_AERIAL:
        return 1;
    default:
        return 0;
    }
}

static int pk_thunder_kinetic_pair(int before, int after)
{
    return (before == PK_THUNDER_START &&
            after == PK_THUNDER_AIR_START) ||
           (before == PK_THUNDER_AIR_START &&
            after == PK_THUNDER_START) ||
           (before == PK_THUNDER_LOOP &&
            after == PK_THUNDER_AIR_LOOP) ||
           (before == PK_THUNDER_AIR_LOOP &&
            after == PK_THUNDER_LOOP) ||
           (before == PK_THUNDER_SELF_HIT &&
            after == PK_THUNDER_AIR_SELF_HIT) ||
           (before == PK_THUNDER_AIR_SELF_HIT &&
            after == PK_THUNDER_SELF_HIT) ||
           (before == PK_THUNDER_END &&
            after == PK_THUNDER_AIR_END) ||
           (before == PK_THUNDER_AIR_END &&
            after == PK_THUNDER_END);
}

static unsigned pk_public_action_frame(const PikachuFighter *fighter)
{
    if (fighter->state == PK_QUICK_ATTACK_START ||
        fighter->state == PK_QUICK_ATTACK_ZIP1 ||
        fighter->state == PK_QUICK_ATTACK_ZIP2 ||
        fighter->state == PK_QUICK_ATTACK_GROUND_START ||
        fighter->state == PK_QUICK_ATTACK_GROUND_ZIP1 ||
        fighter->state == PK_QUICK_ATTACK_GROUND_ZIP2)
        return 0u;
    if (fighter->state == PK_QUICK_ATTACK_WINDOW ||
        fighter->state == PK_QUICK_ATTACK_RECOVERY ||
        fighter->state == PK_QUICK_ATTACK_GROUND_WINDOW ||
        fighter->state == PK_QUICK_ATTACK_GROUND_RECOVERY)
        return fighter->quick_end_frame;
    return fighter->action_frame;
}

static void push_audio(ForeignMoveResult *out, uint32_t cue)
{
    ForeignAudioEvent *event;
    if (out->audio.count >= FOREIGN_AUDIO_EVENT_CAPACITY) return;
    event = &out->audio.events[out->audio.count++];
    event->cue = cue;
    event->gain_percent = 100;
}

static void pk_reset(ForeignState *state)
{
    pikachu_reset(&s_fighter);
    state->state = s_fighter.state;
    state->state_frame = 0;
    state->vx = state->vy = 0.0;
    state->facing = 1.0f;
    state->grounded = 1;
    state->fast_fall = 0;
    state->air_cause = FOREIGN_AIR_NONE;
    state->jump_phase = FOREIGN_JUMP_NONE;
}

static void pk_tick(ForeignState *state, const ForeignInput *input,
                    ForeignMoveResult *out)
{
    PikachuInputRaw raw;
    const ForeignMoveState previous_state = state->state;
    const unsigned previous_frame = state->state_frame;
    int was_grounded = s_fighter.grounded;
    memset(&raw, 0, sizeof(raw));
    raw.stick_x = (int)(input->stick_x * 80.0f);
    raw.stick_y = (int)(input->stick_y * 80.0f);
    raw.jump_pressed = input->jump_pressed;
    raw.jump_held = input->jump_held;
    raw.attack_pressed = input->attack_pressed;
    raw.special_pressed = input->special_pressed;
    raw.down_pressed = input->down_pressed;
    /* Host floor contact is resolved after this tick. Importing its new
     * grounded=true bit here would erase the private airborne edge before
     * pikachu_resolve() can select Landing/AttackAirLanding. Ledge loss is
     * different: the controller must switch to air kinetics before producing
     * this tick's motion, so true->false remains immediate. Same-kinetic
     * synchronization is unchanged. */
    if (!state->grounded || s_fighter.grounded)
        s_fighter.grounded = state->grounded;
    pikachu_tick(&s_fighter, &raw, &s_fighter.last_motion);
    if ((s_fighter.state == PK_QUICK_ATTACK_START ||
         s_fighter.state == PK_QUICK_ATTACK_GROUND_START) &&
        previous_state != s_fighter.state) {
        /* Locomotion's private action clock owns transitions, while the
         * engine ForeignState owns the exact visible cycle. Motion -1 needs
         * the latter, including its save/load-stable Run/Wait/Fall phase. */
        s_fighter.quick_entry_state = previous_state;
        s_fighter.quick_entry_frame = previous_frame;
    }

    out->requested_dx = s_fighter.last_motion.requested_dx;
    out->requested_dy = s_fighter.last_motion.requested_dy;
    out->vx = s_fighter.vel_x;
    out->vy = s_fighter.vel_y;
    out->state = s_fighter.state;
    out->force_airborne = s_fighter.last_motion.force_airborne ||
                          (was_grounded && !s_fighter.grounded);
    out->attack.offset_x = s_fighter.last_motion.attack.offset_x;
    out->attack.offset_y = s_fighter.last_motion.attack.offset_y;
    out->attack.width = s_fighter.last_motion.attack.width;
    out->attack.height = s_fighter.last_motion.attack.height;
    out->attack.damage = s_fighter.last_motion.attack.damage;
    out->attack.flags = s_fighter.last_motion.attack.break_blocks ? FOREIGN_ATTACK_BREAK_BLOCKS : 0;
    out->attack.active = s_fighter.last_motion.attack.active;

    {
        const uint32_t events = s_fighter.last_motion.events;
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N))
            push_audio(out, PIKACHU_AUDIO_SPECIAL_N);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI))
            push_audio(out, PIKACHU_AUDIO_SPECIAL_HI);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_LW))
            push_audio(out, PIKACHU_AUDIO_SPECIAL_LW);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_S))
            push_audio(out, PIKACHU_AUDIO_LIGHT_S);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M))
            push_audio(out, PIKACHU_AUDIO_LIGHT_M);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_L))
            push_audio(out, PIKACHU_AUDIO_LIGHT_L);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1))
            push_audio(out, PIKACHU_AUDIO_ELECTRIC_1);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_2))
            push_audio(out, PIKACHU_AUDIO_ELECTRIC_2);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_3))
            push_audio(out, PIKACHU_AUDIO_ELECTRIC_3);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_5))
            push_audio(out, PIKACHU_AUDIO_ELECTRIC_5);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_QUICK_ATTACK_START))
            push_audio(out, PIKACHU_AUDIO_QUICK_ATTACK_START);
        /* FGM_SWING_PULSE is route 219, a distinct unresolved program. Do
         * not disguise it as one of the three finite light-swing clips. */
        /* ElectricLoop is not a finite source command. The host starts its
         * one persistent voice from the spawned Jolt action and reconciles it
         * against that action's lifetime, including savestate reloads. */
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_THUNDER)) {
            push_audio(out, PIKACHU_AUDIO_THUNDER);
        }
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LANDING))
            push_audio(out, PIKACHU_AUDIO_LANDING);
        if (events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_DEAD_SLAM))
            push_audio(out, PIKACHU_AUDIO_DEAD_SLAM);
    }

    if (s_fighter.last_motion.events &
        PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN)) {
        ForeignActionEvent *event = &out->actions.events[out->actions.count++];
        const int ground_jolt = s_fighter.state == PK_THUNDER_JOLT_GROUND;
        memset(event, 0, sizeof(*event));
        event->instance_id = s_fighter.projectile.persistent_action_id;
        event->kind = PIKACHU_PROJECTILE_JOLT;
        event->command = FOREIGN_ACTION_SPAWN;
        event->flags = FOREIGN_ACTION_HOSTILE |
                       FOREIGN_ACTION_FOLLOW_SURFACES |
                       FOREIGN_ACTION_SURFACE_SPEED |
                       FOREIGN_ACTION_ORIENTED_VELOCITY;
        /* Air Jolt can use source joint 11 directly. In grounded Wait/Run
         * poses, the current host joint-11 projection resolves behind the
         * rendered Pikachu body; use an equivalent front-of-body root offset
         * until the full effect hierarchy/joint-space seam is replaced. */
        event->source_joint = ground_jolt ? 0u : 11u;
        event->offset_x = ground_jolt ? -240.0 : 0.0;
        event->offset_y = 0.0;
        event->velocity_x = ground_jolt
            ? (s_fighter.projectile.speed_x < 0.0 ? -55.0 : 55.0)
            : s_fighter.projectile.speed_x;
        event->velocity_y = ground_jolt ? 0.0 : s_fighter.projectile.speed_y;
        event->surface_velocity = 55.0;
        event->width = 100.0;
        event->height = 100.0;
        event->damage = 10;
        event->lifetime_ticks = 100;
    }
    if (s_fighter.last_motion.events &
        PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN)) {
        ForeignActionEvent *event = &out->actions.events[out->actions.count++];
        memset(event, 0, sizeof(*event));
        event->instance_id = s_fighter.projectile.persistent_action_id;
        event->kind = PIKACHU_PROJECTILE_THUNDER;
        event->command = FOREIGN_ACTION_SPAWN;
        event->flags = FOREIGN_ACTION_HOSTILE | FOREIGN_ACTION_SELF_CONTACT |
                       FOREIGN_ACTION_DESTROY_ON_SOLID |
                       FOREIGN_ACTION_PERSIST_AFTER_TARGET;
        /* Source takes X from joint 11, then replaces Y with stage top minus
         * its authored 500-unit offset. The SMB host owns that top boundary. */
        event->source_joint = 11;
        event->offset_y = 500.0;
        event->velocity_y = -450.0;
        event->width = 160.0;
        event->height = 300.0;
        event->damage = 12;
        event->lifetime_ticks = 40;
    }

    state->state = s_fighter.state;
    if (pk_uses_generic_locomotion_clock(s_fighter.state)) {
        /* Keep presentation time in the generic state so locomotion poses do
         * not freeze. The private timer separately owns source transitions
         * such as Dash-to-Run and Jump-to-Fall. ForeignState is already saved
         * by the engine-owned active-controller record, so the visible cycle
         * also resumes exactly. */
        state->state_frame = previous_state == s_fighter.state
            ? (previous_frame == UINT_MAX ? 0u : previous_frame + 1u)
            : 0u;
    } else {
        state->state_frame = s_fighter.last_motion.action_frame;
    }
    state->facing = (float)s_fighter.lr;
    state->grounded = s_fighter.grounded;
    state->fast_fall = s_fighter.fast_fall;
    state->vx = out->vx;
    state->vy = out->vy;
    state->jump_phase = FOREIGN_JUMP_NONE;
}

static void pk_resolve(ForeignState *state, const ForeignCollisionResult *hit)
{
    PikachuCollision collision;
    int private_state_before;
    unsigned private_frame_before;
    uint32_t i;
    memset(&collision, 0, sizeof(collision));
    collision.actual_dx = hit->actual_dx;
    collision.actual_dy = hit->actual_dy;
    collision.grounded = hit->grounded;
    collision.hit_ceiling = hit->hit_ceiling;
    collision.hit_floor = hit->hit_floor;
    collision.hit_wall = hit->hit_wall;
    for (i = 0; i < hit->action_feedback.count; ++i) {
        const ForeignActionFeedbackEvent *event =
            &hit->action_feedback.events[i];
        if (event->flags & FOREIGN_ACTION_HIT_SELF)
            pikachu_note_thunder_self_contact(&s_fighter);
        if (event->flags & FOREIGN_ACTION_EXPIRED)
            pikachu_note_projectile_finished(&s_fighter,
                                             event->instance_id);
        else if ((event->flags & FOREIGN_ACTION_HIT_TARGET) &&
                 s_fighter.projectile.kind != PIKACHU_PROJECTILE_THUNDER)
            pikachu_note_projectile_finished(&s_fighter,
                                             event->instance_id);
    }
    private_state_before = s_fighter.state;
    private_frame_before = s_fighter.action_frame;
    pikachu_resolve(&s_fighter, &collision);
    state->x = s_fighter.pos_x;
    state->y = s_fighter.pos_y;
    state->vx = s_fighter.vel_x;
    state->vy = s_fighter.vel_y;
    state->grounded = s_fighter.grounded;
    state->fast_fall = s_fighter.fast_fall;
    state->state = s_fighter.state;
    /* Resolve may change both status and its local motion clock (landing,
     * Thunder ground/air map conversion). Publish them atomically so the
     * renderer never observes a new status with the prior status' frame. */
    if (!pk_thunder_kinetic_pair(private_state_before, s_fighter.state) &&
        (s_fighter.state != private_state_before ||
         s_fighter.action_frame != private_frame_before))
        state->state_frame = pk_public_action_frame(&s_fighter);
}

static const char *pk_state_name(ForeignMoveState state)
{
    return pikachu_state_name(state);
}

static int pk_private_get(const ForeignState *state, uint8_t *buf, int cap)
{
    (void)state;
    return pikachu_serialize(&s_fighter, buf, cap);
}

static int pk_private_set(ForeignState *state, const uint8_t *buf, int len)
{
    PikachuFighter candidate;
    (void)state;
    if (!pikachu_deserialize(&candidate, buf, len)) return 0;
    s_fighter = candidate;
    return 1;
}

static const ForeignController kPikachu = {
    SMASH64_PIKACHU_ID, "Pikachu", pk_reset, pk_tick, pk_resolve, pk_state_name
};

int smash64_pikachu_register(void)
{
    int ok = nes_foreign_register(&kPikachu);
    ok &= nes_foreign_register_private_state(SMASH64_PIKACHU_ID,
                                             pk_private_get, pk_private_set);
    return ok;
}

const PikachuMotion *smash64_pikachu_last_motion(void) { return &s_fighter.last_motion; }
void smash64_pikachu_thunder_self_contact(void) { pikachu_note_thunder_self_contact(&s_fighter); }
int smash64_pikachu_quick_entry_pose(int active_state, int *entry_state,
                                     unsigned *entry_frame)
{
    if (!entry_state || !entry_frame || active_state != s_fighter.state ||
        (active_state != PK_QUICK_ATTACK_START &&
         active_state != PK_QUICK_ATTACK_GROUND_START))
        return 0;
    *entry_state = s_fighter.quick_entry_state;
    *entry_frame = s_fighter.quick_entry_frame;
    return 1;
}
