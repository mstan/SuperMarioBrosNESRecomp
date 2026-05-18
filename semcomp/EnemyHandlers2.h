// semcomp/EnemyHandlers2.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class EnemyHandlers2 {
public:
    explicit EnemyHandlers2(GameState& state) : state_(state) {}

    void bridge_collapse();  // $CFEC BridgeCollapse
    void kill_all_enemies_d071();  // $D071 KillAllEnemies
    void run_bowser();  // $D065 RunBowser
    void move_d_bowser();  // $D00F MoveD_Bowser
    void erase_enemy_object();  // $C998 EraseEnemyObject
    void init_vstf();  // $C363 InitVStf
    void init_enemy_object();  // $C226 InitEnemyObject
    void check_frenzy_buffer();  // $C216 CheckFrenzyBuffer
    void check_three_bytes();  // $C250 CheckThreeBytes
    void handle_group_enemies();  // $C71B HandleGroupEnemies
    void inc_3b();  // $C25B Inc3B
    void end_area_points();  // $D336 EndAreaPoints
    void award_game_timer_points();  // $D312 AwardGameTimerPoints

private:
    GameState& state_;
};

}  // namespace smb::semcomp
