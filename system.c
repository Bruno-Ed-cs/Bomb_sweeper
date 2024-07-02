#include "globals.h"


void InitGame(char * level_path)//Fiz uma funcao para a inicializaçao, para que eu pudesse usar pra reiniciar toda vez que entra no menu
{
    LoadLevel(level_path);
    ResetLevel();
}

void ResetLevel() 
{
    mine_index = 0;
    bombs_qtd = 0;
    explosion_qtd = 0;
    minutes = 0;
    seconds = 0;
    timer = 0;
    pause = false;
    final_score = 0;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (tilemap[y][x].type == FLOOR)
            {
                tilemap[y][x].visible = false;
                tilemap[y][x].flaged = false;
                tilemap[y][x].bombed = false;
            }
        }
    }

    MineListInit(); 
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();
    PlayerInit();


};

void DrawBackground()
{
    double x ,y;

    x = world_origin.x - ((background.width/2.0f) - (level_bounds.width/2.0f)); 
    y = world_origin.y - ((background.height/2.0f) - (level_bounds.height/2.0f)); 

    DrawTextureV(background,(Vector2){x, y} , WHITE);

}


 
void InputHandler(int input)
{
    switch (input) {

        case KEY_P:
            pause = !pause;
        break;


        case KEY_R:

            if(pause) ResetLevel();

        break;

        case KEY_F3:
            debug = !debug;
        break;

    }

};

GridPos GetMatrixBegin(GridPos origin, int radius)
{
    GridPos begining;

    begining.x = origin.x - radius;
    begining.y = origin.y - radius;

    if (begining.x < 0) begining.x = 0;
    if (begining.y < 0) begining.y = 0;

    return begining;

};

GridPos GetMatrixEnd(GridPos origin, int radius)
{
    GridPos end;

    end.x = origin.x + radius;
    end.y = origin.y + radius;

    if (end.x >= map_width) end.x = map_width;
    if (end.y >= map_height) end.y = map_height;

    return end;

};


int GetTileType(GridPos tile, int type)
{

    if (tile.y < 0 || tile.y >= map_height) return 0;
    if (tile.x < 0 || tile.x >= map_width) return 0;

    return tilemap[tile.y][tile.x].type;

};

bool ValidateGridPos(GridPos posisition)
{
    if (posisition.y >= map_height || posisition.y < 0)
        return false;

    if (posisition.x >= map_width || posisition.x < 0)
        return false;

    return true;
};

int TileDistance(GridPos a, GridPos b)
{
    return sqrt((pow(b.x - a.x, 2)) + (pow(b.y - a.y, 2)));

};
