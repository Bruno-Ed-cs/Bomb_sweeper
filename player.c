#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#include "globals.h"
#include <stdbool.h>


Player player = { 0 };
extern double dt;
extern Tile tilemap[10][10];

void PlayerInit()
{

    player.position = (Vector2){50, 50};
    player.hitbox = (Rectangle){INIT_X, INIT_Y, TILE_SIZE -8, TILE_SIZE -8};
    player.frame = (Rectangle){0, 0, TILE_SIZE, TILE_SIZE * 2};
    player.view = (Rectangle){INIT_X, INIT_Y, TILE_SIZE, TILE_SIZE * 2};
    player.sprite = LoadTexture("./assets/sprites/Connor_fodder.png");
    player.speed = 50.0f;
    player.move = false;
    player.colliding = false;
    player.direction = DOWN;
    player.previous_pos = (Vector2){0, 0};

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

}


void PlayerMovement() {

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
    if (IsKeyDown(KEY_D) && !(player.colliding)) {
        player.position.x  += player.speed * dt;
        player.hitbox.x = player.position.x- (player.hitbox.width /2);
        player.direction = RIGHT;
    }
    else if(IsKeyDown(KEY_A) && !(player.colliding)) {
        player.position.x -= player.speed * dt;
        player.hitbox.x = player.position.x- (player.hitbox.width /2);
        player.direction = LEFT;
    }
    

}


void PlayerCollision()
{
    for (int i = 0; i < 10; i++) 
    {
        for (int j = 0; j < 10; j++) {

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
                                if (player.hitbox.x < tilemap[i][j].tile.x)
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
                                if (player.hitbox.y < tilemap[i][j].tile.y)
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
}

void PlayerUpdate(){



    PlayerCollision();

    player.previous_pos = player.position;
    PlayerMovement();
    PlayerCollision();
    IsPlayerMoving();
    player.view.x = player.position.x - (player.view.width /2) ;
    player.view.y = player.position.y - (player.view.height /1.4);
    player.hitbox.x = player.position.x - (player.hitbox.width /2);
    player.hitbox.y = player.position.y - (player.hitbox.height /2);

    player.colliding = false;

}
