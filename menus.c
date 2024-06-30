#include "globals.h"
#include "include/raylib.h"

void StartMenu()
{

    //Tela de Menu
    Rectangle exit_menu = {screen.width / 2 - 55, screen.height/ 2 - 10, 127, 60};
    Rectangle exit_menu2 = {(screen.width / 2 - 55) - 5, (screen.height  / 2 - 10) - 5, 137, 75};
    Color c_exit_menu = WHITE;
    Color c_exit_menu2 = WHITE;

    Color c_jogar = BLACK;

    
    if (!IsMusicStreamPlaying(menu_theme)) PlayMusicStream(menu_theme);
    UpdateMusicStream(menu_theme);

    if( CheckCollisionPointRec( mouse_pos, exit_menu ) ){

        c_exit_menu2 = GREEN;

        c_jogar = GREEN;



        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if (IsMusicStreamPlaying(menu_theme)) StopMusicStream(menu_theme);

            ResetGame();

            state = GAME;

        }

    }else{

        c_exit_menu2 = WHITE;

        c_jogar = BLACK;

    }

    BeginDrawing();

    ClearBackground(WHITE);

    DrawText("BETA",screen.width - 100 , screen.height - 50, 20, BLACK);

    DrawText("MENU", screen.width / 2 - 70, 20, 50, BLACK);

    DrawRectangleRec(exit_menu2, c_exit_menu2);

    DrawRectangleRec(exit_menu, c_exit_menu);

    DrawText("Jogar", screen.width / 2 - 50, screen.height  / 2, 40, c_jogar);

    EndDrawing();
}

