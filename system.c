#include "globals.h"


void ResetGame()//Fiz uma funcao para a inicializaçao, para que eu pudesse usar pra reiniciar toda vez que entra no menu
{
    LoadLevel("./assets/levels/mapa1.json");
    PlayerInit();

    camera_bounds.x = player.position.x - (camera_bounds.width / 2);
    camera_bounds.y = player.position.y - (camera_bounds.height / 2);
    camera.rotation = 0.0f;

    MineListInit();
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();

    timer = 0;
    pause = false;

}

 
void InputHandler(int input)
{
    switch (input) {

        case KEY_P:
            pause = !pause;
        break;


        case KEY_R:

            if(debug) ResetLevel();

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

