#include "globals.h"
#include <stdbool.h>

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

Rectangle tile_frame = {0, 0, TILE_SIZE, TILE_SIZE};
Rectangle tile_view = {0, 0, TILE_SIZE, TILE_SIZE};
Texture2D tileset = {0}; 
int qtd_floor = 0;
int mine_index = 0;
GridPos spawn_tile = {1, 1};
Vector2 world_origin = {0, 0};
int map_width = 10;
int map_height = 10;
extern Player player;

Tile ** InitMap()
{

    Tile **tilemap = malloc((map_width * sizeof(Tile *)));



    for (int i = 0; i < map_height; i++) {
        tilemap[i] = malloc(map_width * sizeof(Tile));
    }


    return tilemap;

}


int **InitOrigin()
{
    // Allocate memory for the origin array
    int **origin = malloc(map_height * sizeof(int *));
    if (origin == NULL) {
        fprintf(stderr, "Memory allocation failed for origin\n");
        exit(1);
    }

    for (int i = 0; i < map_height; i++) {
        origin[i] = malloc(map_width * sizeof(int));
        if (origin[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for origin[%d]\n", i);
            exit(1);
        }
    }

    // Populate the origin array with values from the map
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            origin[i][j] = map[i][j];
        }
    }

    return origin;
}


void PopulateTilemap(Tile **tilemap, int **origin)
{
    qtd_floor = 0;
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++) {

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

void GenerateMinefild(Mine *mine_arr, Tile **tilemap)
{
    srand(time(NULL));
    int prob;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0;j < 10; j++) 
        {
            if (!( (i == player.spawn.y && j == player.spawn.x) ||
                (i == player.spawn.y + 1 && j == player.spawn.x + 1) ||
                (i == player.spawn.y + 1 && j == player.spawn.x - 1) ||
                (i == player.spawn.y + 1 && j == player.spawn.x) ||
                (i == player.spawn.y - 1 && j == player.spawn.x + 1) ||
                (i == player.spawn.y - 1 && j == player.spawn.x - 1) ||
                (i == player.spawn.y - 1 && j == player.spawn.x) ||
                (i == player.spawn.y && j == player.spawn.x + 1) ||
                (i == player.spawn.y && j == player.spawn.x - 1) ))            //if para deixar os espaços ao redor do spawn do jogador sem minas
            //eu sei que é uma atrocidade
            {

                prob = rand() % 100;
                if (tilemap[i][j].type == FLOOR)
                {
                    if (prob <= 40)
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

void MapMines(Mine * minefild, Tile **tilemap)
{
    bool is_mine = false;

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {

            tilemap[y][x].sorrounding_mines = 0;
        }
    }


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


void GetSorroundingMines(Tile **tilemap) {
    int mines = 0;
    int max_tile = map_height;  

    for (int y = 0; y < max_tile; y++) {
        for (int x = 0; x < map_width; x++) {

            if (tilemap[y][x].sorrounding_mines > -1) {
                mines = 0;

                if (x + 1 < max_tile && tilemap[y][x + 1].sorrounding_mines == -1) mines++;
                if (x - 1 >= 0 && tilemap[y][x - 1].sorrounding_mines == -1) mines++;
                if (y + 1 < max_tile && x + 1 < map_width && tilemap[y + 1][x + 1].sorrounding_mines == -1) mines++;
                if (y + 1 < max_tile && x - 1 >= 0 && tilemap[y + 1][x - 1].sorrounding_mines == -1) mines++;
                if (y + 1 < max_tile && tilemap[y + 1][x].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && x + 1 < map_width && tilemap[y - 1][x + 1].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && x - 1 >= 0 && tilemap[y - 1][x - 1].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && tilemap[y - 1][x].sorrounding_mines == -1) mines++;

                tilemap[y][x].sorrounding_mines = mines;
            }
        }
    }
}

void RenderMines(Mine *minefild)
{
    tile_frame.x = TILE_SIZE * 2; 

    for (int i = 0; i < mine_index; i++) {

        tile_view.x = minefild[i].hitbox.x;

        tile_view.y = minefild[i].hitbox.y;


        DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);
    }

};


void RevealTiles(GridPos tile_pos, Tile **tilemap)
{

    if (tilemap[tile_pos.y][tile_pos.x].type == FLOOR && !tilemap[tile_pos.y][tile_pos.x].visible)
    {
        tilemap[tile_pos.y][tile_pos.x].visible = true;

        if (tilemap[tile_pos.y][tile_pos.x].sorrounding_mines == 0)
        {
            if ((tile_pos.y +1) >= 0 && 
                (tile_pos.y +1) < map_height &&
                (tile_pos.x ) >= 0 && 
                (tile_pos.x ) < map_width)
            {
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y +1)}, tilemap);
            }

            if ((tile_pos.y -1) >= 0 && 
                (tile_pos.y -1) < map_height &&
                (tile_pos.x ) >= 0 && 
                (tile_pos.x ) < map_width)
            {
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y -1)}, tilemap);
            }

            if ((tile_pos.y ) >= 0 && 
                (tile_pos.y ) < map_height &&
                (tile_pos.x +1) >= 0 && 
                (tile_pos.x +1) < map_width)
            {
                RevealTiles((GridPos){(tile_pos.x +1), tile_pos.y}, tilemap);
            }

            if ((tile_pos.y ) >= 0 && 
                (tile_pos.y ) < map_height &&
                (tile_pos.x -1) >= 0 && 
                (tile_pos.x -1) < map_width)
            {
                RevealTiles((GridPos){(tile_pos.x -1), tile_pos.y}, tilemap);
            }
        }
    }

};

Mine * ResetLevel(Mine *minefild, Tile **tilemap)
{
    mine_index = 0;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (tilemap[y][x].type == FLOOR)
            {
                tilemap[y][x].visible = false;
            }
        }
    }

    minefild = MineListInit(); 
    GenerateMinefild(minefild, tilemap);
    MapMines(minefild, tilemap);
    GetSorroundingMines(tilemap);

    return minefild;

};
