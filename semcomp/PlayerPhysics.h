// semcomp/PlayerPhysics.h — facade over Mario's per-frame movement routines.
//
// Phase 9 ownership via [[replace_func]]:
//   $B0E6 AutoControlPlayer    -> PlayerPhysics::auto_control
//   $B329 PlayerMovementSubs   -> PlayerPhysics::movement_subs
//
// AutoControlPlayer is the entry point used by scripted-Mario states
// (entrance walk, end-level walk-into-castle, death drop). It takes A
// = controller-input mask, stages it at $06FC, and falls through into
// PlayerCtrlRoutine ($B0E9) which we DO NOT own — too entangled in
// the same generated function body.
//
// PlayerMovementSubs reads PlayerSize / Player_State / Joypad to set
// the CrouchingFlag, calls MovePlayer ($B450, still natural-generated),
// then dispatches to OnGroundStateSub / JumpSwimSub / FallingSub /
// ClimbingSub via the $8E04 inline-dispatch table. The four
// sub-handlers are all emitted standalone (func_B35A_b0 / func_B376_b0
// / func_B36D_b0 / func_B3CF_b0) so we can dispatch them via
// call_by_address.
//
// Why these two? The natural in-game test surface is huge:
//   - AutoControlPlayer fires every scripted-walk frame (level intro,
//     flagpole-touched walk into castle, death-state Y-drop).
//   - PlayerMovementSubs fires every gameplay frame Mario is alive.
// If either replacement has a bug, normal play breaks immediately —
// that's the strongest verification signal.
//
// Mario.cpp keeps the attribute reads/writes (position, power, facing).
// PlayerPhysics owns the per-frame routines.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class PlayerPhysics {
public:
    explicit PlayerPhysics(GameState& state) : state_(state) {}

    // auto_control: replacement body for $B0E6.
    // Caller passes A = controller-input mask. We write it to $06FC,
    // then call into PlayerCtrlRoutine ($B0E9) — which is a separate
    // standalone function the recompiler emitted, NOT owned by us.
    void auto_control();

    // ---- PlayerMovementSubs dispatch targets (Phases 11-13) -------------
    // The four sub-handlers from PlayerMovementSubs' $8E04 dispatch table.
    // PhysicsSub ($B450) intentionally deferred — ~300-line body with
    // heavy ROM-table lookups, dedicated phase later.
    //
    // $B35A OnGroundStateSub — ground-walking frame. 4 sub-calls, 1 branch.
    // $B376 JumpSwimSub      — air/swim physics. Sign-bit branches; tail
    //                          into $B3AC LRAir (standalone).
    // $B36D FallingSub       — copy $070A → $0709, tail-call $B3AC LRAir.
    // $B3CF ClimbingSub      — vine/flagpole climb. Inner labels exist as
    //                          standalone _b1 (sound bank) but are unused
    //                          from _b0, so replace is safe.
    void on_ground_state_sub();
    void jump_swim_sub();
    void falling_sub();
    void climbing_sub();

    // Phase 14 — $B450 PlayerPhysicsSub. Per-frame physics dispatcher.
    // Three-branch tree: climbing (ProcClimb) / new-jump (CheckForJumping +
    // InitJS) / X-physics (tail-call to standalone $B51C). Sets initial
    // jump-state, picks Y-physics tier from ROM tables at $B424/$B42B/
    // $B439/$B432 based on $0700 PlayerXSpeedAbsolute and $0704 SwimmingFlag.
    void physics_sub();

    // Phase 15 — MovePlayer family.
    //   $B200 MovePlayerYAxis     — trivial: $CE += A; RTS
    //   $BF09 MovePlayerHorizontally — gate on $070E, body shared with $BF4C
    //   $BF4C ExXMove             — just RTS (early-exit point of $BF09)
    //   $BF4D MovePlayerVertically — gate on $0747+$070E, tail-call $BFAD
    void move_player_y_axis();
    void move_player_horizontally();
    void ex_x_move();
    void move_player_vertically();

    // movement_subs: replacement body for $B329.
    // Logic chain:
    //   1. CrouchingFlag computation: tall Mario on ground with Down
    //      held -> crouch. Stored at $0714.
    //   2. JSR $B450 (MovePlayer — natural, applies velocity).
    //   3. Bail-out gate: PlayerChangeSizeFlag ($070B) != 0 -> early
    //      return (don't run movement subs during grow/shrink anim).
    //   4. Dispatch on $001D Player_State:
    //        $001D == 3 -> skip the $0789 = $18 stage, go to MoveSubs
    //        else      -> Y = $18, $0789 = Y, fall to MoveSubs
    //   5. MoveSubs: switch on A (0..3) -> OnGround / JumpSwim /
    //      Falling / Climbing handlers (all separately-emitted).
    void movement_subs();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
