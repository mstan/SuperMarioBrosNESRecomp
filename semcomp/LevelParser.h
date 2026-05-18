// semcomp/LevelParser.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class LevelParser {
public:
    explicit LevelParser(GameState& state) : state_(state) {}

    void get_area_palette();  // $85BF GetAreaPalette
    void area_parser_task_control();  // $86E6 AreaParserTaskControl
    void render_area_graphics();  // $88AE RenderAreaGraphics
    void initialize_area();  // $8FE4 InitializeArea
    void area_parser_task_handler();  // $92B0 AreaParserTaskHandler
    void area_parser_tasks();  // $92C8 AreaParserTasks
    void get_area_object_i_d();  // $9B36 GetAreaObjectID
    void get_area_obj_x_position();  // $9BCB GetAreaObjXPosition
    void get_area_obj_y_position();  // $9BD3 GetAreaObjYPosition
    void load_area_pointer();  // $9C03 LoadAreaPointer
    void get_area_type();  // $9C09 GetAreaType
    void get_area_data_addrs();  // $9C22 GetAreaDataAddrs

private:
    GameState& state_;
};

}  // namespace smb::semcomp
