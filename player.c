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


void PlayerMovement() {

    extern double dt;

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

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)
        || IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_DOWN)
        || IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_LEFT)
        || IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT)
        || IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_UP)
    )
    {
        player.move = true;
    } else {
        player.move = false;
    }


}

void PlayerUpdate(){


    PlayerMovement();
    player.view.x = player.position.x - (player.view.width /2) ;
    player.view.y = player.position.y - (player.view.height /1.5);
    player.hitbox.x = player.position.x - (player.hitbox.width /2);
    player.hitbox.y = player.position.y - (player.hitbox.height /2);

}
