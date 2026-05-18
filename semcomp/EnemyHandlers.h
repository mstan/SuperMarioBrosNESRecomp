// semcomp/EnemyHandlers.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class EnemyHandlers {
public:
    explicit EnemyHandlers(GameState& state) : state_(state) {}

    void init_goomba();  // $C2F1 InitGoomba
    void init_hammer_bro();  // $C328 InitHammerBro
    void init_bullet_bill();  // $C36B InitBulletBill
    void init_cheep_cheep();  // $C375 InitCheepCheep
    void init_lakitu();  // $C385 InitLakitu
    void setup_lakitu();  // $C38A SetupLakitu
    void init_short_firebar();  // $C45C InitShortFirebar
    void move_defeated_enemy();  // $CAE5 MoveDefeatedEnemy
    void move_jumping_enemy();  // $CAF9 MoveJumpingEnemy
    void move_bloober();  // $CB89 MoveBloober

private:
    GameState& state_;
};

}  // namespace smb::semcomp
