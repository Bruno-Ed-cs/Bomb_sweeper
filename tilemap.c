#include "globals.h"
#include "include/raylib.h"
#include <stdio.h>
#include <string.h>

void AllocMap() {

    tilemap = malloc(map_height * sizeof(Tile *));
    if (tilemap == NULL) {
        fprintf(stderr, "Memory allocation failed for tilemap\n");
        exit(1);
    }

    for (int i = 0; i < map_height; i++) {
        tilemap[i] = malloc(map_width * sizeof(Tile));
        if (tilemap[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for tilemap[%d]\n", i);
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(tilemap[j]);
            }
            free(tilemap);
            exit(1);
        }
    }
}

void LoadLevel(char *level)
{
    qtd_floor = 0;
    
    FILE *file = fopen(level, "r");// abre o arquivo do json
    
    //detecta se o arquivo foi carregado
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", level);
        return;
    }

    fseek(file, 0, SEEK_END);//coloca o ponteiro do arquivo no final
    long fileSize = ftell(file);//pegamos o tamanho do arquivo
    fseek(file, 0, SEEK_SET);//colocamos o ponteiro de volta ao inicio

    char *buffer = (char *)malloc(fileSize + 1);// criamos um buffer para colocar o arquivo
    fread(buffer, 1, fileSize, file); // colocamos o arquivo no buffer
    buffer[fileSize] = '\0'; // colocamos o finalizador no buffer

    fclose(file); //fechamos o arquivo ja que ja carregamos ele no buffer

    cJSON *json = cJSON_Parse(buffer); //carrgamos o json

    // verifivação para ver se o carregamento foi bem sucedido
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        free(buffer);
        return;
    }


    cJSON *map = cJSON_GetObjectItem(json, "map");// carregamos a matriz do mapa
    cJSON *spawn_x = cJSON_GetObjectItem(json, "spawn_x");
    cJSON *spawn_y = cJSON_GetObjectItem(json, "spawn_y");
    cJSON *density = cJSON_GetObjectItem(json, "bomb_density");
    cJSON *music = cJSON_GetObjectItem(json, "music");
    cJSON *level_background= cJSON_GetObjectItem(json, "background");

    map_height = cJSON_GetArraySize(map); // pegamos o tamanho da matriz
    map_width = cJSON_GetArraySize(cJSON_GetArrayItem(map, 0)); // pegamos o tamanho da linha
    bomb_density = density->valueint;

    UnloadTexture(background);
    UnloadMusicStream(level_music);
    level_music = LoadMusicStream(music->valuestring);
    background = LoadTexture(level_background->valuestring);

    spawn_tile = (GridPos){spawn_x->valueint, spawn_y->valueint}; //pegamos o tile de nascimento
    AllocMap();

    level_bounds.x = world_origin.x;
    level_bounds.y = world_origin.y;
    level_bounds.width = map_width * TILE_SIZE; 
    level_bounds.height = map_height * TILE_SIZE;

    for (int i = 0; i < map_height; i++)
    {
        cJSON *linha = cJSON_GetArrayItem(map, i);

        for (int j = 0; j < map_width; j++) {

            cJSON *item = cJSON_GetArrayItem(linha, j);
            int tile = item->valueint;

            tilemap[i][j].visible = true;
            tilemap[i][j].flaged = false;
            tilemap[i][j].bombed = false;
            tilemap[i][j].tile_pos = (GridPos){j, i};
            tilemap[i][j].tile = (Rectangle){world_origin.x + (j * TILE_SIZE), world_origin.y + (i * TILE_SIZE), TILE_SIZE, TILE_SIZE};
            tilemap[i][j].sorrounding_mines = 0;

            switch (tile) {

                case PORTAL: tilemap[i][j].type = PORTAL;
                    portal_tile = (GridPos){j, i};
                break;

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


    cJSON_Delete(json);
    free(buffer);

    level_loaded = true;

};

void UnloadLevel()
{
    for (int i = 0; i < map_height; i++) {

        free(tilemap[i]);
    
    }
    printf("Level unloaded\n");
    level_loaded = false;

};

void MineListInit()
{
    minefild = malloc(sizeof(Mine) * qtd_floor);

};

void GenerateMinefild()
{
    SetRandomSeed(time(NULL));
    int prob;
    int treshold = bomb_density;

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0;j < map_width; j++) 
        {
            if (TileDistance(spawn_tile, (GridPos){j, i}) > 1 && TileDistance(portal_tile, (GridPos){j, i}) > 1)
            {

                prob = GetRandomValue(0, 1000);
                if (tilemap[i][j].type == FLOOR)
                {
                    if (prob <= treshold)
                    {

                        minefild[mine_index] = (Mine){ 
                            (GridPos){ j, i}, 
                            (Rectangle){
                                tilemap[i][j].tile.x, 
                                tilemap[i][j].tile.y,
                                TILE_SIZE, TILE_SIZE},
                                false,
                                false,
                                1,
                                0.25f};


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

        grid_x = GetRandomValue(0, 10);
        grid_y = GetRandomValue(0, 10);

        while (tilemap[grid_x][grid_y].type != FLOOR) {

            grid_x = GetRandomValue(0, 10);
            grid_y = GetRandomValue(0, 10);

        }

        minefild[mine_index] = (Mine){ 
            (GridPos){ grid_x, grid_y}, 
            (Rectangle){
                tilemap[grid_x][grid_y].tile.x, 
                tilemap[grid_x][grid_y].tile.y,
                TILE_SIZE, TILE_SIZE}, false, false, 1, 0.25f};
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
    if (debug)
    {
        for (int i = 0; i < mine_index; i++) {

                if (minefild[i].detonated)
                {

                    tile_frame.x = TILE_SIZE * 5; 
                } else {

                    tile_frame.x = TILE_SIZE * 2; 
                }
            if (CheckCollisionRecs(minefild[i].hitbox, camera_bounds) )
            {
                tile_view.x = minefild[i].hitbox.x;

                tile_view.y = minefild[i].hitbox.y;


                DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);
            }
        }
    } else 
    {
        for (int i = 0; i < mine_index; i++) {
            if (CheckCollisionRecs(minefild[i].hitbox, camera_bounds))
            {
                if (minefild[i].detonated && minefild[i].fuse <= 0)
                {

                    tile_frame.x = TILE_SIZE * 5; 
                } else {

                    tile_frame.x = TILE_SIZE * 2; 
                }
                int x = minefild[i].grid_pos.x;

                int y = minefild[i].grid_pos.y;
                //printf("x: %d, y: %d\n", x, y);
                if (!ValidateGridPos((GridPos){x,y}))
                {
                    printf("Invalid tilemap\n");
                    printf("%d\n", i);
                    continue;
                }


                tile_view.x = minefild[i].hitbox.x;

                tile_view.y = minefild[i].hitbox.y;

                if(tilemap[y][x].visible == true && !minefild[i].detonated)
                {
                    DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);
                }
            }

        }
    }


};

void MinesUpdate()
{
    for (int i = 0; i < mine_index; i++) {


        bool explosion_collision = false;
        int previous_power = 0;
        
        for (int j = 0; j < explosion_qtd; j++) {

            if (CheckExplosionCollision(explosion_buffer[j], minefild[i].hitbox))
            {
                explosion_collision = true;
                previous_power = explosion_buffer[j].power;

            }
        
        }

        for (int j = 0; j < bombs_qtd; j++) {

            if (CheckCollisionRecs(bombs[j].hitbox, minefild[i].hitbox))
            {
                explosion_collision = true;
                minefild[i].power++;

            }
        }

        if(!minefild[i].detonated && CheckCollisionPointRec(player.position, minefild[i].hitbox) && !minefild[i].exploding)
        {

            minefild[i].exploding = true;
        }
        

        if(!minefild[i].detonated && explosion_collision && !minefild[i].exploding)
        {
            previous_power++;
            minefild[i].power += previous_power;
            if (minefild[i].power >= 5) minefild[i].power = 5;
            minefild[i].exploding = true;


        }

        if (minefild[i].exploding)
        {
            if (minefild[i].fuse > 0)
            {
                minefild[i].fuse -= dt;

            }
        }

        if (minefild[i].exploding && minefild[i].fuse <= 0)
        {

            DetonateMine(i, minefild[i].power);

        }
    }

}

void DetonateMine(int minefild_index, int power)
{
    GridPos pos = minefild[minefild_index].grid_pos;
    minefild[minefild_index].detonated = true;

    if(ValidateGridPos(pos) && minefild[minefild_index].fuse <= 0) 
    {
        CreateExplosion(pos, power);
        tilemap[pos.y][pos.x].visible = true;
        tilemap[pos.y][pos.x].bombed = true;

    }else 
    {
        printf("invalid detonation position\n");
    }

    minefild[minefild_index].exploding = false;


}


void RevealTiles(GridPos tile_pos)
{

    if (tilemap[tile_pos.y][tile_pos.x].type == FLOOR && !tilemap[tile_pos.y][tile_pos.x].visible)
    {
        tilemap[tile_pos.y][tile_pos.x].visible = true;

        player.score += 5;

        if (tilemap[tile_pos.y][tile_pos.x].sorrounding_mines == 0)
        {

            if (ValidateGridPos((GridPos){tile_pos.x, tile_pos.y +1}))
            {
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y +1)});
            }

            if (ValidateGridPos((GridPos){tile_pos.x, tile_pos.y -1}))
            {
                RevealTiles((GridPos){tile_pos.x, (tile_pos.y -1)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x -1, tile_pos.y}))
            {
                RevealTiles((GridPos){tile_pos.x -1, (tile_pos.y)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x -1, tile_pos.y -1}))
            {
                RevealTiles((GridPos){tile_pos.x -1, (tile_pos.y -1)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x -1, tile_pos.y +1}))
            {
                RevealTiles((GridPos){tile_pos.x -1, (tile_pos.y +1)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x +1, tile_pos.y}))
            {
                RevealTiles((GridPos){tile_pos.x +1, (tile_pos.y)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x +1, tile_pos.y +1}))
            {
                RevealTiles((GridPos){tile_pos.x +1, (tile_pos.y +1)});
            }


            if (ValidateGridPos((GridPos){tile_pos.x +1, tile_pos.y -1}))
            {
                RevealTiles((GridPos){tile_pos.x +1, (tile_pos.y -1)});
            }


        }
    }

};

