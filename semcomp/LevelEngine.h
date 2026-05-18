// semcomp/LevelEngine.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class LevelEngine {
public:
    explicit LevelEngine(GameState& state) : state_(state) {}

    void get_background_color();  // $85E3 GetBackgroundColor (entry 0)
    void at_862e();  // $862E at_862e (entry 1)
    void write_game_text();  // $8808 WriteGameText (entry 0)
    void at_8887();  // $8887 at_8887 (entry 1)
    void at_8846();  // $8846 at_8846 (entry 2)
    void write_block_metatile();  // $8A6D WriteBlockMetatile (entry 0)
    void move_v_offset();  // $8A8F MoveVOffset (entry 1)
    void put_block_metatile();  // $8A97 PutBlockMetatile (entry 0)
    void rem_bridge();  // $8ACD RemBridge (entry 1)
    void at_8a9d();  // $8A9D at_8a9d (entry 2)
    void get_area_music();  // $90ED GetAreaMusic (entry 0)
    void at_9100();  // $9100 at_9100 (entry 1)
    void area_parser_core();  // $93FC AreaParserCore (entry 0)
    void at_9494();  // $9494 at_9494 (entry 1)
    void terr_loop();  // $9491 TerrLoop (entry 2)
    void process_area_data();  // $9508 ProcessAreaData (entry 0)
    void end_a_parse();  // $9588 EndAParse (entry 1)
    void decode_area_data();  // $9595 DecodeAreaData (entry 0)
    void loop_cmd_e();  // $9645 LoopCmdE (entry 1)
    void at_95df();  // $95DF at_95df (entry 2)
    void area_style_object();  // $9740 AreaStyleObject (entry 0)
    void at_9792();  // $9792 at_9792 (entry 1)
    void at_9989();  // $9989 at_9989 (entry 2)
    void set_hi_max();  // $BF94 SetHiMax (entry 0)
    void set_x_move_amt();  // $BF96 SetXMoveAmt (entry 1)

private:
    void get_background_color_body(int _entry);  // shared body for $85E3_b0 /* GetBackgroundColor */
    void write_game_text_body(int _entry);  // shared body for $8808_b0 /* WriteGameText */
    void write_block_metatile_body(int _entry);  // shared body for $8A6D_b0 /* WriteBlockMetatile */
    void put_block_metatile_body(int _entry);  // shared body for $8A97_b0 /* PutBlockMetatile */
    void get_area_music_body(int _entry);  // shared body for $90ED_b0 /* GetAreaMusic */
    void area_parser_core_body(int _entry);  // shared body for $93FC_b0 /* AreaParserCore */
    void process_area_data_body(int _entry);  // shared body for $9508_b0 /* ProcessAreaData */
    void decode_area_data_body(int _entry);  // shared body for $9595_b0 /* DecodeAreaData */
    void area_style_object_body(int _entry);  // shared body for $9740_b0 /* AreaStyleObject */
    void set_hi_max_body(int _entry);  // shared body for $BF94_b0 /* SetHiMax */
    GameState& state_;
};

}  // namespace smb::semcomp
