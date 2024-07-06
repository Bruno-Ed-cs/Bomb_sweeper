#include "globals.h"
#include "include/raylib.h"
#include <stdbool.h>

//assets
//audio

double general_volume = 1.0f;

//music
Music menu_theme;
Music level_music;

Music *music_list[2] = {&menu_theme, &level_music};
double music_volume = 0.45f;

//sfx
Sound footstep_sfx;
Sound explosion_sfx;
Sound flag_sfx;
Sound place_bomb_sfx;
Sound button_click;
Sound fuse_sfx;
Sound win_theme;
Sound lose_theme;

double sfx_volume = 0.35f;
Sound *sfx_list[8] = {&footstep_sfx, &explosion_sfx, &flag_sfx, &place_bomb_sfx, &button_click, &fuse_sfx, &win_theme, &lose_theme};

//sprites
Texture2D explosion_sheet;
Texture2D bomb_sheet;
Texture2D wallet_sprite;
Texture2D clock_sprite;
Texture2D background;
Texture2D tileset; 
Texture2D MenuTela;
Texture2D thumb_beach;
Texture2D pause_ui;
Texture2D volume_slide;

//main globals
Rectangle screen = {0, 0, INIT_WIDTH, INIT_HEIGHT};
bool running = true;
double dt = 0;
Camera2D camera = { 0 };
bool debug = false;
bool pause = false;
double timer = 0;
double minutes = 0;
double seconds = 0;
Vector2 mouse_pos = {0, 0};
Font custom_font;
int final_score = 0;
int game_ui = PAUSE;

//Tela de jogo
GameState state = START_MENU;

//player globals
Player player = { 0 };
double frametime = 0;
int cur_frame = 0;
int animation_index = 0;
Rectangle camera_bounds = {0, 0, 320, 180};

//ui globals
//controle de explosoes
Explosion explosion_buffer[MAX_EXPLOSIONS];
int explosion_qtd = 0;

//bombas
Bomb bombs[MAX_BOMBS];
int bombs_qtd = 0;

//Level globals
Rectangle tile_frame = {0, 0, TILE_SIZE, TILE_SIZE};
Rectangle tile_view = {0, 0, TILE_SIZE, TILE_SIZE};
int qtd_floor = 0;
int mine_index = 0;
GridPos spawn_tile = {5, 2};
GridPos portal_tile = {0,0};
Vector2 world_origin = {0, 0};
int map_width = 50;
int map_height = 80;
Tile **tilemap;
Mine *minefild;
Rectangle level_bounds = {0};
bool level_loaded = false;
int bomb_density = 0;
int tile_index;





