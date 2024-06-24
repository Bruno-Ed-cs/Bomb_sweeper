#ifdef _WIN32

#include "include/Windows/raylib.h"
#elif X11

#include "include/Linux/x11/raylib.h"
#elif __linux__

#include "include/Linux/wayland/raylib.h"
#endif

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "include/cJSON.h"



#define TILE_SIZE 16

#define INIT_WIDTH 1280
#define INIT_HEIGHT 720

#define INIT_X 0
#define INIT_Y 0

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2

#define AIR 0
#define FLOOR 2
#define WALL 1

typedef enum GameScreen {MENU, GAME} GameScreen; 

typedef struct GridPos
{
	int x;
	int y;

} GridPos ;

typedef struct Tile
{

	GridPos tile_pos;
	int type;
	Rectangle tile;
	int sorrounding_mines;
	bool visible;
	bool flaged;


} Tile;

typedef struct Mine
{
	GridPos grid_pos;
	Rectangle hitbox;

} Mine;

typedef struct Player {

	Vector2 position;
	Vector2 previous_pos;
	GridPos grid_pos;
	GridPos spawn;
	Rectangle hitbox;
	Rectangle frame;
	Rectangle view;
	Texture2D sprite;
	bool move;
	bool colliding;
	int direction;
	double speed;


} 




Player;

//declaração das variáveis globais
//Localização: globals.c
//main globals
extern Rectangle screen;
extern double dt;
extern Camera2D camera;
extern bool debug;
extern bool pause;
extern double timer;
extern GameScreen CurrentScreen;

//Menu
extern Rectangle exit_menu;
extern Rectangle play;

//player globals
extern Player player;
extern double frametime;
extern int cur_frame;
extern int animation_index;
extern Rectangle camera_bounds;


//tilemap globals

extern Rectangle tile_frame;
extern Rectangle tile_view;
extern Texture2D tileset; 
extern int qtd_floor;
extern int mine_index;
extern GridPos spawn_tile;
extern Vector2 world_origin;
extern int map_width;
extern int map_height;
extern Tile **tilemap;
extern Mine *minefild;
extern Rectangle level_bounds;

//funçoes do jogador 
//Localização: player.c
void PlayerInit();
void PlayerMovement();
void DrawPlayer();
void PlayerUpdate();
void IsPlayerMoving();
void PlayerCollision();
void AnimationHandler();
void PutFlag();
void CameraUpdate();

// funçoes do mapa e minas
// Localização: tilemap.c
void AllocMap();
void LoadLevel(char *level);
void MineListInit();
void GenerateMinefild();
void MapMines();
void GetSorroundingMines();
void RenderMines();
void RevealTiles(GridPos tile_pos);
void ResetLevel();
void UnloadLevel();
void DrawTiles(GridPos start, GridPos end);

//funções de sistema
//Localização: system.c

int GetTileType(GridPos tile, int type);
GridPos GetMatrixEnd(GridPos origin, int radius);
GridPos GetMatrixBegin(GridPos origin, int radius);
void InputHandler(int input);


