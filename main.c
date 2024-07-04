#include "globals.h"
#include <stdio.h>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screen.width, screen.height, "Bombsweeper beta 1.1");

    SetWindowMinSize(screen.width, screen.height);

    Image icon = LoadImage("./assets/sprites/icon.png");
    SetWindowIcon(icon);

    InitAudioDevice();

    LoadAssets();

    SetTargetFPS(-1);

    while (!WindowShouldClose()) {


        //todo : colocar os menus em uma funcao e dixar as variaveis deles locais

        //Trouxe a configuraçao de fullScreen aqui para funcionar no menu
         if (IsWindowFullscreen())
        {

            screen.height = GetMonitorHeight(GetCurrentMonitor());
            screen.width = GetMonitorWidth(GetCurrentMonitor());

        } else 
        {
             screen.height = GetScreenHeight();
            screen.width = GetScreenWidth();

        }
        //controle de tela cheia
        if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT))
        {

            ToggleFullscreen();


            SetWindowSize(screen.width, screen.height); //quando a tela cheia é ativada ou desativada atualizamos o tamanho da janela para que todos os valores dependent delas continuem corretos

        }

        mouse_pos = GetMousePosition();
        UpdateVolume();

        switch(state){



            case START_MENU:

                StartMenu();

            break;

            //case MENU


            case GAME:

                if (!level_loaded) 
                {
                    printf("Error - level not loaded\n");

                }

                Game();

            break;



        }
    
    }

    free(minefild);
    if (level_loaded) UnloadLevel();
    free(tilemap);
    UnloadAssets();

    CloseWindow();
    return 0;
}
