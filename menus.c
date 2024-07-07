#include "globals.h"
#include "include/raylib.h"
#include <stdbool.h>

void StartMenu()
{

    //Tela de Menu

    Rectangle Jogar_menu = {screen.width - 255, 200, 185, 65};
    Rectangle Jogar_menu2 = {screen.width - 260, 195, 195, 75};

    Color c_Jogar_menu = WHITE;
    Color c_Jogar_menu2 = WHITE;

    Color c_jogar = BLACK;

    Rectangle sair_menu = {screen.width - 75, screen.height - 53, 60, 28};

    Rectangle sair_menu2 = {screen.width - 80, screen.height - 58, 70, 38};

    Color c_sair_menu;

    Color c_sair_menu2;
    



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
            PlaySound(button_click);

            state = SELECT_MENU;

        }

    }else{

        c_Jogar_menu2 = WHITE;

        c_jogar = BLACK;

    }

     if(CheckCollisionPointRec(mouse_pos, sair_menu)){

        c_sair_menu = BLACK;

        c_sair_menu2 = RED;

        DrawRectangleRec(sair_menu2, c_sair_menu2);

        DrawRectangleRec(sair_menu, c_sair_menu);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            PlaySound(button_click);
            running = false;

        }



    }else{

        c_sair_menu2 = BLACK;

    }

    BeginDrawing();

    ClearBackground(WHITE);

    //DrawText("Jogar", screen.width - 250, 200, 60, c_jogar);
    DrawTextPro(custom_font, "Play", (Vector2){screen.width - 250, 195}, (Vector2){0, 0}, 0.0f, 70, 1, c_jogar);

    //DrawText("Sair", screen.width - 68, screen.height - 50, 25, c_sair_menu2);
    DrawTextPro(custom_font, "Exit", (Vector2){screen.width - 68, screen.height - 50}, (Vector2){0, 0}, 0.0f, 25, 1, c_sair_menu2);

    EndDrawing();
}

void menu_levels()
{

    Rectangle frame = {0, 0, 32, 32};

    Rectangle Level_1 = {screen.width / 2 - 600, 88, 288, 288};

    Rectangle Level_2 = {screen.width / 2 - 144, 88, 288, 288};

    Rectangle Level_3 = {screen.width / 2 + 300, 88, 288, 288};

    Rectangle Tutorial = {screen.width / 2 - 112, screen.height - 300, 224, 224};

    Rectangle sair_levels = {screen.width - 75, screen.height - 53, 60, 28};

    Rectangle sair_levels2 = {screen.width - 80, screen.height - 58, 70, 38};

    Color c_sair_level;

    Color c_sair_level2 = BLACK;

    Color c_level_1 = BLACK;

    Color c_level_2 = BLACK;

    Color c_level_3 = BLACK;

    Color c_tutorial = BLACK;


        //Botao de sair - Levels
    if(CheckCollisionPointRec(mouse_pos, sair_levels)){

        c_sair_level = BLACK;

        c_sair_level2 = RED;

        DrawRectangleRec(sair_levels2, c_sair_level2);

        DrawRectangleRec(sair_levels, c_sair_level);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            PlaySound(button_click);
            state = START_MENU;

        }

    }

    //Botao da fase 1
    if(CheckCollisionPointRec(mouse_pos, Level_1)){

            c_level_1 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            PlaySound(button_click);
            InitGame("./assets/levels/beach_day.json");
            state = GAME;

        }

    }

    //Botao da fase 2
    if(CheckCollisionPointRec(mouse_pos, Level_2)){

            c_level_2 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Level 2...
            PlaySound(button_click);
            InitGame("./assets/levels/dejavu.json");
            state = GAME;

        }

    }

    //Botao da fase 3
    if(CheckCollisionPointRec(mouse_pos, Level_3)){

            c_level_3 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Level 3...
            PlaySound(button_click);
            InitGame("./assets/levels/crystal_cove.json");
            state = GAME;

        }

    }

    //Botao do tutorial
    if(CheckCollisionPointRec(mouse_pos, Tutorial)){

            c_tutorial = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Tutorial...
            PlaySound(button_click);
            InitGame("./assets/levels/mapa1.json");
            state = GAME;

        }

    }


    BeginDrawing();


    ClearBackground(WHITE);

    DrawRectangleRec(Level_1, BLACK);
    DrawTexturePro(thumb_beach, frame, Level_1, (Vector2){0,0}, 0.0f, WHITE);

    DrawRectangleRec(Level_2, BLACK);

    DrawRectangleRec(Level_3, BLACK);

    DrawRectangleRec(Tutorial, BLACK);


    DrawTextEx(custom_font,"LEVEL 1", (Vector2){screen.width / 2 - 530, 45}, 46, 1, c_level_1);

    DrawTextEx(custom_font, "LEVEL 2", (Vector2){screen.width / 2 - 70, 45}, 46, 1, c_level_2);

    DrawTextEx(custom_font, "LEVEL 3", (Vector2){screen.width / 2 + 370, 45}, 46, 1, c_level_3);


    DrawTextEx(custom_font, "Beach Day",(Vector2){ screen.width / 2 - 570, 375}, 46, 1,c_level_1);

    DrawTextEx(custom_font, "Dejavu", (Vector2){screen.width / 2 - 65, 375}, 46, 1, c_level_2);

    DrawTextEx(custom_font, "Crystal Cove", (Vector2){screen.width / 2 + 315, 375}, 46, 1, c_level_3);

    

    DrawTextEx(custom_font, "Tutorial", (Vector2){screen.width / 2 - 60, screen.height - 75}, 36,1, c_tutorial);

    DrawTextEx(custom_font, "Exit", (Vector2){screen.width - 68, screen.height - 50}, 25, 1, c_sair_level2);

    EndDrawing();


}



