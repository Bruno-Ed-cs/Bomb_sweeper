#include "globals.h"

int CreateExplosion(GridPos origin, int power)
{
    explosion_qtd++;

    if (explosion_qtd > MAX_EXPLOSIONS) return 1;

    Explosion *expo = &explosion_buffer[explosion_qtd -1];

    expo->grid_pos = origin;
    expo->timer = 0.75f;
    expo->power = power;
    expo->center = (Rectangle){tilemap[origin.y][origin.x].tile.x,
                                                            tilemap[origin.y][origin.x].tile.y,
                                                            TILE_SIZE, TILE_SIZE};
    expo->right = GetExplosionRight(power, explosion_buffer[explosion_qtd -1].center, origin);
    expo->left = GetExplosionLeft(power, explosion_buffer[explosion_qtd -1].center, origin);
    expo->bottom = GetExplosionBottom(power, explosion_buffer[explosion_qtd -1].center, origin);
    expo->top = GetExplosionTop(power, explosion_buffer[explosion_qtd -1].center, origin);
    expo->frametime = 0;
    expo->frame_counter = 0;
    expo->view = (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE};
    expo->frame = (Rectangle){0, 0, TILE_SIZE, TILE_SIZE};

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

void DrawExCenter(Explosion *expo)
{
    expo->frame.x = 0;
    expo->view.x = expo->center.x;
    expo->view.y = expo->center.y;

    DrawTexturePro(explosion_sheet,expo->frame, expo->view, (Vector2){0,0}, 0, WHITE);

}

void DrawExRight(Explosion *expo)
{
    int length = (int)(expo->right.width) / TILE_SIZE;
    expo->view.y = expo->right.y + (expo->center.height/2);

    for (int i = 0; i < length; i++)
    {
        if ((i +1) == length)
        {
            expo->frame.x = TILE_SIZE *2;

        } else 
        {
            expo->frame.x = TILE_SIZE;
        }

        expo->view.x = expo->right.x + (i * TILE_SIZE) + (expo->center.width/2) ;

        DrawTexturePro(explosion_sheet ,expo->frame, expo->view, (Vector2){expo->view.width/2, expo->view.height/2}, 0.0f, WHITE);

    }

}

void DrawExLeft(Explosion *expo)
{
    int length = (int)(expo->left.width) / TILE_SIZE;
    expo->view.y = expo->left.y + (expo->center.height/2);

    for (int i = 0; i < length; i++)
    {
        if (i == 0)
        {
            expo->frame.x = TILE_SIZE *2;

        } else 
        {
            expo->frame.x = TILE_SIZE;
        }

        expo->view.x = (expo->left.x + (i * TILE_SIZE));
        expo->view.x += (expo->center.width/2);

        DrawTexturePro(explosion_sheet ,expo->frame, expo->view, (Vector2){expo->view.width/2, expo->view.height/2}, 180.0f, WHITE);

    }

}

void DrawExBottom(Explosion *expo)
{
    int length = (int)(expo->bottom.height) / TILE_SIZE;
    expo->view.x = expo->bottom.x + (expo->center.width/2);

    for (int i = 0; i < length; i++)
    {
        if ((i +1) == length)
        {
            expo->frame.x = TILE_SIZE *2;

        } else 
        {
            expo->frame.x = TILE_SIZE;
        }

        expo->view.y = (expo->bottom.y + (i * TILE_SIZE));
        expo->view.y += (expo->center.height/2);

        DrawTexturePro(explosion_sheet ,expo->frame, expo->view, (Vector2){expo->view.width/2, expo->view.height/2}, 90.0f, WHITE);

    }

}

void DrawExTop(Explosion *expo)
{
    int length = (int)(expo->top.height) / TILE_SIZE;
    expo->view.x = expo->top.x + (expo->center.width/2);

    for (int i = 0; i < length; i++)
    {
        if (i == 0)
        {
            expo->frame.x = TILE_SIZE *2;

        } else 
        {
            expo->frame.x = TILE_SIZE;
        }

        expo->view.y = (expo->top.y + (i * TILE_SIZE));
        expo->view.y += (expo->center.height/2);

        DrawTexturePro(explosion_sheet ,expo->frame, expo->view, (Vector2){expo->view.width/2, expo->view.height/2}, 270.0f, WHITE);

    }

}

void AnimateExplosion(Explosion *expo)
{
    expo->frametime += dt;


        expo->frame_counter = (int)((expo->frametime / 0.75f) * 9.0f);
        
        if (expo->frame_counter >= 9)
        {
            expo->frame_counter = 8;
        }
        
        expo->frame.y = TILE_SIZE * expo->frame_counter;

}

void DrawExplosions()
{
    for (int i = 0; i < explosion_qtd; i++)
    {

        AnimateExplosion(&explosion_buffer[i]);

        if (debug)
        {
        DrawRectangleRec(explosion_buffer[i].center, RED);
        DrawRectangleRec(explosion_buffer[i].right, GREEN);
        DrawRectangleRec(explosion_buffer[i].left, YELLOW);
        DrawRectangleRec(explosion_buffer[i].top, PURPLE);
        DrawRectangleRec(explosion_buffer[i].bottom, BLUE);
        }

        DrawExCenter(&explosion_buffer[i]);

        if (explosion_buffer[i].right.width > 0) DrawExRight(&explosion_buffer[i]);
        if (explosion_buffer[i].left.width > 0) DrawExLeft(&explosion_buffer[i]);
        if (explosion_buffer[i].bottom.height > 0) DrawExBottom(&explosion_buffer[i]);
        if (explosion_buffer[i].top.height > 0) DrawExTop(&explosion_buffer[i]);
    }



}
