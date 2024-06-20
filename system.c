#include "globals.h"

void InputHandler(int input)
{
    switch (input) {

        case KEY_P:
            pause = !pause;
        break;


        case KEY_R:

            if(debug) ResetLevel();

        break;

        case KEY_F3:
            debug = !debug;
        break;

    }

};

GridPos GetMatrixBegin(GridPos origin, int radius)
{
    GridPos begining;

    begining.x = origin.x - radius;
    begining.y = origin.y - radius;

    if (begining.x < 0) begining.x = 0;
    if (begining.y < 0) begining.y = 0;

    return begining;

};

GridPos GetMatrixEnd(GridPos origin, int radius)
{
    GridPos end;

    end.x = origin.x + radius;
    end.y = origin.y + radius;

    if (end.x >= map_width) end.x = map_width;
    if (end.y >= map_height) end.y = map_height;

    return end;

};


int GetTileType(GridPos tile, int type)
{

    if (tile.y < 0 || tile.y >= map_height) return 0;
    if (tile.x < 0 || tile.x >= map_width) return 0;

    return tilemap[tile.y][tile.x].type;

};


