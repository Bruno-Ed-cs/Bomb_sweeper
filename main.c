#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#include <string.h>


int main()
{
    Rectangle screen = {0, 0, 1280, 720};

    InitWindow(screen.width, screen.height, "Bombsweeper 0.0 Pre-alpha");

    while (!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(WHITE);

            DrawText("Isso definitivamente funciona",
                     (screen.width /2) - ((strlen("Isso definitivamente funciona") / 2.0f) * 10),
                     (screen.height /2) - 10,
                     20,
                     GREEN);

            DrawFPS(0, 0);

        EndDrawing();
    
    }

    CloseWindow();
    return 0;
}
