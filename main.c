#include "globals.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    //SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screen.width, screen.height, "Bombsweeper 1.0 Alpha");

    SetWindowMinSize(screen.width, screen.height);

    InitAudioDevice();

    footstep_sfx = LoadSound("./assets/audio/sfx/Retro FootStep 03.wav");

    custom_font = LoadFontEx("./assets/fonts/Hardpixel.OTF",  128, NULL, 0);

    tileset = LoadTexture("./assets/sprites/tileset.png");
    bomb_sheet = LoadTexture("./assets/sprites/bomb.png");
    
    menu_theme = LoadMusicStream("./assets/audio/music/menu_theme.mp3");
    tutorial_theme = LoadMusicStream("./assets/audio/music/tutorial_theme.mp3");

    explosion_sheet = LoadTexture("./assets/sprites/explosion.png");

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

            //case MENU


            case GAME:

                if (!level_loaded) ResetGame();

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
