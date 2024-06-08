#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>



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


} Player;

void PlayerInit();
void PlayerMovement();
void PlayerUpdate();
void IsPlayerMoving();
void PlayerCollision();
void AnimationHandler();


void PopulateTilemap(int size, Tile tilemap[size][size], int origin[size][size]);
void GenerateMinefild(Mine *mine_arr);
void GetSorroundingMines();
Mine * MineListInit();
void RenderMines(Mine *minefild);
void MapMines(Mine * minefild);
