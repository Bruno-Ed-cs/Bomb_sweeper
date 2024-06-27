#include "globals.h"

int CreateExplosion(GridPos origin, int power)
{
    explosion_qtd++;

    if (explosion_qtd > MAX_EXPLOSIONS) return 1;

    explosion_buffer[explosion_qtd -1].grid_pos = origin;
    explosion_buffer[explosion_qtd -1].timer = 1.0f;
    explosion_buffer[explosion_qtd -1].power = power;
    explosion_buffer[explosion_qtd -1].center = (Rectangle){tilemap[origin.y][origin.x].tile.x,
                                                            tilemap[origin.y][origin.x].tile.y,
                                                            TILE_SIZE, TILE_SIZE};
    explosion_buffer[explosion_qtd -1].right = GetExplosionRight(power, explosion_buffer[explosion_qtd -1].center, origin);
    explosion_buffer[explosion_qtd -1].left = GetExplosionLeft(power, explosion_buffer[explosion_qtd -1].center, origin);

    explosion_buffer[explosion_qtd -1].bottom = GetExplosionBottom(power, explosion_buffer[explosion_qtd -1].center, origin);
    explosion_buffer[explosion_qtd -1].top = GetExplosionTop(power, explosion_buffer[explosion_qtd -1].center, origin);
    


    return 0;

};

void ExplosionsUpdate()
{
    for (int i = 0; i < explosion_qtd; i++)
    {
        explosion_buffer[i].timer -= dt;

        if (explosion_buffer[i].timer <= 0)
        {

            DeleteExplosion(i);
        }
    }

};

void DeleteExplosion(int delete_index)
{

    for (int i = delete_index; i < explosion_qtd; i++)
    {
        explosion_buffer[i] = explosion_buffer[i +1];
    }

    explosion_qtd--;
};

bool IsRectExploded(Rectangle target)
{
    bool exploded = false;

    for (int i = 0; i < explosion_qtd; i++)
    {

        if (CheckCollisionRecs(target, explosion_buffer[i].top)) exploded = true;
        if (CheckCollisionRecs(target, explosion_buffer[i].bottom)) exploded = true;
        if (CheckCollisionRecs(target, explosion_buffer[i].left)) exploded = true;
        if (CheckCollisionRecs(target, explosion_buffer[i].center)) exploded = true;
        if (CheckCollisionRecs(target, explosion_buffer[i].right)) exploded = true;

    }

    return exploded;

}

bool CheckExplosionCollision(Explosion explosion, Rectangle target)
{
    bool exploded = false;

    if (CheckCollisionRecs(target, explosion.top)) exploded = true;
    if (CheckCollisionRecs(target, explosion.bottom)) exploded = true;
    if (CheckCollisionRecs(target, explosion.left)) exploded = true;
    if (CheckCollisionRecs(target, explosion.center)) exploded = true;
    if (CheckCollisionRecs(target, explosion.right)) exploded = true;


    return exploded;


}

int GetEplosionPower(Rectangle target)
{
    int power = 0;

    for (int i = 0; i < explosion_qtd; i++)
    {

        if (CheckExplosionCollision(explosion_buffer[i], target))
        {
            power = explosion_buffer[i].power;
        }
        
    }

    return power;

}

Rectangle GetExplosionRight(int power, Rectangle center, GridPos grid_pos)
{
    double x = center.x +TILE_SIZE;
    double y = center.y;
    double width = 0;
    double height = TILE_SIZE;

    int range = 0;

    for (int i = 0; i < power; i++)
    {
        if (!ValidateGridPos((GridPos){grid_pos.x + (i + 1), grid_pos.y}))
        {
            break;
        }else
        {
            if (ValidateGridPos((GridPos){grid_pos.x + (i + 1), grid_pos.y}) && tilemap[grid_pos.y][grid_pos.x + (i + 1)].type == WALL)
            {
                break;
            }

            range++;
        }
    }

    width = TILE_SIZE * range;

    return (Rectangle){x, y, width, height};

};

Rectangle GetExplosionLeft(int power, Rectangle center, GridPos grid_pos)
{
    double x = 0;
    double y = center.y;
    double width = 0;
    double height = TILE_SIZE;

    int range = 0;

    for (int i = 0; i < power; i++)
    {
        if (!ValidateGridPos((GridPos){grid_pos.x - (i + 1), grid_pos.y}))
        {
            break;
        }else
        {
            if (ValidateGridPos((GridPos){grid_pos.x - (i + 1), grid_pos.y}) && tilemap[grid_pos.y][grid_pos.x - (i + 1)].type == WALL)
            {
                break;
            }

            range++;
        }
    }

    width = TILE_SIZE * range;
    x = center.x - (TILE_SIZE * range);

    return (Rectangle){x, y, width, height};

};

Rectangle GetExplosionTop(int power, Rectangle center, GridPos grid_pos)
{
    double x = center.x;
    double y = 0;
    double width = TILE_SIZE;
    double height = 0;

    int range = 0;

    for (int i = 0; i < power; i++)
    {
        if (!ValidateGridPos((GridPos){grid_pos.x, grid_pos.y - (i + 1)}))
        {
            break;
        }else
        {
            if (ValidateGridPos((GridPos){grid_pos.x, grid_pos.y - (i + 1)}) && tilemap[grid_pos.y - (i + 1)][grid_pos.x].type == WALL)
            {
                break;
            }

            range++;
        }
    }

    height = TILE_SIZE * range;
    y = center.y - (TILE_SIZE * range);

    return (Rectangle){x, y, width, height};

};

Rectangle GetExplosionBottom(int power, Rectangle center, GridPos grid_pos)
{
    double x = center.x;
    double y = center.y + TILE_SIZE;
    double width = TILE_SIZE;
    double height = 0;

    int range = 0;

    for (int i = 0; i < power; i++)
    {
        if (!ValidateGridPos((GridPos){grid_pos.x, grid_pos.y + (i + 1)}))
        {
            break;
        }else
        {
            if (ValidateGridPos((GridPos){grid_pos.x, grid_pos.y + (i + 1)}) && tilemap[grid_pos.y + (i + 1)][grid_pos.x].type == WALL)
            {
                break;
            }

            range++;
        }
    }

    height = TILE_SIZE * range;

    return (Rectangle){x, y, width, height};

};
