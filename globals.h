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

void PlayerInit(Tile **tilemap);
void PlayerMovement();

void PlayerUpdate(Tile **tilemap);
void IsPlayerMoving();
void PlayerCollision(Tile **tilemap);
void AnimationHandler();


Tile **InitMap(void);
int **InitOrigin(void);
void PopulateTilemap(Tile **tilemap, int **origin);
Mine *MineListInit(void);
void GenerateMinefild(Mine *mine_arr, Tile **tilemap);
void MapMines(Mine *minefild, Tile **tilemap);
void GetSorroundingMines(Tile **tilemap);
void RenderMines(Mine *minefild);
void RevealTiles(GridPos tile_pos, Tile **tilemap);
Mine * ResetLevel(Mine *minefild, Tile **tilemap);

