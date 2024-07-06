#include "globals.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    #ifdef RELEASE
    
        SetConfigFlags(FLAG_VSYNC_HINT);
    #endif /* ifdef RELEASE */

    InitWindow(screen.width, screen.height, "Bombsweeper beta 1.1");

    SetWindowMinSize(screen.width, screen.height);

    Image icon = LoadImage("./assets/sprites/icon.png"); //carregamos o icone da janaela e depois carregamos ele
    SetWindowIcon(icon);

    InitAudioDevice();

    LoadAssets();// funcao que carrega todas a imagens e sons usados no jogo para a memoria

    while (running) {

        if (WindowShouldClose()) running = false; // if para detectar se a janela foi fechada ou se o esc foi apertado

        //todo : colocar os menus em uma funcao e dixar as variaveis deles locais

        //atualizacao da variavel do tamanho da tela para corresponder no codigo, detecta o tamanho do monitor em tela cheia
        if (IsWindowFullscreen())
        {

            screen.height = GetMonitorHeight(GetCurrentMonitor());
            screen.width = GetMonitorWidth(GetCurrentMonitor());

        } else 
        {
            screen.height = GetScreenHeight();
            screen.width = GetScreenWidth();

        }

        //controle de tela cheia para alt + enter
        if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT))
        {

            ToggleFullscreen();


            SetWindowSize(screen.width, screen.height); //quando a tela cheia é ativada ou desativada atualizamos o tamanho da janela para que todos os valores dependent delas continuem corretos

        }

        mouse_pos = GetMousePosition(); //variavel da posicao do mouse
        UpdateVolume(); // funcao para atualizar o volume de todos os sons do jogo

        // controle do estado do jogo
        switch(state){

            case START_MENU:

                StartMenu(); // Menu inicial do jogo

                break;

            case SELECT_MENU:

                menu_levels(); // menu de seleção de fases

                break;

            case GAME:

                if (!level_loaded) 
                {
                    printf("Error - level not loaded\n");

                }

                Game(); // funcao principal do jogo

                break;



        }

    }

    // delocaçao de memoria quando a janela é fechada
    free(minefild);
    if (level_loaded) UnloadLevel();
    free(tilemap);
    UnloadAssets();

    CloseWindow();
    return 0;
}