void DrawTiles(GridPos start, GridPos end)
{

    for (int i = start.y; i < end.y; i++) 
    {
        for (int j = start.x; j < end.x; j++) {

            tile_view = tilemap[i][j].tile;

            switch (tilemap[i][j].type) {

                case WALL:
                    tile_frame.x = TILE_SIZE;
                    tile_frame.y = 0;
                break;

                case FLOOR:
                    tile_frame.x = 0;
                    tile_frame.y = 0;
                break;

                case PORTAL:
                    tile_frame.x = 0;
                    tile_frame.y = 0;
                break;


                case AIR:
                    tile_frame.x = TILE_SIZE * 4;
                    tile_frame.y = 0;
                break;
            
            }

            if (tilemap[i][j].visible)
            {
                Color color = PURPLE;
                if (tilemap[i][j].type == PORTAL) color = GREEN;

                DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, color);

            } else {

                DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, ColorTint(PURPLE, GRAY));

            }

            char num[10];
            sprintf(num, "%d" ,tilemap[i][j].sorrounding_mines);

            if (tilemap[i][j].type == FLOOR && tilemap[i][j].sorrounding_mines > 0 && tilemap[i][j].visible && !tilemap[i][j].flaged)
            {
                DrawText(num, (tilemap[i][j].tile.x + (TILE_SIZE /2.0f)) -2, (tilemap[i][j].tile.y + (TILE_SIZE /2.0f)) - 5, 11, WHITE);
            }

            if (tilemap[i][j].bombed)
            {
                tile_frame.y = 0;
                tile_frame.x = TILE_SIZE * 5;


                DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, WHITE);

            }

            if (tilemap[i][j].flaged == true)
            {

                tile_frame.y = 0;
                tile_frame.x = TILE_SIZE * 3;
                DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, WHITE);
            }

        }

    }



};
