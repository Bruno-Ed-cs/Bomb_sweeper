#include <stdbool.h>
#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#include "globals.h"

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 1, 1, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

Tile tilemap[10][10];
Rectangle tile_frame = {0, 0, TILE_SIZE, TILE_SIZE};
Rectangle tile_view = {0, 0, TILE_SIZE, TILE_SIZE};
Texture2D tileset = {0}; 
int qtd_floor = 0;
int mine_index = 0;
GridPos spawn_tile = {1, 1};
Vector2 world_origin = {0, 0};

void PopulateTilemap(int size, Tile tilemap[size][size], int origin[size][size])
{
    qtd_floor = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {

            tilemap[i][j].visible = true;
            tilemap[i][j].tile_pos = (GridPos){i, j};
            tilemap[i][j].tile = (Rectangle){world_origin.x + (i * TILE_SIZE), world_origin.y + (j * TILE_SIZE), TILE_SIZE, TILE_SIZE};
            tilemap[i][j].sorrounding_mines = 0;

            switch (origin[i][j]) {

                case WALL: tilemap[i][j].type = WALL;
                    break;

                case FLOOR: tilemap[i][j].type = FLOOR;

                    tilemap[i][j].visible = false;
                    qtd_floor++;
                    break;           

                case AIR: tilemap[i][j].type = AIR;
                    break;
            }

        
        }

    }

    tileset = LoadTexture("./assets/sprites/tileset.png");
    

};

Mine * MineListInit()
{
    Mine *mine_array = malloc(sizeof(Mine) * qtd_floor);

    return mine_array;

};

void GenerateMinefild(Mine *mine_arr)
{
    srand(time(NULL));
    int prob;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0;j < 10; j++) 
        {
            prob = rand() % 100;
            if (tilemap[i][j].type == FLOOR)
            {
                if (prob <= 10)
                {

                    mine_arr[mine_index] = (Mine){ 
                        (GridPos){ i, j}, 
                        (Rectangle){
                            tilemap[i][j].tile.x, 
                            tilemap[i][j].tile.y,
                            TILE_SIZE, TILE_SIZE}};

                    mine_index++;
                }
            }
        }
    }

    if (mine_index <= 0)
    {
        int grid_x;
        int grid_y;

        grid_x = rand() % 10;
        grid_y = rand() % 10;

        while (tilemap[grid_x][grid_y].type != FLOOR) {

            grid_x = rand() % 10;
            grid_y = rand() % 10;       
        }

        mine_arr[mine_index] = (Mine){ 
            (GridPos){ grid_x, grid_y}, 
            (Rectangle){
                tilemap[grid_x][grid_y].tile.x, 
                tilemap[grid_x][grid_y].tile.y,
                TILE_SIZE, TILE_SIZE}};
        mine_index++;


    }


};

void MapMines(Mine * minefild)
{
    bool is_mine = false;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {

            is_mine = false;

            for (int i = 0; i < mine_index; i++)
            {

                if (minefild[i].grid_pos.x == x && minefild[i].grid_pos.y == y)
                {
                    is_mine = true;
                }

            }

            if (is_mine) tilemap[x][y].sorrounding_mines = -1;
        }
    }
    
};

void GetSorroundingMines()
{

    int mines = 0;
    int max_tile = 10;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {

            if (tilemap[y][x].sorrounding_mines > -1) {

                if ((x +1 < max_tile && y < max_tile) && tilemap[y][x + 1].sorrounding_mines == -1) mines++;

                if ((x -1 < max_tile && y < max_tile) && tilemap[y][x - 1].sorrounding_mines == -1) mines++;

                if ((x +1 < max_tile && y +1 < max_tile) && tilemap[y + 1][x + 1].sorrounding_mines == -1) mines++;

                if ((x -1 < max_tile && y +1 < max_tile) && tilemap[y + 1][x - 1].sorrounding_mines == -1) mines++;

                if ((x < max_tile && y +1 < max_tile) && tilemap[y + 1][x].sorrounding_mines == -1) mines++;

                if ((x +1 < max_tile && y -1 < max_tile) && tilemap[y -1][x + 1].sorrounding_mines == -1) mines++;

                if ((x -1 < max_tile && y -1 < max_tile) && tilemap[y -1][x - 1].sorrounding_mines == -1) mines++;

                if ((x < max_tile && y -1 < max_tile) && tilemap[y -1][x].sorrounding_mines == -1) mines++;

                tilemap[y][x].sorrounding_mines = mines;
            
            }

            mines = 0;

        }
    }
};


void RenderMines(Mine *minefild)
{
    tile_frame.x = TILE_SIZE * 2; 

    for (int i = 0; i < mine_index; i++) {

        tile_view.x = minefild[i].hitbox.x;

        tile_view.y = minefild[i].hitbox.y;


        DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);
    }

}
