
#include "globals.h"

//main globals
Rectangle screen = {0, 0, INIT_WIDTH, INIT_HEIGHT};
double dt = 0;
Camera2D camera = { 0 };
bool debug = true;
bool pause = false;

//player globals
Player player = { 0 };
double frametime = 0;
int cur_frame = 0;
int animation_index = 0;


//tilemap globals
int map[20][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 1, 2, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

Rectangle tile_frame = {0, 0, TILE_SIZE, TILE_SIZE};
Rectangle tile_view = {0, 0, TILE_SIZE, TILE_SIZE};
Texture2D tileset = {0}; 
int qtd_floor = 0;
int mine_index = 0;
GridPos spawn_tile = {5, 2};
Vector2 world_origin = {0, 0};
int map_width = 10;
int map_height = 20;



