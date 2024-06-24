#include "globals.h"

void StartMenu()
{

    //Tela de Menu
    Rectangle exit_menu = {screen.width / 2 - 55, screen.height/ 2 - 10, 127, 60};
    Rectangle exit_menu2 = {(screen.width / 2 - 55) - 5, (screen.height  / 2 - 10) - 5, 137, 75};
    Color c_exit_menu = WHITE;
    Color c_exit_menu2 = WHITE;

    Color c_jogar = BLACK;

    if( CheckCollisionPointRec( mouse_pos, exit_menu ) ){

        c_exit_menu2 = GREEN;

        c_jogar = GREEN;



        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

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

void PauseMenu()
{
    Color c_exit_pause = LIGHTGRAY;
    Color c_continue_pause = LIGHTGRAY;
    Color c_continue_pause2 = WHITE;
    Color c_sair = BLACK;

    //Tela de Pausa
    Rectangle exit_pause = {(screen.width /2 - 70) + 20, screen.height / 2 - 15, 118, 50};
    Rectangle exit_pause2 = {((screen.width/2 - 70) + 20) - 5, (screen.height / 2 - 15) - 5, 118 + 10, 50 + 10};
    Rectangle continue_pause = {screen.width /2 - 100, 245, 215, 50};
    Rectangle continue_pause2 = {(screen.width /2 - 100) - 5, 240, 225, 60};

    ClearBackground(GRAY);


    if( CheckCollisionPointRec( mouse_pos, exit_pause ) ){

        c_exit_pause = BLACK;

        c_sair = RED;


        DrawRectangleRec(exit_pause2, RED);

        DrawRectangleRec(exit_pause, c_exit_pause);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state = START_MENU;

        }


    }else{

        c_sair = WHITE;

    }


    if( CheckCollisionPointRec( mouse_pos, continue_pause ) ){

        c_continue_pause = WHITE;

        c_continue_pause2 = GREEN;

        DrawRectangleRec(continue_pause2, c_continue_pause2);

        DrawRectangleRec(continue_pause, c_continue_pause);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            pause = !pause;

        }

    }else{

        c_continue_pause2 = WHITE;


    }


    DrawText("Pause", screen.width /2 - 64, 100, 50, BLACK );

    DrawText("Continuar", screen.width /2 - 90, 250, 40, c_continue_pause2);

    DrawText("Sair", exit_pause.x + 10, exit_pause.y + 5, 40, c_sair);

}
