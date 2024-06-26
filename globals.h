#include "include/raylib.h"


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
#define PORTAL 3

#define MAX_EXPLOSIONS 256
#define MAX_BOMBS 5

#define TRANSPARENCY CLITERAL(Color){255, 255, 255, 150} 

typedef enum GameState 
{	
	START_MENU,
	GAME
} GameState; 

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
	bool bombed;


} Tile;

typedef struct Mine
{
	GridPos grid_pos;
	Rectangle hitbox;
	bool detonated;
	bool exploding;
	int power;
	double fuse;

} Mine;

typedef struct Explosion
{
	GridPos grid_pos;
	int power;
	Rectangle center;
	Rectangle top;
	Rectangle bottom;
	Rectangle left;
	Rectangle right;
	double timer;
	double frametime;
	Rectangle frame;
	Rectangle view;
	int frame_counter;

} Explosion;

typedef struct Bomb
{
	GridPos grid_pos;
	Rectangle hitbox;
	double timer;
	double frametime;
	int power;
	int frame_count;
	Rectangle frame;
	Rectangle view;

} Bomb;

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
	bool dead;
	bool win;
	int direction;
	double speed;
	double final_time;
	int score;


} Player;

//declaração das variáveis globais
//Localização: globals.c
//main globals
extern Rectangle screen;
extern double dt;
extern Camera2D camera;
extern bool debug;
extern bool pause;
extern double timer;
extern GameState state;
extern Vector2 mouse_pos;
extern Font custom_font;
extern double minutes;
extern double seconds;
extern int final_score;

//audio globals

extern Music menu_theme;
extern Music level_music;

//Menu
extern Rectangle exit_menu;
extern Rectangle play;

//player globals
extern Player player;
extern double frametime;
extern int cur_frame;
extern int animation_index;
extern Rectangle camera_bounds;
extern Sound footstep_sfx;

//Ui globals
extern Texture2D clock_sprite;
extern Texture2D wallet_sprite;

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
extern bool level_loaded;
extern GridPos portal_tile;
extern Texture2D background;
extern int bomb_density;

//explosion globals
extern Explosion explosion_buffer[MAX_EXPLOSIONS];
extern int explosion_qtd ;
extern Texture2D explosion_sheet;

//bombs globals

extern Bomb bombs[MAX_BOMBS];
extern int bombs_qtd;
extern Texture2D bomb_sheet;

//funçoes do jogador 
//Localização: player.c
void PlayerInit();
void PlayerInputHandler();
void DrawPlayer();
void PlayerUpdate();
void IsPlayerMoving();
void PlayerCollision();
void AnimationHandler();
void PutFlag();
GridPos GetTargetTile();
void CameraUpdate();
void PlaceBomb();
void ApplyCollision(Rectangle rect);
void DrawPreviewFlag(GridPos preview);
void DrawPreviewBomb(GridPos preview);

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

void MinesUpdate();
void DetonateMine(int minefild_index, int power);

//Funcoes de explosoes
//local : explosions.c

int CreateExplosion(GridPos origin, int power);
Rectangle GetExplosionRight(int power, Rectangle center, GridPos grid_pos);
Rectangle GetExplosionLeft(int power, Rectangle center, GridPos grid_pos);
Rectangle GetExplosionTop(int power, Rectangle center, GridPos grid_pos);
Rectangle GetExplosionBottom(int power, Rectangle center, GridPos grid_pos);
void ExplosionsUpdate();
void DeleteExplosion(int delete_index);
bool IsRectExploded(Rectangle target);
bool CheckExplosionCollision(Explosion explosion, Rectangle target);
int GetEplosionPower(Rectangle target);
void DrawExCenter(Explosion *expo);
void DrawExRight(Explosion *expo);
void DrawExLeft(Explosion *expo);
void DrawExTop(Explosion *expo);
void DrawExBottom(Explosion *expo);
void DrawExplosions();
void AnimateExplosion(Explosion *expo);


//Funcoes de bombas
//local : bombs.c

void CreateBomb(GridPos grid_pos);
void BombUpdate();
void DeleteBomb(int bomb_index);
void AnimateBomb(Bomb *bomb);
void RenderBomb(Bomb *bomb);
void DrawBombs();

//funções de sistema
//Localização: system.c

void ResetGame();
int GetTileType(GridPos tile, int type);
GridPos GetMatrixEnd(GridPos origin, int radius);
GridPos GetMatrixBegin(GridPos origin, int radius);
void InputHandler(int input);
int TileDistance(GridPos a, GridPos b);
bool ValidateGridPos(GridPos posisition);
void DrawBackground();

//funções dos menus
//localização : menus.c

void StartMenu();

//funcao principal do jogo
// localização game.c
void Game();
void DeathScreen();
void VictoryScreen();
void PauseMenu();

//funcoes da pontuação
//localização : score.c

int GetTimeBonus();
int GetRevealedTiles();
int GetFlagedMines();
void GetFinalScore();
