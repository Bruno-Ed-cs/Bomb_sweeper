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
Vector2 last_pos = { 0,0 };
extern double dt;
extern Tile tilemap[10][10];

void PlayerInit()
{

    player.position = (Vector2){0, 0};
    player.hitbox = (Rectangle){INIT_X, INIT_Y, TILE_SIZE -4, TILE_SIZE -4};
    player.frame = (Rectangle){0, 0, TILE_SIZE, TILE_SIZE * 2};
    player.view = (Rectangle){INIT_X, INIT_Y, TILE_SIZE, TILE_SIZE * 2};
    player.sprite = LoadTexture("./assets/sprites/Connor_fodder.png");
    player.speed = 150.0f;
    player.move = false;
    player.direction = DOWN;

};

void IsPlayerMoving()
{
    if (player.position.x == last_pos.x && player.position.y == last_pos.y)
    {
        player.move = false;
    } else 
    {
        player.move = true;
    }

    last_pos = player.position;

}


void PlayerMovement() {

    if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        player.position.y -= player.speed * dt;
        player.direction = UP;
    }
    else if (IsKeyDown(KEY_S)|| IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        player.position.y += player.speed * dt;
        player.direction = DOWN;
    }
    else if (IsKeyDown(KEY_D)|| IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        player.position.x  += player.speed * dt;
        player.direction = RIGHT;
    }
    else if (IsKeyDown(KEY_A)|| IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        player.position.x -= player.speed * dt;
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

                    switch (player.direction) {

                        case UP:
                            player.position.y += player.speed * dt; 
                            break;
                        case DOWN:
                            player.position.y -= player.speed * dt; 
                            break;

                        case LEFT:
                            player.position.x += player.speed * dt; 
                            break;

                        case RIGHT:
                            player.position.x -= player.speed * dt; 
                            break;
                    }


                }
            }


        }

    }
}

void PlayerUpdate(){


    PlayerMovement();
    IsPlayerMoving();
    PlayerCollision();
    player.view.x = player.position.x - (player.view.width /2) ;
    player.view.y = player.position.y - (player.view.height /1.5);
    player.hitbox.x = player.position.x - (player.hitbox.width /2);
    player.hitbox.y = player.position.y - (player.hitbox.height /2);

}
