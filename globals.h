#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#define TILE_SIZE 16

#define INIT_WIDTH 1280
#define INIT_HEIGHT 720

#define INIT_X 0
#define INIT_Y 0

#define UP 0
#define DOWN 1
#define LEFT 3
#define RIGHT 2

#define AIR 0
#define FLOOR 2
#define WALL 1

typedef struct Tile{

	Vector2 tile_pos;
	int type;
	Rectangle tile;

} Tile;

typedef struct Player {

	Vector2 position;
	Rectangle hitbox;
	Rectangle frame;
	Rectangle view;
	Texture2D sprite;
	bool move;
	int direction;
	double speed;


} Player;

void PlayerInit();
void PlayerMovement();
void PlayerUpdate();
void IsPlayerMoving();
void PlayerCollision();


void PopulateTilemap(int size, Tile tilemap[size][size], int origin[size][size]);

