/*
 * Samus gameplay/presentation layer for SMB1.
 *
 * Movement stays behind ForeignController; this file owns Metroid-specific
 * energy, weapons, projectiles, enemy freezing, pickups and owner-ROM tiles.
 * The implementation is clean-room and consumes graphics only from the
 * launcher's already verified Metroid ROM path.
 */
#include "game_samus.h"
#include "game_samus_audio.h"

#include "game_smash64.h"
#include "mods/metroid/samus_controller.h"

#include "foreign_controller.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "nes_runtime.h"
#include "generated/super-mario-bros_full_decls.h"

#include <SDL.h>

#include <stdio.h>
#include <string.h>

#define SAMUS_CONTACT_HOOK_ID "super-mario-bros.metroid.player-enemy-contact"
#define SAMUS_POWERUP_HOOK_ID "super-mario-bros.metroid.powerup"
#define SAMUS_INJURY_HOOK_ID "super-mario-bros.metroid.injury"
#define SMB1_PLAYER_ENEMY_COLLISION_ADDR 0xD853
#define SMB1_POWERUP_COLLISION_ADDR 0xD800
#define SMB1_INJURY_ADDR 0xD92C

#define PAD_A      0x80
#define PAD_B      0x40
#define PAD_SELECT 0x20
#define PAD_UP     0x08

#define SAMUS_MAX_ENERGY 99
#define SAMUS_INVULN_FRAMES 60
#define SAMUS_FREEZE_FRAMES 300
#define SAMUS_CHR_BYTES 1968
#define SAMUS_CHR_PRG_OFFSET 0x18000L

typedef struct SamusShot {
    int active; /* 0=free, 1=flying, 2=impact animation */
    int missile;
    int vertical;
    int age;
    double x;
    double y;
    double dx;
    double dy;
} SamusShot;

typedef struct SamusBomb {
    int active;
    int timer;
    double x;
    double y;
} SamusBomb;

typedef struct FrozenEnemy {
    unsigned timer;
    uint8_t id;
    uint8_t page, x, y, yhi;
    uint8_t x_speed, y_speed;
    uint8_t boss_hits;
} FrozenEnemy;

static int s_enabled;
static int s_energy = SAMUS_MAX_ENERGY;
static int s_missile_mode;
static unsigned s_invuln;
static int s_death_latched;
static int s_force_native_injury;
static uint8_t s_prev_buttons;
static uint8_t s_fire_pose;
static uint64_t s_present_frame;
static int s_prev_move_state;
static uint8_t s_chr[SAMUS_CHR_BYTES];
static int s_assets_ready;
static SamusShot s_shots[3];
static SamusBomb s_bombs[3];
static FrozenEnemy s_frozen[5];
/* SMB marks pipe sprites with OAM priority bit $20. Samus is composited after
 * the native PPU frame, so reproduce that priority explicitly while drawing
 * her; otherwise the completed pipe background can never cover her. */
static int s_draw_behind_background;

#define SAMUS_FIRE_POSE_TICKS 0x7Fu
#define SAMUS_FIRE_POSE_UP    0x80u

static int overlap(double a0, double a1, double b0, double b1)
{
    return a0 < b1 && b0 < a1;
}

static int world_player_x(void)
{
    return ((int)g_ram[Player_PageLoc] << 8) | g_ram[Player_X_Position];
}

static int screen_left_x(void)
{
    return ((int)g_ram[ScreenLeft_PageLoc] << 8) | g_ram[ScreenLeft_X_Pos];
}

static void enemy_hurtbox(int slot, double *left, double *right,
                          double *top, double *bottom)
{
    int x = ((int)g_ram[Enemy_PageLoc + slot] << 8) |
            g_ram[Enemy_X_Position + slot];
    int y = g_ram[Enemy_Y_Position + slot];
    if (g_ram[Enemy_ID + slot] == Bowser) {
        *left = x + 1; *right = x + 31;
        *top = y + 1; *bottom = y + 31;
    } else {
        /* SMB's generic 16x24 object box includes generous blank margins.
         * Metroid projectiles test the visible body, not that whole cell. */
        *left = x + 2; *right = x + 14;
        *top = y + 3; *bottom = y + 21;
    }
}

static void samus_contact_box(double *left, double *right,
                              double *top, double *bottom)
{
    int x = world_player_x();
    int y = g_ram[Player_Y_Position];
    if (metroid_samus_is_morphed()) {
        *left = x + 3; *right = x + 13;
        *top = y + 19; *bottom = y + 30;
    } else if (metroid_samus_is_spinning()) {
        *left = x + 2; *right = x + 14;
        *top = y + 7; *bottom = y + 25;
    } else {
        *left = x + 3; *right = x + 13;
        *top = y + 3; *bottom = y + 29;
    }
}

static int samus_overlaps_enemy(int slot)
{
    double sl, sr, st, sb, el, er, et, eb;
    samus_contact_box(&sl, &sr, &st, &sb);
    enemy_hurtbox(slot, &el, &er, &et, &eb);
    return overlap(sl, sr, el, er) && overlap(st, sb, et, eb);
}

