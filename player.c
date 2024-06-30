#include "globals.h"
#include "include/raylib.h"

void PlayerInit()
{

    player.hitbox = (Rectangle){INIT_X, INIT_Y, TILE_SIZE -8, TILE_SIZE -8};
    player.frame = (Rectangle){0, 0, TILE_SIZE, TILE_SIZE * 2};
    player.view = (Rectangle){INIT_X, INIT_Y, TILE_SIZE, TILE_SIZE * 2};
    player.speed = 50.0f;
    player.move = false;
    player.dead = false;
    player.win = false;
    player.colliding = false;
    player.direction = DOWN;
    player.previous_pos = (Vector2){0, 0};
    player.spawn = spawn_tile;
    player.grid_pos = player.spawn;
    player.position = (Vector2){tilemap[player.spawn.y][player.spawn.x].tile.x + (TILE_SIZE /2.0f), tilemap[player.spawn.y][player.spawn.x].tile.y + (TILE_SIZE /2.0f) };
    if (!IsTextureReady(player.sprite)) player.sprite = LoadTexture("./assets/sprites/Connor_fodder-sheet.png");
    player.score = 0;
    player.final_time = 0;

};

void IsPlayerMoving()
{
    if (player.position.x == player.previous_pos.x && player.position.y == player.previous_pos.y)
    {
        player.move = false;
    } else 
    {
        player.move = true;
    }

};

void CameraUpdate()
{
    camera_bounds.width = GetScreenToWorld2D((Vector2){screen.width, 0}, camera).x - GetScreenToWorld2D((Vector2) {0,0}, camera).x;
    camera_bounds.height = GetScreenToWorld2D((Vector2){0, screen.height}, camera).y - GetScreenToWorld2D((Vector2) {0,0}, camera).y;


    camera_bounds.y = player.position.y - (camera_bounds.height / 2);
    camera_bounds.x = player.position.x - (camera_bounds.width / 2);

/** todo: isso tudo
    float cameraFocusOffsetX = TILE_SIZE * 9;
    float cameraFocusOffsetY = TILE_SIZE * 4;

    if (player.position.x <= (level_bounds.width - cameraFocusOffsetX) && player.position.x >= (level_bounds.x + cameraFocusOffsetX))
    {
        camera_bounds.x = player.position.x - (camera_bounds.width / 2);
    }

    if (player.position.y <= (level_bounds.height - cameraFocusOffsetY) && player.position.y >= (level_bounds.y + cameraFocusOffsetY))
    {
        camera_bounds.y = player.position.y - (camera_bounds.height / 2);
    }
    

    if (camera_bounds.x < (level_bounds.x - (TILE_SIZE * 2)))
    {
    
        camera_bounds.x = level_bounds.x - (TILE_SIZE * 2);

    }
 
    if (camera_bounds.y <= (level_bounds.y - (TILE_SIZE * 2)))
    {
    
        camera_bounds.y = level_bounds.y - (TILE_SIZE * 2);

    }


//dois ifs problematicos, por enquanto so coloque spawn points fora da parte de baixo da fase
    if ((camera_bounds.y - camera_bounds.height) > (level_bounds.height - (TILE_SIZE * 2)))
    {
    
        camera_bounds.y = (level_bounds.height - camera_bounds.height) - TILE_SIZE * 2;

    }

    if ((camera_bounds.x + camera_bounds.width) > (level_bounds.width + (TILE_SIZE * 2)))
    {
    
        camera_bounds.x = (level_bounds.width - camera_bounds.width) + (TILE_SIZE * 2);
 
    }
 
**/
    camera.target = (Vector2){ player.position.x, player.position.y};
    camera.offset = (Vector2){screen.width/2, screen.height/2};
    camera.zoom = (screen.width / INIT_WIDTH) * 3.5;
};


void PlayerMovement() {

    if (debug)
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            player.position = GetScreenToWorld2D(GetMousePosition(), camera);

        }
    }

    if (IsKeyDown(KEY_W)) {
        player.position.y -= player.speed * dt;

        player.hitbox.y = player.position.y- (player.hitbox.height /2);
        player.direction = UP;
    }
    else if (IsKeyDown(KEY_S) && !(player.colliding)) {
        player.position.y += player.speed * dt;
        player.hitbox.y = player.position.y- (player.hitbox.height /2);
        player.direction = DOWN;
    }
    else if (IsKeyDown(KEY_D) && !(player.colliding)) {
        player.position.x  += player.speed * dt;
        player.hitbox.x = player.position.x- (player.hitbox.width /2);
        player.direction = RIGHT;
    }
    else if(IsKeyDown(KEY_A) && !(player.colliding)) {
        player.position.x -= player.speed * dt;
        player.hitbox.x = player.position.x- (player.hitbox.width /2);
        player.direction = LEFT;
    }

    if (IsKeyPressed(KEY_F))
    {
        PutFlag();
    }

    if (IsKeyPressed(KEY_SPACE))
    {
            PlaceBomb();
    }


};

