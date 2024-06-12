#include "globals.h"

void InitMap()
{

    tilemap = malloc((map_height * sizeof(Tile *)));
    if (tilemap == NULL) {
        fprintf(stderr, "Memory allocation failed for tilemap\n");
        exit(1);
    }


    for (int i = 0; i < map_height; i++) {
        tilemap[i] = malloc(map_width * sizeof(Tile));
        if (tilemap == NULL) {
            fprintf(stderr, "Memory allocation failed for tilemap[%d]\n", i);
            exit(1);
        }
    }

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


void PopulateTilemap()
{
    qtd_floor = 0;
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++) {

            tilemap[i][j].visible = true;
            tilemap[i][j].tile_pos = (GridPos){j, i};
            tilemap[i][j].tile = (Rectangle){world_origin.x + (j * TILE_SIZE), world_origin.y + (i * TILE_SIZE), TILE_SIZE, TILE_SIZE};
            tilemap[i][j].sorrounding_mines = 0;

            switch (map[i][j]) {

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

void MineListInit()
{
    minefild = malloc(sizeof(Mine) * qtd_floor);

};

void GenerateMinefild()
{
    srand(time(NULL));
    int prob;

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0;j < map_width; j++) 
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

                        minefild[mine_index] = (Mine){ 
                            (GridPos){ j, i}, 
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

        minefild[mine_index] = (Mine){ 
            (GridPos){ grid_x, grid_y}, 
            (Rectangle){
                tilemap[grid_x][grid_y].tile.x, 
                tilemap[grid_x][grid_y].tile.y,
                TILE_SIZE, TILE_SIZE}};
        mine_index++;


    }


};

void MapMines()
{
    bool is_mine = false;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {

            tilemap[y][x].sorrounding_mines = 0;
        }
    }


    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {

            is_mine = false;

            for (int i = 0; i < mine_index; i++)
            {

                if (minefild[i].grid_pos.x == x && minefild[i].grid_pos.y == y)
                {
                    is_mine = true;
                }

            }

            if (is_mine) tilemap[y][x].sorrounding_mines = -1;
        }
    }

};


void GetSorroundingMines(){
    int mines = 0;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {

            if (tilemap[y][x].sorrounding_mines > -1) {
                mines = 0;

                if (x + 1 < map_width && tilemap[y][x + 1].sorrounding_mines == -1) mines++;
                if (x - 1 >= 0 && tilemap[y][x - 1].sorrounding_mines == -1) mines++;
                if (y + 1 < map_height && x + 1 < map_width && tilemap[y + 1][x + 1].sorrounding_mines == -1) mines++;
                if (y + 1 < map_height && x - 1 >= 0 && tilemap[y + 1][x - 1].sorrounding_mines == -1) mines++;
                if (y + 1 < map_height && tilemap[y + 1][x].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && x + 1 < map_width && tilemap[y - 1][x + 1].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && x - 1 >= 0 && tilemap[y - 1][x - 1].sorrounding_mines == -1) mines++;
                if (y - 1 >= 0 && tilemap[y - 1][x].sorrounding_mines == -1) mines++;

                tilemap[y][x].sorrounding_mines = mines;
            }
        }
    }
}

void RenderMines()
{
    tile_frame.x = TILE_SIZE * 2; 

    for (int i = 0; i < mine_index; i++) {

        tile_view.x = minefild[i].hitbox.x;

        tile_view.y = minefild[i].hitbox.y;


        DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);
    }

};


void RevealTiles(GridPos tile_pos)
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
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y +1)});
            }

            if ((tile_pos.y -1) >= 0 && 
                (tile_pos.y -1) < map_height &&
                (tile_pos.x ) >= 0 && 
                (tile_pos.x ) < map_width)
            {
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y -1)});
            }

            if ((tile_pos.y ) >= 0 && 
                (tile_pos.y ) < map_height &&
                (tile_pos.x +1) >= 0 && 
                (tile_pos.x +1) < map_width)
            {
                RevealTiles((GridPos){(tile_pos.x +1), tile_pos.y});
            }

            if ((tile_pos.y ) >= 0 && 
                (tile_pos.y ) < map_height &&
                (tile_pos.x -1) >= 0 && 
                (tile_pos.x -1) < map_width)
            {
                RevealTiles((GridPos){(tile_pos.x -1), tile_pos.y});
            }
        }
    }

};

void ResetLevel() 
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

    MineListInit(); 
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();


}