static int load_owner_tiles(const char *rom_path)
{
    SDL_RWops *file;
    unsigned char header[16];
    Sint64 size;
    long base = 0;
    if (!rom_path || !*rom_path) return 0;
    file = SDL_RWFromFile(rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    if (size == 131088) {
        if (SDL_RWread(file, header, 1, sizeof(header)) != sizeof(header) ||
            memcmp(header, "NES\x1a", 4) != 0 || (header[6] & 0x04) != 0 ||
            header[4] != 8 || header[5] != 0) {
            SDL_RWclose(file);
            return 0;
        }
        base = 16;
    } else if (size != 131072) {
        SDL_RWclose(file);
        return 0;
    }
    if (SDL_RWseek(file, (Sint64)base + SAMUS_CHR_PRG_OFFSET, RW_SEEK_SET) < 0 ||
        SDL_RWread(file, s_chr, 1, sizeof(s_chr)) != sizeof(s_chr)) {
        SDL_RWclose(file);
        return 0;
    }
    SDL_RWclose(file);
    return 1;
}

static void reset_runtime(void)
{
    s_energy = SAMUS_MAX_ENERGY;
    s_missile_mode = 0;
    s_invuln = 0;
    s_death_latched = 0;
    s_force_native_injury = 0;
    s_prev_buttons = 0;
    s_fire_pose = 0;
    s_present_frame = 0;
    s_prev_move_state = -1;
    memset(s_shots, 0, sizeof(s_shots));
    memset(s_bombs, 0, sizeof(s_bombs));
    memset(s_frozen, 0, sizeof(s_frozen));
}

int game_samus_set_enabled(int enabled, const char *owner_rom_path)
{
    s_enabled = 0;
    s_assets_ready = 0;
    nes_mod_set_function_hook_enabled(SAMUS_CONTACT_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SAMUS_POWERUP_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SAMUS_INJURY_HOOK_ID, 0);
    reset_runtime();
    game_samus_audio_shutdown();
    if (!enabled) return 1;
    if (!load_owner_tiles(owner_rom_path)) {
        fprintf(stderr, "[Metroid] Could not extract Samus tiles from the "
                        "verified owner ROM.\n");
        return 0;
    }
    if (!game_samus_audio_prepare(owner_rom_path)) {
        fprintf(stderr, "[Metroid] Could not build sound effects from the "
                        "verified owner ROM.\n");
        return 0;
    }
    if (!game_smash64_set_mod_enabled(1, METROID_SAMUS_CONTROLLER_ID) ||
        !nes_mod_set_function_hook_enabled(SAMUS_CONTACT_HOOK_ID, 1) ||
        !nes_mod_set_function_hook_enabled(SAMUS_POWERUP_HOOK_ID, 1) ||
        !nes_mod_set_function_hook_enabled(SAMUS_INJURY_HOOK_ID, 1)) {
        game_smash64_set_mod_enabled(0, NULL);
        game_samus_audio_shutdown();
        return 0;
    }
    s_assets_ready = 1;
    s_enabled = 1;
    printf("[Metroid] Samus armed with Morph Ball, Bombs, High Jump, Varia, "
           "Long/Wave/Ice Beam, Screw Attack and infinite missiles.\n");
    return 1;
}

int game_samus_active(void)
{
    return s_enabled && game_smash64_samus_selected();
}

static void freeze_enemy(int slot, unsigned frames)
{
    FrozenEnemy *f = &s_frozen[slot];
    f->timer = frames;
    f->id = g_ram[Enemy_ID + slot];
    f->page = g_ram[Enemy_PageLoc + slot];
    f->x = g_ram[Enemy_X_Position + slot];
    f->y = g_ram[Enemy_Y_Position + slot];
    f->yhi = g_ram[Enemy_Y_HighPos + slot];
    f->x_speed = g_ram[Enemy_X_Speed + slot];
    f->y_speed = g_ram[Enemy_Y_Speed + slot];
}

static int defeat_slot(int slot)
{
    int ex = ((int)g_ram[Enemy_PageLoc + slot] << 8) |
             g_ram[Enemy_X_Position + slot];
    int ey = g_ram[Enemy_Y_Position + slot];
    uint8_t square1 = g_ram[Square1SoundQueue];
    int hits = game_smash64_defeat_enemies(ex, ex + 16, ey, ey + 24, 1);
    /* ShellOrBlockDefeat always queues SMB's $08 enemy-smack effect. Samus
     * supplies Metroid's EnemyHit cue below, and playing both produces a harsh
     * detuned stack, most obvious under the sustained Screw Attack noise. Keep
     * the native state/score/floatey-number consequences, but restore whatever
     * unrelated Square 1 request existed before the native helper. */
    g_ram[Square1SoundQueue] = square1;
    return hits;
}

static void star_defeat_slot(int slot)
{
    if (g_ram[Enemy_State + slot] & 0x20) return;
    if (g_ram[Enemy_ID + slot] == Bowser) {
        g_ram[BowserHitPoints] = 0;
        g_ram[Enemy_State + slot] = 0x20;
        g_ram[Enemy_X_Speed + slot] = 0;
        g_ram[Enemy_Y_Speed + slot] = 0xFE;
        s_frozen[slot].timer = 0;
    } else {
        /* Star contact is broader than the weapon policy (notably cannon
         * Bullet Bills). Once the tight Samus overlap is proven, invoke the
         * same native defeat consequence SMB uses for invincible contact. */
        CPU6502State save_cpu = g_cpu;
        uint8_t square1 = g_ram[Square1SoundQueue];
        g_cpu.X = (uint8_t)slot;
        RelativeEnemyPosition();
        g_cpu.X = (uint8_t)slot;
        ShellOrBlockDefeat();
        g_ram[Square1SoundQueue] = square1;
        g_cpu = save_cpu;
    }
    game_samus_audio_play(SAMUS_AUDIO_ENEMY_HIT);
}

static void hit_enemy(int slot, int missile, int screw)
{
    uint8_t id = g_ram[Enemy_ID + slot];
    if (id == Bowser) {
        FrozenEnemy *f = &s_frozen[slot];
        if (missile || screw) {
            if (!f->boss_hits) f->boss_hits = 5;
            if (--f->boss_hits == 0) {
                /* HurtBowser's terminal native consequence: enter defeated
                 * fall state and let SMB's bridge/level script proceed. */
                g_ram[BowserHitPoints] = 0;
                g_ram[Enemy_State + slot] = 0x20;
                g_ram[Enemy_X_Speed + slot] = 0;
                g_ram[Enemy_Y_Speed + slot] = 0xFE;
                g_ram[Square2SoundQueue] = 0x80;
                f->timer = 0;
                game_samus_audio_play(SAMUS_AUDIO_ENEMY_HIT);
                return;
            }
        }
        freeze_enemy(slot, missile ? 90u : SAMUS_FREEZE_FRAMES);
    } else if (!defeat_slot(slot)) return;
    game_samus_audio_play(SAMUS_AUDIO_ENEMY_HIT);
}

static int shot_hits_enemy(SamusShot *shot)
{
    for (int slot = 0; slot < 5; ++slot) {
        double el, er, et, eb;
        double half_w = shot->missile ? 6.0 : 2.0;
        double half_h = 2.0;
        if (!g_ram[Enemy_Flag + slot] ||
            g_ram[Enemy_Y_HighPos + slot] != 1 ||
            (g_ram[Enemy_State + slot] & 0x20)) continue;
        enemy_hurtbox(slot, &el, &er, &et, &eb);
        if (overlap(shot->x - half_w, shot->x + half_w, el, er) &&
            overlap(shot->y - half_h, shot->y + half_h, et, eb)) {
            hit_enemy(slot, shot->missile, 0);
            return 1;
        }
    }
    return 0;
}

static void begin_shot_impact(SamusShot *shot)
{
    shot->active = 2;
    shot->age = 0;
    shot->dx = 0.0;
    shot->dy = 0.0;
}

static void spawn_weapon(void)
{
    const ForeignState *state = nes_foreign_state();
    int px = world_player_x();
    int py = g_ram[Player_Y_Position];
    if (!state) return;
    if (metroid_samus_is_morphed()) {
        for (int i = 0; i < 3; ++i) if (!s_bombs[i].active) {
            s_bombs[i].active = 1;
            s_bombs[i].timer = 45;
            s_bombs[i].x = px + 8;
            s_bombs[i].y = py + 28;
            game_samus_audio_play(SAMUS_AUDIO_BOMB_LAUNCH);
            return;
        }
        return;
    }
    if (s_missile_mode)
        for (int i = 0; i < 3; ++i)
            if (s_shots[i].active && s_shots[i].missile) return;
    for (int i = 0; i < 3; ++i) if (!s_shots[i].active) {
        SamusShot *shot = &s_shots[i];
        shot->active = 1;
        shot->missile = s_missile_mode;
        shot->vertical = (g_controller1_buttons & PAD_UP) != 0;
        shot->age = 0;
        shot->x = px + 8 + (shot->vertical ? 0.0 : state->facing * 10.0);
        shot->y = py + 10;
        shot->dx = shot->vertical ? 0.0 : state->facing *
                   (shot->missile ? 4.0 : 3.0);
        shot->dy = shot->vertical ? -(shot->missile ? 4.0 : 3.0) : 0.0;
        s_fire_pose = (uint8_t)(7u | (shot->vertical
                                      ? SAMUS_FIRE_POSE_UP : 0u));
        game_samus_audio_play(shot->missile ? SAMUS_AUDIO_MISSILE_LAUNCH
                                            : SAMUS_AUDIO_WAVE_BEAM);
        return;
    }
}

void game_samus_update_input(uint64_t frame_count)
{
    uint8_t buttons, pressed;
    (void)frame_count;
    if (!game_samus_active()) return;
    buttons = g_controller1_buttons;
    /* Samus owns B completely. Letting SMB also see it starts native Fire
     * Mario's throw timer and fireballs, which changes the hidden player
     * presentation and made the replacement blink on firing. */
    g_controller1_buttons &= (uint8_t)~PAD_B;
    g_ram[Fireball_State] = 0;
    g_ram[Fireball_State + 1] = 0;
    g_ram[FireballCounter] = 0;
    g_ram[FireballThrowingTimer] = 0;
    if (!game_smash64_active()) {
        s_prev_buttons = buttons;
        return;
    }
    pressed = (uint8_t)(buttons & ~s_prev_buttons);
    if (pressed & PAD_SELECT) {
        s_missile_mode ^= 1;
        printf("[Metroid] Weapon: %s\n", s_missile_mode ? "MISSILE" : "BEAM");
    }
    if (pressed & PAD_B) spawn_weapon();
    s_prev_buttons = buttons;
}

static void update_freeze(void)
{
    for (int slot = 0; slot < 5; ++slot) {
        FrozenEnemy *f = &s_frozen[slot];
        if (!f->timer) continue;
        if (!g_ram[Enemy_Flag + slot] || g_ram[Enemy_ID + slot] != f->id) {
            memset(f, 0, sizeof(*f));
            continue;
        }
        g_ram[Enemy_PageLoc + slot] = f->page;
        g_ram[Enemy_X_Position + slot] = f->x;
        g_ram[Enemy_Y_Position + slot] = f->y;
        g_ram[Enemy_Y_HighPos + slot] = f->yhi;
        g_ram[Enemy_X_Speed + slot] = 0;
        g_ram[Enemy_Y_Speed + slot] = 0;
        if (--f->timer == 0) {
            g_ram[Enemy_X_Speed + slot] = f->x_speed;
            g_ram[Enemy_Y_Speed + slot] = f->y_speed;
        }
    }
}

static void update_shots(void)
{
    static const int8_t wave_horizontal[12] = {
        -7, -5, -1, 1, 5, 7, 7, 5, 1, -1, -5, -7
    };
    static const int8_t wave_vertical[12] = {
         7,  5,  1, -1, -5, -7, -7, -5, -1, 1, 5, 7
    };
    for (int i = 0; i < 3; ++i) {
        SamusShot *shot = &s_shots[i];
        if (!shot->active) continue;
        if (shot->active == 2) {
            if (++shot->age > (shot->missile ? 13 : 4)) shot->active = 0;
            continue;
        }
        shot->x += shot->dx;
        shot->y += shot->dy;
        if (!shot->missile) {
            /* Exact 12-step sign/magnitude trajectory from Metroid's
             * WaveBulletTrajectoryHorizontal/Vertical tables. */
            if (shot->vertical)
                shot->x += wave_vertical[shot->age % 12];
            else
                shot->y += wave_horizontal[shot->age % 12];
        }
        if (++shot->age > (shot->missile ? 90 : 60)) {
            shot->active = 0;
            continue;
        }
        if (shot_hits_enemy(shot)) {
            begin_shot_impact(shot);
            continue;
        }
        if (shot->missile &&
            game_smash64_break_bricks(shot->x - 6, shot->x + 6,
                                      shot->y - 2, shot->y + 2))
            begin_shot_impact(shot);
    }
}

static void damage_enemies_in_box(double left, double right,
                                  double top, double bottom, int screw)
{
    for (int slot = 0; slot < 5; ++slot) {
        double el, er, et, eb;
        if (!g_ram[Enemy_Flag + slot] ||
            g_ram[Enemy_Y_HighPos + slot] != 1 ||
            (g_ram[Enemy_State + slot] & 0x20)) continue;
        if (screw && s_frozen[slot].timer) continue;
        enemy_hurtbox(slot, &el, &er, &et, &eb);
        if (overlap(left, right, el, er) &&
            overlap(top, bottom, et, eb))
            hit_enemy(slot, 0, screw);
    }
}

static void update_bombs(void)
{
    for (int i = 0; i < 3; ++i) {
        SamusBomb *bomb = &s_bombs[i];
        if (!bomb->active) continue;
        if (--bomb->timer == 0) {
            int px = world_player_x();
            int py = g_ram[Player_Y_Position];
            damage_enemies_in_box(bomb->x - 10, bomb->x + 10,
                                  bomb->y - 10, bomb->y + 10, 0);
            game_smash64_break_bricks(bomb->x - 10, bomb->x + 10,
                                      bomb->y - 10, bomb->y + 10);
            game_samus_audio_play(SAMUS_AUDIO_BOMB_EXPLODE);
            if (overlap(bomb->x - 10, bomb->x + 10, px + 3, px + 13) &&
                overlap(bomb->y - 10, bomb->y + 10, py + 19, py + 30))
                metroid_samus_bomb_jump();
        }
        if (bomb->timer < -16) bomb->active = 0;
    }
}

void game_samus_update(uint64_t frame_count)
{
    int px, py;
    const ForeignState *move;
    s_present_frame = frame_count;
    if (!game_samus_active()) return;
    if (g_ram[GameEngineSubroutine] == 11) {
        s_death_latched = 1;
    } else if (s_death_latched && g_ram[GameEngineSubroutine] == 8) {
        s_death_latched = 0;
        s_energy = SAMUS_MAX_ENERGY;
        s_invuln = 0;
        memset(s_shots, 0, sizeof(s_shots));
        memset(s_bombs, 0, sizeof(s_bombs));
        memset(s_frozen, 0, sizeof(s_frozen));
    }
    if (!game_smash64_active()) return;
    if (s_invuln) s_invuln--;
    if (s_fire_pose & SAMUS_FIRE_POSE_TICKS) {
        uint8_t ticks = (uint8_t)((s_fire_pose & SAMUS_FIRE_POSE_TICKS) - 1u);
        s_fire_pose = ticks ? (uint8_t)((s_fire_pose & SAMUS_FIRE_POSE_UP) |
                                        ticks) : 0;
    }
    update_freeze();
    update_shots();
    update_bombs();
    move = nes_foreign_state();
    if (move) {
        if (s_prev_move_state >= 0 && move->state != s_prev_move_state) {
            if (move->state == METROID_SAMUS_MORPH &&
                s_prev_move_state != METROID_SAMUS_ROLL &&
                s_prev_move_state != METROID_SAMUS_MORPH)
                game_samus_audio_play(SAMUS_AUDIO_MORPH_BALL);
            if (!move->grounded &&
                (move->state == METROID_SAMUS_JUMP ||
                 move->state == METROID_SAMUS_SPIN)) {
                game_samus_audio_play(SAMUS_AUDIO_JUMP);
                if (move->state == METROID_SAMUS_SPIN)
                    game_samus_audio_play(SAMUS_AUDIO_SCREW_ATTACK);
            }
        }
        if (move->grounded && move->state == METROID_SAMUS_RUN &&
            (move->state_frame % 12u) == 0u)
            game_samus_audio_play(SAMUS_AUDIO_WALK);
        s_prev_move_state = move->state;
    }
    if (metroid_samus_is_spinning()) {
        px = world_player_x();
        py = g_ram[Player_Y_Position];
        damage_enemies_in_box(px + 2, px + 14, py + 7, py + 25, 1);
        game_smash64_break_bricks(px + 2, px + 14, py + 7, py + 25);
    }
}

static int contact_hook(uint16_t addr)
{
    int slot = g_cpu.X;
    int damage;
    CPU6502State save_cpu;
    (void)addr;
    if (!game_samus_active() || slot < 0 || slot >= 5) return 0;
    /* Platforms, power-ups, vines and end-level objects retain their native
     * collision routines. Ordinary enemies, Bowser/flame and cannon Bills
     * are the hostile contact set Samus replaces. */
    if (g_ram[Enemy_ID + slot] >= Fireworks &&
        g_ram[Enemy_ID + slot] != Bowser &&
        g_ram[Enemy_ID + slot] != BulletBill_CannonVar)
        return 0;
    /* This entry hook runs once per candidate enemy, before SMB's broad
     * hidden-Mario bounding-box test. Own the hostile path completely and
     * apply effects only when Samus's visible body actually overlaps it. */
    if (!samus_overlaps_enemy(slot)) return 1;
    /* SMB's Starman timer remains the source of truth, but its consequence is
     * routed through Samus's visible contact box, never a screen-wide test. */
    if (g_ram[StarInvincibleTimer]) {
        star_defeat_slot(slot);
        return 1;
    }
    if (s_frozen[slot].timer) return 1;
    if (metroid_samus_is_spinning()) {
        hit_enemy(slot, 0, 1);
        return 1;
    }
    if (s_invuln) return 1;
    damage = g_ram[Enemy_ID + slot] == Bowser ? 40 :
             g_ram[Enemy_ID + slot] == HammerBro ? 30 : 20;
    damage = (damage + 1) / 2; /* Varia Suit is permanently equipped. */
    s_energy -= damage;
    s_invuln = SAMUS_INVULN_FRAMES;
    game_samus_audio_play(SAMUS_AUDIO_SAMUS_HIT);
    if (s_energy <= 0) {
        s_energy = 0;
        save_cpu = g_cpu;
        g_ram[PlayerStatus] = 0;
        g_ram[InjuryTimer] = 0;
        s_force_native_injury = 1;
        InjurePlayer();
        g_cpu = save_cpu;
    }
    return 1; /* no native stomp and no Mario shrink state */
}

static int injury_hook(uint16_t addr)
{
    (void)addr;
    if (!game_samus_active()) return 0;
    if (s_force_native_injury) {
        s_force_native_injury = 0;
        return 0;
    }
    if (s_invuln) return 1;
    s_energy -= 10; /* generic hazard damage after permanent Varia reduction */
    s_invuln = SAMUS_INVULN_FRAMES;
    game_samus_audio_play(SAMUS_AUDIO_SAMUS_HIT);
    if (s_energy > 0) return 1;
    s_energy = 0;
    g_ram[PlayerStatus] = 0;
    g_ram[InjuryTimer] = 0;
    return 0;
}

static int powerup_hook(uint16_t addr)
{
    uint8_t type;
    CPU6502State save_cpu;
    (void)addr;
    if (!game_samus_active()) return 0;
    type = g_ram[PowerUpType];
    if (type >= 2) return 0; /* star and 1-up keep their native behavior */
    s_energy += type == 0 ? 30 : SAMUS_MAX_ENERGY;
    if (s_energy > SAMUS_MAX_ENERGY) s_energy = SAMUS_MAX_ENERGY;
    /* Preserve SMB's hidden item progression so later blocks can produce a
     * Fire Flower, without entering Mario's size-change presentation. */
    g_ram[PlayerStatus] = type == 0 ? 1 : 2;
    save_cpu = g_cpu;
    EraseEnemyObject();
    g_ram[Square2SoundQueue] = 0x20;
    g_cpu = save_cpu;
    return 1;
}

typedef struct SamusGameSave {
    uint8_t version, missile_mode, death_latched, fire_pose;
    uint16_t energy, invuln;
    SamusShot shots[3];
    SamusBomb bombs[3];
    FrozenEnemy frozen[5];
} SamusGameSave;

static int save_get(uint8_t *buf, int cap)
{
    SamusGameSave save;
    if (!game_samus_active()) return 0;
    if (cap < (int)sizeof(save)) return -1;
    memset(&save, 0, sizeof(save));
    save.version = 1;
    save.missile_mode = (uint8_t)s_missile_mode;
    save.death_latched = (uint8_t)s_death_latched;
    save.fire_pose = s_fire_pose;
    save.energy = (uint16_t)s_energy;
    save.invuln = (uint16_t)s_invuln;
    memcpy(save.shots, s_shots, sizeof(s_shots));
    memcpy(save.bombs, s_bombs, sizeof(s_bombs));
    memcpy(save.frozen, s_frozen, sizeof(s_frozen));
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int save_set(const uint8_t *buf, int len)
{
    SamusGameSave save;
    if (len != (int)sizeof(save)) return 0;
    memcpy(&save, buf, sizeof(save));
    if (save.version != 1) return 0;
    s_missile_mode = save.missile_mode != 0;
    s_death_latched = save.death_latched != 0;
    s_fire_pose = save.fire_pose;
    s_energy = save.energy > SAMUS_MAX_ENERGY ? SAMUS_MAX_ENERGY : save.energy;
    s_invuln = save.invuln;
    memcpy(s_shots, save.shots, sizeof(s_shots));
    memcpy(s_bombs, save.bombs, sizeof(s_bombs));
    memcpy(s_frozen, save.frozen, sizeof(s_frozen));
    return 1;
}

int game_samus_register_hooks(void)
{
    int ok = nes_mod_register_function_entry_plugin(
        SAMUS_CONTACT_HOOK_ID, SMB1_PLAYER_ENEMY_COLLISION_ADDR, contact_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SAMUS_POWERUP_HOOK_ID, SMB1_POWERUP_COLLISION_ADDR, powerup_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SAMUS_INJURY_HOOK_ID, SMB1_INJURY_ADDR, injury_hook);
    ok &= nes_mod_register_savestate_hook("super-mario-bros.metroid.gameplay",
                                          save_get, save_set);
    return ok;
}

static void put_pixel(uint32_t *fb, int x, int y, uint32_t color)
{
    if (x >= 0 && x < g_render_width && y >= 0 && y < 240 &&
        !(s_draw_behind_background &&
          ppu_renderer_background_opaque(x, y)))
        fb[y * g_render_width + x] = color;
}

static const uint8_t k_varia_palette[4] = {0x0F, 0x16, 0x19, 0x35};
static const uint8_t k_missile_palette[4] = {0x0F, 0x16, 0x2C, 0x24};
static const uint8_t k_screw_palettes[4][4] = {
    {0x0F, 0x16, 0x19, 0x35},
    {0x0F, 0x12, 0x30, 0x21},
    {0x0F, 0x27, 0x2A, 0x3C},
    {0x0F, 0x15, 0x21, 0x38}
};

static void draw_tile(uint32_t *fb, int tile, int x, int y, int hflip,
                      int vflip, const uint8_t palette[4])
{
    const uint8_t *p;
    if (!s_assets_ready || tile < 0 || tile * 16 + 15 >= SAMUS_CHR_BYTES) return;
    p = s_chr + tile * 16;
    for (int row = 0; row < 8; ++row) {
        int sy = vflip ? 7 - row : row;
        uint8_t lo = p[sy], hi = p[sy + 8];
        for (int col = 0; col < 8; ++col) {
            int sx = hflip ? col : 7 - col;
            int value = ((lo >> sx) & 1) | (((hi >> sx) & 1) << 1);
            if (value)
                put_pixel(fb, x + col, y + row,
                          g_nes_palette[palette[value] & 0x3F]);
        }
    }
}

/* Metroid draws Samus as an OAM metasprite. Frame bytes select a placement
 * table, change tile attributes ($FD), skip placement cells ($FE), and offset
 * the object origin ($FC). Keeping those semantics is essential: treating the
 * tile ids as a rectangular grid is what produced the fragmented first build. */
static const int8_t k_place0[] = {
    -16,-8, -16,0, -8,-16, -8,-8, -8,0, 0,-8, 0,0, 0,8,
    8,-8, 8,0, 8,8, -8,-12, -8,-10, -20,-12, -18,-12
};
/* ObjPlace6 is intentionally followed by ObjPlace0 in Metroid's ROM. Aim-up
 * frames start at ObjPlace6, consume its two cannon cells, then continue into
 * the ordinary body placements. Keep the concatenation explicit here. */
static const int8_t k_place6[] = {
    -24,-4, -22,-4,
    -16,-8, -16,0, -8,-16, -8,-8, -8,0, 0,-8, 0,0, 0,8,
    8,-8, 8,0, 8,8, -8,-12, -8,-10, -20,-12, -18,-12
};
static const int8_t k_place1[] = {
    -13,-8, -13,0, -5,-8, -5,0, 3,-8, 3,0
};
static const int8_t k_place2[] = {
    -8,-10, -8,-2, -8,6, 0,-10, 0,-2, 0,6
};
static const int8_t k_place8[] = {
    -16,0, -16,8, -8,8, -16,-16, -16,-8, -8,-16,
    0,-16, 8,-16, 8,-8, 0,8, 8,0, 8,8
};
static const int8_t k_place_a[] = {
    -4,-8, -4,0, -4,16, -4,24
};
static const int8_t k_place_b[] = {
    -4,-16, -12,-8, -12,0, -4,8, 4,-8, 4,0
};
static const int8_t k_place_c[] = {
    -4,-24, -20,-16, -20,8, -4,16, 12,-16, 12,8
};
static const int8_t k_place_d[] = {
    -8,-8, -8,0, 0,-8, 0,0
};

static const uint8_t k_frame_stand[] = {
    0x40,0x0F,0x04, 0xFD,0x20, 0x0E,0x0D, 0xFE, 0x1E,0x1D,
    0x2E,0x2D, 0xFE, 0xFD,0x60, 0x3B,0x3C, 0xFE, 0x17,0xFF
};
static const uint8_t k_frame_run0[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0xFE, 0x41,0x40,
    0xFD,0x60, 0x20,0x21, 0xFE,0xFE, 0x31,0xFF
};
static const uint8_t k_frame_run1[] = {
    0x40,0x0F,0x04, 0x02,0x03, 0xFD,0x20, 0xFE, 0x43,0x42,
    0xFD,0x60, 0x22,0x23, 0xFE, 0x32,0x33,0x34,0xFF
};
static const uint8_t k_frame_run2[] = {
    0x40,0x0F,0x04, 0x05,0x06, 0xFD,0x20, 0xFE, 0x45,0x44,
    0xFD,0x60, 0x25,0x26,0x27,0x35,0x36,0xFF
};
static const uint8_t k_frame_stand_fire[] = {
    0x40,0x0F,0x04, 0xFD,0x20, 0x0E,0x0D, 0xFE, 0x1E,0x1D,
    0x2E,0x2D, 0xFE, 0xFD,0x60, 0x3B,0x3C, 0xFE,0xFE,0x17,0xFF
};
static const uint8_t k_frame_jump[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0xFE,0x41,0x40,
    0xFD,0x60, 0x22,0x07,0x08,0x32,0xFF
};
static const uint8_t k_frame_jump_fire[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0x4B,0x4A,0x49,
    0xFD,0x60, 0x22,0x07,0x08,0x32,0xFF
};
static const uint8_t k_frame_point_up[] = {
    0x40,0x0F,0x04, 0x69,0xFE, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77,0x2E,0x2D,0xFE, 0xFD,0x60, 0x3B,0x3C,0xFF
};
static const uint8_t k_frame_point_up_fire[] = {
    0x40,0x0F,0x04, 0xFE,0x69, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77,0x2E,0x2D,0xFE, 0xFD,0x60, 0x3B,0x3C,0xFF
};
static const uint8_t k_frame_jump_point_up[] = {
    0x40,0x0F,0x04, 0x69, 0xFD,0x20,0xFE, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x22,0x07,0x08,0x32,0xFF
};
static const uint8_t k_frame_jump_point_up_fire[] = {
    0x40,0x0F,0x04, 0xFE,0x69, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x22,0x07,0x08,0x32,0xFF
};
static const uint8_t k_frame_run_point_up0[] = {
    0x40,0x0F,0x04, 0x69,0xFE, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x20,0x21,0xFE,0xFE,0x31,0xFF
};
static const uint8_t k_frame_run_point_up1[] = {
    0x40,0x0F,0x04, 0x69,0xFE, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x22,0x23,0xFE,0x32,0x33,0x34,0xFF
};
static const uint8_t k_frame_run_point_up2[] = {
    0x40,0x0F,0x04, 0x69,0xFE, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x25,0x26,0x27,0x35,0x36,0xFF
};
static const uint8_t k_frame_run_point_up_fire0[] = {
    0x40,0x0F,0x04, 0xFE,0x69, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x20,0x21,0xFE,0xFE,0x31,0xFF
};
static const uint8_t k_frame_run_point_up_fire1[] = {
    0x40,0x0F,0x04, 0xFE,0x69, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x22,0x23,0xFE,0x32,0x33,0x34,0xFF
};
static const uint8_t k_frame_run_point_up_fire2[] = {
    0x40,0x0F,0x04, 0xFE,0x69, 0xFD,0x20, 0x7A,0x79,0xFE,
    0x78,0x77, 0xFD,0x60, 0x25,0x26,0x27,0x35,0x36,0xFF
};
static const uint8_t k_frame_run_fire0[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0x4B,0x4A,0x49,
    0xFD,0x60, 0x20,0x21, 0xFE,0xFE,0x31,0xFF
};
static const uint8_t k_frame_run_fire1[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0x4B,0x4A,0x49,
    0xFD,0x60, 0x22,0x23, 0xFE,0x32,0x33,0x34,0xFF
};
static const uint8_t k_frame_run_fire2[] = {
    0x40,0x0F,0x04, 0x00,0x01, 0xFD,0x20, 0x4B,0x4A,0x49,
    0xFD,0x60, 0x25,0x26,0x27,0x35,0x36,0xFF
};
static const uint8_t k_frame_spin0[] = {
    0x41,0x0F,0x04, 0x52,0x53,0x62,0x63,0x72,0x73,0xFF
};
static const uint8_t k_frame_spin1[] = {
    0x42,0x0F,0x04, 0x54,0x55,0x56,0x64,0x65,0x66,0xFF
};
static const uint8_t k_frame_spin2[] = {
    0x81,0x0F,0x04, 0x52,0x53,0x62,0x63,0x72,0x73,0xFF
};
static const uint8_t k_frame_spin3[] = {
    0x82,0x0F,0x04, 0x54,0x55,0x56,0x64,0x65,0x66,0xFF
};
static const uint8_t k_frame_roll0[] = {
    0x41,0x08,0x04, 0xFC,0x03,0x00, 0x50,0x51,0x60,0x61,0xFF
};
static const uint8_t k_frame_roll1[] = {
    0xC1,0x08,0x04, 0xFC,0xFD,0x00, 0x50,0x51,0x60,0x61,0xFF
};
static const uint8_t k_frame_roll2[] = {
    0x81,0x08,0x04, 0xFC,0xFD,0x00, 0x50,0x51,0x60,0x61,0xFF
};
static const uint8_t k_frame_roll3[] = {
    0x01,0x08,0x04, 0xFC,0x03,0x00, 0x50,0x51,0x60,0x61,0xFF
};
static const uint8_t k_frame_missile_explode0[] = {
    0x0A,0x04,0x08, 0xFD,0x00,0x57, 0xFD,0x40,0x57,0xFF
};
static const uint8_t k_frame_missile_explode1[] = {
    0x0B,0x04,0x0C, 0xFD,0x00,0x57,0x18, 0xFD,0x40,0x18,0x57,
    0xFD,0xC0,0x18,0x18,0xFF
};
static const uint8_t k_frame_missile_explode2[] = {
    0x0C,0x04,0x10, 0xFD,0x00,0x57,0x18, 0xFD,0x40,0x18,0x57,
    0xFD,0xC0,0x18,0x18,0xFF
};
static const uint8_t k_frame_bomb_explode0[] = {
    0x0D,0x0C,0x0C, 0x74, 0xFD,0x60,0x74, 0xFD,0xA0,0x74,
    0xFD,0xE0,0x74,0xFF
};
static const uint8_t k_frame_bomb_explode1[] = {
    0x0D,0x0C,0x0C, 0x75, 0xFD,0x60,0x75, 0xFD,0xA0,0x75,
    0xFD,0xE0,0x75,0xFF
};
static const uint8_t k_frame_bomb_explode2[] = {
    0x08,0x10,0x10, 0x3D,0x3E,0x4E, 0xFD,0x60,0x3E,0x3D,0x4E,
    0xFD,0xE0,0x4E,0x3E,0x3D, 0xFD,0xA0,0x4E,0x3D,0x3E,0xFF
};

static void draw_metasprite(uint32_t *fb, const uint8_t *frame,
                            const int8_t *place, int place_count,
                            int origin_x, int origin_y, int mirror,
                            const uint8_t palette[4])
{
    unsigned frame_i = 3;
    int place_i = 0;
    int offset_x = 0, offset_y = 0;
    int attrs = frame[0] & 0xC0;
    const int place_hflip = ((frame[0] & 0x40) != 0) ^ mirror;
    const int place_vflip = (frame[0] & 0x80) != 0;
    for (int guard = 0; guard < 64; ++guard) {
        int value = frame[frame_i++];
        if (value == 0xFF) return;
        if (value == 0xFC) {
            offset_y += (int8_t)frame[frame_i++];
            offset_x += (int8_t)frame[frame_i++];
            continue;
        }
        if (value == 0xFD) {
            attrs = frame[frame_i++];
            continue;
        }
        if (value == 0xFE) {
            place_i++;
            continue;
        }
        if (place_i >= place_count) return;
        int dy = place[place_i * 2];
        int dx = place[place_i * 2 + 1];
        if (place_hflip) dx = -dx - 8;
        if (place_vflip) dy = -dy - 8;
        draw_tile(fb, value, origin_x + offset_x + dx,
                  origin_y + offset_y + dy,
                  ((attrs & 0x40) != 0) ^ mirror,
                  (attrs & 0x80) != 0, palette);
        place_i++;
    }
}

static const uint8_t *samus_palette(const ForeignState *state)
{
    if (state && metroid_samus_is_spinning())
        return k_screw_palettes[(state->state_frame >> 1) & 3];
    return s_missile_mode ? k_missile_palette : k_varia_palette;
}

static void draw_samus(uint32_t *fb)
{
    const ForeignState *state = nes_foreign_state();
    int x = g_ram[Player_Rel_XPos] + g_widescreen_left;
    int y = g_ram[Player_Rel_YPos] +
            (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256);
    int mirror = state && state->facing < 0.0f;
    int firing = (s_fire_pose & SAMUS_FIRE_POSE_TICKS) != 0;
    int aiming_up = (g_controller1_buttons & PAD_UP) != 0 ||
                    (s_fire_pose & SAMUS_FIRE_POSE_UP) != 0;
    const uint8_t *palette = samus_palette(state);
    if (s_invuln && (s_invuln & 2)) return;
    if (metroid_samus_is_morphed()) {
        static const uint8_t *frames[4] = {
            k_frame_roll0, k_frame_roll1, k_frame_roll2, k_frame_roll3
        };
        int phase = state ? (int)(state->state_frame / 4u) & 3 : 0;
        int origin_y = y + ((frames[phase][0] & 0x80) ? 22 : 26);
        draw_metasprite(fb, frames[phase], k_place1, 6,
                        x + 8, origin_y, 0, palette);
    } else if (aiming_up) {
        static const uint8_t *run_up_frames[3] = {
            k_frame_run_point_up0, k_frame_run_point_up1,
            k_frame_run_point_up2
        };
        static const uint8_t *run_up_fire_frames[3] = {
            k_frame_run_point_up_fire0, k_frame_run_point_up_fire1,
            k_frame_run_point_up_fire2
        };
        int airborne = state && !state->grounded;
        int running = state && state->state == METROID_SAMUS_RUN;
        unsigned phase = state ? (state->state_frame / 6u) % 3u : 0u;
        const uint8_t *frame;
        if (airborne)
            frame = firing ? k_frame_jump_point_up_fire
                           : k_frame_jump_point_up;
        else if (running)
            frame = (firing ? run_up_fire_frames : run_up_frames)[phase];
        else
            frame = firing ? k_frame_point_up_fire : k_frame_point_up;
        draw_metasprite(fb, frame, k_place6, 17,
                        x + 8, y + 16, mirror, palette);
    } else if (metroid_samus_is_spinning()) {
        static const uint8_t *frames[4] = {
            k_frame_spin0, k_frame_spin1, k_frame_spin2, k_frame_spin3
        };
        int phase = state ? (int)(state->state_frame / 4u) & 3 : 0;
        const int8_t *place = (phase & 1) ? k_place2 : k_place1;
        draw_metasprite(fb, frames[phase], place, 6,
                        x + 8, y + 16, mirror, palette);
    } else {
        static const uint8_t *run_frames[3] = {
            k_frame_run0, k_frame_run1, k_frame_run2
        };
        static const uint8_t *run_fire_frames[3] = {
            k_frame_run_fire0, k_frame_run_fire1, k_frame_run_fire2
        };
        int scripted_walk = game_smash64_scripted_presentation() ==
                            SMASH64_SCRIPTED_PRESENTATION_WALK;
        unsigned animation_frame = scripted_walk
                                       ? (unsigned)s_present_frame
                                       : (state ? state->state_frame : 0u);
        int running = scripted_walk ||
                      (state && state->state == METROID_SAMUS_RUN);
        const uint8_t *frame = k_frame_stand;
        if (state && state->state == METROID_SAMUS_JUMP)
            frame = firing ? k_frame_jump_fire : k_frame_jump;
        else if (running)
            frame = (firing ? run_fire_frames : run_frames)
                    [(animation_frame / 6u) % 3u];
        else if (firing)
            frame = k_frame_stand_fire;
        draw_metasprite(fb, frame, k_place0, 15,
                        x + 8, y + 16, mirror, palette);
    }
}

static void draw_projectiles(uint32_t *fb)
{
    int camera = screen_left_x();
    for (int i = 0; i < 3; ++i) if (s_shots[i].active) {
        int x = (int)s_shots[i].x - camera + g_widescreen_left;
        int y = (int)s_shots[i].y;
        if (s_shots[i].active == 2) {
            if (!s_shots[i].missile) {
                if (s_shots[i].age < 3)
                    draw_tile(fb, 0x04, x - 4, y - 4, 0, 0,
                              k_varia_palette);
            } else if (s_shots[i].age < 3) {
                draw_metasprite(fb, k_frame_missile_explode0,
                                k_place_a, 4, x, y, 0,
                                k_missile_palette);
            } else if (s_shots[i].age < 5) {
                draw_metasprite(fb, k_frame_missile_explode1,
                                k_place_b, 6, x, y, 0,
                                k_missile_palette);
            } else {
                draw_metasprite(fb, k_frame_missile_explode2,
                                k_place_c, 6, x, y, 0,
                                k_missile_palette);
            }
        } else if (!s_shots[i].missile) {
            draw_tile(fb, 0x4C, x - 4, y - 4, 0, 0, k_varia_palette);
        } else if (s_shots[i].vertical) {
            draw_tile(fb, 0x14, x - 4, y - 8, 0, 0, k_missile_palette);
            draw_tile(fb, 0x24, x - 4, y, 0, 0, k_missile_palette);
        } else {
            int hflip = s_shots[i].dx > 0.0;
            /* ObjFrame_MissileRight horizontally flips ObjPlaceA as well as
             * the tile pixels, so the two cells exchange positions. Merely
             * flipping each cell leaves the nose and exhaust separated. */
            draw_tile(fb, 0x5E, hflip ? x : x - 8, y - 4,
                      hflip, 0, k_missile_palette);
            draw_tile(fb, 0x5F, hflip ? x - 8 : x, y - 4,
                      hflip, 0, k_missile_palette);
        }
    }
    for (int i = 0; i < 3; ++i) if (s_bombs[i].active) {
        int x = (int)s_bombs[i].x - camera + g_widescreen_left;
        int y = (int)s_bombs[i].y;
        if (s_bombs[i].timer > 0) {
            draw_tile(fb, 0x70 + ((s_bombs[i].timer >> 2) & 1),
                      x - 4, y - 4, 0, 0, k_varia_palette);
        } else {
            int phase = -s_bombs[i].timer;
            if (phase < 2)
                draw_metasprite(fb, k_frame_bomb_explode0,
                                k_place_d, 4, x, y, 0, k_varia_palette);
            else if (phase < 4) {
                /* Metroid deliberately inserts a blank flash frame. */
            } else if (phase < 6)
                draw_metasprite(fb, k_frame_bomb_explode1,
                                k_place_d, 4, x, y, 0, k_varia_palette);
            else if (phase < 8) {
                /* Second blank flash frame. */
            } else if (phase < 12 || phase >= 14)
                draw_metasprite(fb, k_frame_bomb_explode2,
                                k_place8, 12, x, y, 0, k_varia_palette);
        }
    }
}

static void draw_digit(uint32_t *fb, int digit, int x, int y, uint32_t color)
{
    static const uint16_t bits[10] = {
        0x7b6f,0x2492,0x73e7,0x73cf,0x5bc9,
        0x79cf,0x79ef,0x7249,0x7bef,0x7bcf
    };
    uint16_t pattern = bits[digit % 10];
    for (int row = 0; row < 5; ++row)
        for (int col = 0; col < 3; ++col)
            if (pattern & (1u << (14 - (row * 3 + col))))
                put_pixel(fb, x + col, y + row, color);
}

static void draw_hud(uint32_t *fb)
{
    int x = g_widescreen_left + 8;
    uint32_t color = s_missile_mode ? 0xFFFF4848u : 0xFF80F8F8u;
    draw_digit(fb, (s_energy / 100) % 10, x, 8, color);
    draw_digit(fb, (s_energy / 10) % 10, x + 4, 8, color);
    draw_digit(fb, s_energy % 10, x + 8, 8, color);
    /* Infinite missile indicator: a compact sideways-eight beside energy. */
    if (s_missile_mode) {
        for (int i = 0; i < 3; ++i) {
            put_pixel(fb, x + 14 + i, 9 + (i == 1), color);
            put_pixel(fb, x + 18 + i, 9 + (i == 1), color);
        }
    }
}

void game_samus_render_post_render(uint32_t *framebuffer)
{
    Smash64ScriptedPresentation scripted_presentation;
    if (!framebuffer || !game_samus_active() || g_ram[OperMode] != 1) return;
    scripted_presentation = game_smash64_scripted_presentation();
    if (!game_smash64_active() &&
        !game_smash64_death_presentation_active() &&
        !game_smash64_still_presentation_active() &&
        !game_smash64_swim_presentation_active() &&
        scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_NONE) return;
    s_draw_behind_background =
        (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE ||
         scripted_presentation ==
             SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL) &&
        (g_ram[Player_SprAttrib] & 0x20) != 0;
    draw_samus(framebuffer);
    s_draw_behind_background = 0;
    draw_projectiles(framebuffer);
    for (int slot = 0; slot < 5; ++slot) if (s_frozen[slot].timer) {
        int x = (int)s_frozen[slot].x + ((int)s_frozen[slot].page << 8) -
                screen_left_x() + g_widescreen_left;
        int y = s_frozen[slot].y;
        uint32_t ice = g_nes_palette[(s_present_frame & 2) ? 0x21 : 0x2C];
        for (int p = 0; p < 4; ++p) {
            put_pixel(framebuffer, x + p, y + 2, ice);
            put_pixel(framebuffer, x + 15 - p, y + 2, ice);
            put_pixel(framebuffer, x + p, y + 20, ice);
            put_pixel(framebuffer, x + 15 - p, y + 20, ice);
        }
        for (int p = 0; p < 3; ++p) {
            put_pixel(framebuffer, x + 1, y + 3 + p, ice);
            put_pixel(framebuffer, x + 14, y + 3 + p, ice);
            put_pixel(framebuffer, x + 1, y + 17 + p, ice);
            put_pixel(framebuffer, x + 14, y + 17 + p, ice);
        }
        put_pixel(framebuffer, x + 5 + (s_present_frame & 3), y + 6, ice);
        put_pixel(framebuffer, x + 9 - (s_present_frame & 3), y + 15, ice);
    }
    draw_hud(framebuffer);
}
