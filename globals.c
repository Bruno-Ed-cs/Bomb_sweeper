#include "globals.h"
#include <stdbool.h>

//main globals
Rectangle screen = {0, 0, INIT_WIDTH, INIT_HEIGHT};
double dt = 0;
Camera2D camera = { 0 };
bool debug = false;
bool pause = false;
double timer = 0;
Vector2 mouse_pos = {0, 0};

//Tela de jogo
GameState state = START_MENU;

//player globals
Player player = { 0 };
double frametime = 0;
int cur_frame = 0;
int animation_index = 0;
Rectangle camera_bounds = {0, 0, 320, 180};
Sound footstep_sfx;

//controle de explosoes
Explosion explosion_buffer[MAX_EXPLOSIONS];
int explosion_qtd = 0;

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
bool level_loaded = false;





