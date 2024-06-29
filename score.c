#include "globals.h"

int GetFlagedMines()
{
    int qtd = 0;

    for (int i = 0; i < mine_index; i++) 
    {

        if (!ValidateGridPos(minefild[i].grid_pos)) 
        {
            printf("Invalid gridpo\n");
            continue;
        }

        int x = minefild[i].grid_pos.x, y = minefild[i].grid_pos.y;

        bool flaged = tilemap[y][x].flaged;
        bool detonated = tilemap[y][x].bombed;

        if (flaged && !detonated)
        {
            qtd++;

        }


    }

    return qtd;

}

int GetRevealedTiles()
{
    int revealed_tiles = 0;

    for (int y = 0; y < map_height; y++) 
    {
        for (int x = 0; x < map_width; x++) 
        {
            if (tilemap[y][x].type == FLOOR)
            {
                if (tilemap[y][x].visible) revealed_tiles++;

            }
        }

    }

    return revealed_tiles;

}

int GetTimeBonus()
{
    int bonus = ((qtd_floor) + (mine_index * 50)) / ((GetFlagedMines() +1) / (timer +1));

    return bonus;

}

void GetFinalScore()
{
    final_score = player.score + GetTimeBonus() + (GetFlagedMines() * 150);
}

