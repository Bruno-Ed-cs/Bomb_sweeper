#include "globals.h"
#include "include/Linux/wayland/raylib.h"

//main globals
Rectangle screen = {0, 0, INIT_WIDTH, INIT_HEIGHT};
double dt = 0;
Camera2D camera = { 0 };
bool debug = false;
bool pause = false;
double timer = 0;


//Tela de jogo
GameScreen CurrentScreen = MENU;



//player globals
Player player = { 0 };
double frametime = 0;
int cur_frame = 0;
int animation_index = 0;
Rectangle camera_bounds = {0, 0, 320, 180};


//tilemap globals
Rectangle tile_frame = {0, 0, TILE_SIZE, TILE_SIZE};
Rectangle tile_view = {0, 0, TILE_SIZE, TILE_SIZE};
Texture2D tileset = {0}; 
int qtd_floor = 0;
int mine_index = 0;
GridPos spawn_tile = {5, 2};
Vector2 world_origin = {0, 0};
int map_width = 50;
int map_height = 80;
Tile **tilemap;
Mine *minefild;
Rectangle level_bounds = {0};





