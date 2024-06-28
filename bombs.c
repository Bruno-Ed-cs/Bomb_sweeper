#include "globals.h"


void CreateBomb(GridPos grid_pos)
{

    bombs_qtd++;
    if (bombs_qtd > MAX_BOMBS)
    {
        bombs_qtd = MAX_BOMBS;
        return;
    }

    Bomb *bomb = &bombs[bombs_qtd -1];

    bomb->grid_pos = grid_pos;
    bomb->hitbox = (Rectangle){tilemap[grid_pos.y][grid_pos.x].tile.x,tilemap[grid_pos.y][grid_pos.x].tile.y, TILE_SIZE, TILE_SIZE};
    bomb->timer = 3.0f;
    bomb->power = 1;
    bomb->frame = (Rectangle){0, 0, 0, 0};

};

void DeleteBomb(int bomb_index)
{

    for (int i = bomb_index; i < bombs_qtd; i++) 
    {
        bombs[i] = bombs[i + 1];

    }

    bombs_qtd--;

};

void BombUpdate()
{
    for (int i = 0; i < bombs_qtd; i++)
    {
        bombs[i].timer -= dt;
        
        for (int j = 0 ; j < explosion_qtd; j++)
        {
            if (CheckExplosionCollision(explosion_buffer[j], bombs[i].hitbox))
            {
                bombs[i].timer = 0;
            }

        };

        if (bombs[i].timer <= 0)
        {
            CreateExplosion(bombs[i].grid_pos, bombs[i].power);
            DeleteBomb(i);

        }
    }

};
