#include "globals.h"
#include "include/raylib.h"

void StartMenu()
{

    //Tela de Menu

    Rectangle Jogar_menu = {screen.width - 255, 200, 185, 65};
    Rectangle Jogar_menu2 = {screen.width - 260, 195, 195, 75};

    Color c_Jogar_menu = WHITE;
    Color c_Jogar_menu2 = WHITE;

    Color c_jogar = BLACK;
    

    Texture2D MenuTela = LoadTexture("./assets/sprites/menumap.png");


    DrawTexturePro(
            MenuTela,
            (Rectangle){ 0, 0, MenuTela.width, MenuTela.height },
            (Rectangle){ 0, 0, screen.width, screen.height },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );

    
    if (!IsMusicStreamPlaying(menu_theme)) PlayMusicStream(menu_theme);
    UpdateMusicStream(menu_theme);

    if( CheckCollisionPointRec( mouse_pos, Jogar_menu ) ){

        c_Jogar_menu2 = GREEN;

        c_jogar = GREEN;

        
       DrawRectangleRec(Jogar_menu2, c_Jogar_menu2);

       DrawRectangleRec(Jogar_menu, c_Jogar_menu);




        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if (IsMusicStreamPlaying(menu_theme)) StopMusicStream(menu_theme);

            ResetGame();

            state = GAME;

        }

    }else{

        c_Jogar_menu2 = WHITE;

        c_jogar = BLACK;

    }

    BeginDrawing();

    ClearBackground(WHITE);

    DrawText("Jogar", screen.width - 250, 200, 60, c_jogar);

    EndDrawing();
}

