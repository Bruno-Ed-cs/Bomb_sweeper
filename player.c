#include "globals.h"
#include "include/Linux/wayland/raylib.h"

void PlayerInit()
{

    player.hitbox = (Rectangle){INIT_X, INIT_Y, TILE_SIZE -8, TILE_SIZE -8};
    player.frame = (Rectangle){0, 0, TILE_SIZE, TILE_SIZE * 2};
    player.view = (Rectangle){INIT_X, INIT_Y, TILE_SIZE, TILE_SIZE * 2};
    player.sprite = LoadTexture("./assets/sprites/Connor_fodder-sheet.png");
    player.speed = 50.0f;
    player.move = false;
    player.colliding = false;
    player.direction = DOWN;
    player.previous_pos = (Vector2){0, 0};
    player.spawn = spawn_tile;
    player.grid_pos = player.spawn;
    player.position = (Vector2){tilemap[player.spawn.y][player.spawn.x].tile.x + (TILE_SIZE /2.0f), tilemap[player.spawn.y][player.spawn.x].tile.y + (TILE_SIZE /2.0f) };

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

    if (IsKeyPressed(KEY_SPACE))
    {
        PutFlag();
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
    DrawTexturePro(player.sprite,
                   player.frame,
                   player.view,
                   (Vector2){0, 0},
                   0.0f,
                   WHITE);
};




void PlayerCollision()
{


    GridPos mat_ini = GetMatrixBegin(player.grid_pos, 13);
    GridPos mat_end = GetMatrixEnd(player.grid_pos, 13);

    for (int i = mat_ini.y; i < mat_end.y; i++) 
    {
        for (int j = mat_ini.x ; j < mat_end.x; j++) {

            if (CheckCollisionPointRec(player.position, tilemap[i][j].tile))
            {
                player.grid_pos = (GridPos){j, i};

            }


            if (CheckCollisionRecs(player.hitbox, tilemap[i][j].tile))
            {

                if (tilemap[i][j].type == WALL)
                {
                    player.colliding = true;

                    player.position = player.previous_pos;

                    player.hitbox.y = player.position.y- (player.hitbox.height /2);

                    player.hitbox.x = player.position.x- (player.hitbox.width /2);


                    // Resolve collision by moving the player out of the tile
                    for (int k = 0; k < 20; k++)
                    {
                        Rectangle overlap = GetCollisionRec(player.hitbox, tilemap[i][j].tile);
                        double step = 0.0000001f;


                        if (CheckCollisionRecs(player.hitbox, tilemap[i][j].tile))
                        {
                            if (overlap.width < overlap.height)
                            {
                                // Horizontal collision
                                if (player.hitbox.x <= tilemap[i][j].tile.x)
                                {
                                    player.position.x -= (overlap.width + step) *dt;
                                    player.hitbox.x = player.position.x- (player.hitbox.width /2);
                                }
                                else
                            {
                                    player.position.x += (overlap.width + step ) *dt;
                                    player.hitbox.x = player.position.x- (player.hitbox.width /2);
                                }
                            }
                            else
                        {
                                // Vertical collision
                                if (player.hitbox.y <= tilemap[i][j].tile.y)
                                {
                                    player.position.y -= (overlap.width + step) *dt;
                                    player.hitbox.y = player.position.y- (player.hitbox.height /2);
                                }
                                else
                            {
                                    player.position.y += (overlap.width + step) *dt;
                                    player.hitbox.y = player.position.y- (player.hitbox.height/2);
                                }

                            }
                        }
                    }
                }
            }


        }

    }
};

void PutFlag()
{
    switch (player.direction) {

        case UP:

            if (GetTileType((GridPos){player.grid_pos.x, player.grid_pos.y -1} ,FLOOR) == FLOOR) 
            {
                tilemap[player.grid_pos.y -1][player.grid_pos.x].flaged = !tilemap[player.grid_pos.y -1][player.grid_pos.x].flaged;

            }

        break;
          
        case DOWN:
 
            if (GetTileType((GridPos){player.grid_pos.x, player.grid_pos.y +1} ,FLOOR) == FLOOR) 
            {
                tilemap[player.grid_pos.y +1][player.grid_pos.x].flaged = !tilemap[player.grid_pos.y +1][player.grid_pos.x].flaged;

            }

 
        break;
 
        case LEFT:

            if (GetTileType((GridPos){player.grid_pos.x -1, player.grid_pos.y} ,FLOOR) == FLOOR) 
            {
                tilemap[player.grid_pos.y ][player.grid_pos.x -1].flaged = !tilemap[player.grid_pos.y ][player.grid_pos.x -1].flaged;

            }


        break;
            
        case RIGHT:

            if (GetTileType((GridPos){player.grid_pos.x +1, player.grid_pos.y} ,FLOOR) == FLOOR) 
            {
                tilemap[player.grid_pos.y][player.grid_pos.x +1].flaged = !tilemap[player.grid_pos.y ][player.grid_pos.x +1].flaged;

            }


        break;
               
    }

};

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
