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

    footstep_sfx = LoadSound("./assets/audio/sfx/Retro FootStep 03.wav");
    custom_font = LoadFontEx("./assets/fonts/Hardpixel.OTF",  128, NULL, 0);
    tileset = LoadTexture("./assets/sprites/tileset.png");
    bomb_sheet = LoadTexture("./assets/sprites/bomb.png");
    menu_theme = LoadMusicStream("./assets/audio/music/menu_theme.mp3");
    level_music = LoadMusicStream("./assets/audio/music/tutorial_theme.mp3");
    explosion_sheet = LoadTexture("./assets/sprites/explosion.png");
    background = LoadTexture("./assets/sprites/background_dejavu.png");
    clock_sprite = LoadTexture("./assets/sprites/clock.png");
    wallet_sprite = LoadTexture("./assets/sprites/wallet.png");
    MenuTela = LoadTexture("./assets/sprites/menumap.png");

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

        switch(state){



            case START_MENU:

                StartMenu();

            break;

            case SELECT_MENU:

              menu_levels();

            break;

          


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
    UnloadSound(footstep_sfx);

    CloseWindow();
    return 0;
}
