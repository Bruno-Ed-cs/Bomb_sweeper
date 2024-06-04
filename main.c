#include <stdio.h>
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
#include <string.h>

Rectangle screen = {0, 0, INIT_WIDTH, INIT_HEIGHT};
double dt = 0;
Camera2D camera = { 0 };
bool debug = true;

int main()
{
   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen.width, screen.height, "Bombsweeper 0.0 Pre-alpha");

    SetWindowMinSize(INIT_WIDTH, INIT_HEIGHT);
 
    extern Player player;

    PlayerInit();

    camera.target = (Vector2){player.position.x, player.position.y};
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screen.width /2, screen.height /2};
    camera.rotation = 0.0f;


    while (!WindowShouldClose()) {

        dt = GetFrameTime();

        if (IsWindowFullscreen())
        {
            screen.height = GetMonitorHeight(GetCurrentMonitor());
            screen.width = GetMonitorWidth(GetCurrentMonitor());
        } else 
        {
            screen.height = GetScreenHeight();
            screen.width = GetScreenWidth();
        }

        PlayerUpdate();
        camera.target = (Vector2){player.position.x, player.position.y};
        camera.offset = (Vector2){screen.width /2, screen.height /2};
        camera.zoom = (screen.width / INIT_WIDTH) + 3;

        if (IsKeyReleased(KEY_F3))
        {
            debug = !debug;    
        }

        if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT))
        {
            ToggleFullscreen();
        }

        BeginDrawing();

        ClearBackground(WHITE);
        BeginMode2D(camera);

        DrawText("Isso definitivamente funciona",
                 100 - ((strlen("Isso definitivamente funciona") / 2.0f) * 10),
                 50 - 10,
                 20,
                 GREEN);

        DrawTexturePro(player.sprite,
                       player.frame,
                       player.view,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        if (debug)
        {
            DrawRectangleLinesEx(player.hitbox, 1.0f, RED);
            DrawCircleV(player.position, 2.0f, RED);
        }

        EndMode2D();


        if (debug)
        {
            char debug_pos[200];
            sprintf(debug_pos, "X = %.2lf\nY = %.2lf\n", player.position.x, player.position.y);

            DrawText(debug_pos, screen.width -200, screen.height -40, 20, GREEN);

            DrawFPS(0, 0);

        }
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