void AnimationHandler()
{
    frametime += dt;

    if (player.move)
    {

        if (frametime >= (1.0f / 6.0f))
        {


            frametime = 0.0f;
            cur_frame++;

            if(cur_frame >=1)
            {
                if (!IsSoundPlaying(footstep_sfx)) PlaySound(footstep_sfx);
            }

            if (cur_frame >= 3)
            {

                cur_frame = 0;
            }        

        }

    } else {

        cur_frame = 0;
    }

    switch (player.direction) {

        case UP:
            animation_index = 1;
            
            player.frame.width = TILE_SIZE; 
        break;

        case DOWN:
            animation_index = 0;

            player.frame.width = TILE_SIZE; 
        break;

        case LEFT:
            animation_index = 2;

            player.frame.width = -TILE_SIZE; 
        break;

        case RIGHT:
            animation_index = 2;

            player.frame.width = TILE_SIZE; 
        break;
    
    }

    player.frame.x = TILE_SIZE * cur_frame;
    player.frame.y = (TILE_SIZE * 2) * animation_index;


};

void DrawPlayer()
{
    double rotation = 0.0f;

    if (player.dead)
    {
        player.frame.y = (TILE_SIZE *2) * 3;
        player.frame.x = 0;
    }

    DrawTexturePro(player.sprite,
                   player.frame,
                   player.view,
                   (Vector2){0, 0},
                   rotation,
                   WHITE);
};




void PlayerCollision()
{


    GridPos mat_ini = GetMatrixBegin(player.grid_pos, 13);
    GridPos mat_end = GetMatrixEnd(player.grid_pos, 13);

    for (int i = 0; i < explosion_qtd; i++)
    {

        if (CheckExplosionCollision(explosion_buffer[i], player.hitbox))
        {
            player.dead = true;
        }

    }


    for (int i = mat_ini.y; i < mat_end.y; i++) 
    {
        for (int j = mat_ini.x ; j < mat_end.x; j++) {

            if (CheckCollisionPointRec(player.position, tilemap[i][j].tile))
            {
                player.grid_pos = (GridPos){j, i};

            }


            if (CheckCollisionRecs(player.hitbox, tilemap[i][j].tile))
            {
                if (tilemap[i][j].type == PORTAL)
                {
                    if(!player.dead) player.win = true;
                    player.final_time = timer;

                }

                if (tilemap[i][j].type == WALL)
                {
                    ApplyCollision(tilemap[i][j].tile);
                    // Resolve collision by moving the player out of the tile
                   
                }

                for (int k = 0; k < 20; k++)
                {
                    for (int i = 0; i < bombs_qtd; i++)
                    {
                        if (CheckCollisionRecs(player.hitbox, bombs[i].hitbox))
                        {
                           ApplyCollision(bombs[i].hitbox);
                        }

                    }
                }


            }


        }

    }
};

void ApplyCollision(Rectangle rect)
{
    player.colliding = true;

    player.position = player.previous_pos;

    player.hitbox.y = player.position.y- (player.hitbox.height /2);

    player.hitbox.x = player.position.x- (player.hitbox.width /2);

    Rectangle overlap = GetCollisionRec(player.hitbox, rect);
    int direction = 0;
    Vector2 center = {rect.x + (rect.width/2.0f), rect.y + (rect.height/2.0f)};

    if (overlap.width > 0 && CheckCollisionRecs(player.hitbox, rect))
    {

        if (player.position.x >= center.x)
        {
            direction = 1;
        } else if (player.position.x < center.x)
        {
            direction = -1;
        }

        player.position.x += overlap.width * direction;
        player.hitbox.x = player.position.x- (player.hitbox.width /2);
        player.hitbox.y = player.position.y- (player.hitbox.height /2);

    }


    overlap = GetCollisionRec(player.hitbox, rect);
    direction = 0;
 
    if (overlap.height > 0 && CheckCollisionRecs(player.hitbox, rect))
    {

        if (player.position.y >= center.y)
        {
            direction = 1;
        } else if (player.position.y < center.y)
        {
            direction = -1;
        }

        player.position.y += overlap.height * direction;
        player.hitbox.x = player.position.x- (player.hitbox.height /2);
        player.hitbox.y = player.position.y- (player.hitbox.height /2);

    }   



}

void PutFlag()
{

    GridPos target = GetTargetTile();

    if (tilemap[target.y][target.x].type == FLOOR)
    {
        
        tilemap[target.y][target.x].flaged = !tilemap[target.y][target.x].flaged;
    }
    
};

GridPos GetTargetTile()
{
    Vector2 target = {0,0};

    switch (player.direction) {
        case UP:
            target.x = 0;
            target.y = -1;
        break;

        case DOWN:
          target.x = 0;
          target.y = +1;
          break;
        case LEFT:
          target.x = -1;
          target.y = 0;
          break;
        case RIGHT:
          target.x = +1;
          target.y = 0;
          break;
        }

    if (!ValidateGridPos((GridPos){player.grid_pos.x + target.x, player.grid_pos.y + target.y}))
    {
        return (GridPos){0,0};
        
    }

    
    return (GridPos){player.grid_pos.x + target.x, player.grid_pos.y + target.y};
}

void PlaceBomb()
{
    GridPos target = GetTargetTile();
    Tile tile = tilemap[target.y][target.x];

    if (tile.type == FLOOR && bombs_qtd < 1)
    {
        CreateBomb(target);
        tilemap[target.y][target.x].visible = true;

    }

}

void PlayerUpdate()
{

    player.previous_pos = player.position;
    PlayerMovement();
    PlayerCollision();
    RevealTiles(player.grid_pos);
    IsPlayerMoving();
    AnimationHandler();
    player.view.x = player.position.x - (player.view.width /2) ;
    player.view.y = player.position.y - (player.view.height /1.4);
    player.hitbox.x = player.position.x - (player.hitbox.width /2);
    player.hitbox.y = player.position.y - (player.hitbox.height /2);

    player.colliding = false;

};
