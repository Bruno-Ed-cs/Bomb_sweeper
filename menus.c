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

        c_jogar = WHITE;

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
    DrawTextPro(custom_font, "Play", (Vector2){screen.width - 230, 195}, (Vector2){0, 0}, 0.0f, 70, 1, c_jogar);

    //DrawText("Sair", screen.width - 68, screen.height - 50, 25, c_sair_menu2);
    DrawTextPro(custom_font, "Exit", (Vector2){screen.width - 68, screen.height - 53}, (Vector2){0, 0}, 0.0f, 25, 1, c_sair_menu2);

    EndDrawing();
}

void menu_levels()
{

    Rectangle frame = {0, 0, 32, 32};

    Rectangle Level_1 = {screen.width / 2 - 600, screen.height/2 -144, 288, 288};

    Rectangle Level_2 = {screen.width / 2 - 144, screen.height/2 -144, 288, 288};

    Rectangle Level_3 = {screen.width / 2 + 300, screen.height/2 - 144, 288, 288};


    Rectangle sair_levels = {screen.width - 75, screen.height - 53, 60, 28};

    Rectangle sair_levels2 = {screen.width - 80, screen.height - 58, 70, 38};

    Color c_sair_level;

    Color c_sair_level2 = BLACK;

    Color c_level_1 = BLACK;

    Color c_level_2 = BLACK;

    Color c_level_3 = BLACK;

     DrawTexturePro(
            LevelTela,
            (Rectangle){ 0, 0, LevelTela.width, LevelTela.height },
            (Rectangle){ 0, 0, screen.width, screen.height },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );

    if (!FileExists("./save.json"))
    {
        CreateSavefile();
    }

    int scores[3] = {GetLevelScore("beach_day"), GetLevelScore("dejavu"), GetLevelScore("crystal_cove")};
    char score_strigs[3][100];

    for (int i = 0; i < 3; i++)
    {
        sprintf(score_strigs[i], "%d $", scores[i]);
    }

        //Botao de sair - Levels
    if(CheckCollisionPointRec(mouse_pos, sair_levels)){
        //Modifica as cores do botao de sair
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

    BeginDrawing();


    ClearBackground(WHITE);

    DrawRectangleRec(Level_1, BLACK);
    DrawTexturePro(thumb_beach, frame, Level_1, (Vector2){0,0}, 0.0f, WHITE);

    DrawRectangleRec(Level_2, BLACK);

    DrawRectangleRec(Level_3, BLACK);


    Vector2 len_beach = MeasureTextEx(custom_font, score_strigs[0], 46, 1);
    DrawTextEx(custom_font, score_strigs[0], 
               (Vector2){Level_1.x - (len_beach.x/2 - Level_1.width/2),
               Level_1.y - len_beach.y},
               46, 1, c_level_1);

    Vector2 len_dejavu = MeasureTextEx(custom_font, score_strigs[1], 46, 1);
    DrawTextEx(custom_font, score_strigs[1], 
               (Vector2){Level_2.x - (len_dejavu.x/2 - Level_2.width/2),
               Level_2.y - len_dejavu.y},
               46, 1, c_level_2);

    Vector2 len_cove = MeasureTextEx(custom_font, score_strigs[2], 46, 1);
    DrawTextEx(custom_font, score_strigs[2], 
               (Vector2){Level_3.x - (len_cove.x/2 - Level_2.width/2),
               Level_3.y - len_cove.y},
               46, 1, c_level_3);


    //Desenha os textos das telas de level
    DrawTextEx(custom_font, "Beach Day",(Vector2){ Level_1.x + (Level_1.width/2 - MeasureTextEx(custom_font, "Beach Day", 46 , 1).x/2) ,
        Level_1.y + Level_1.height},
               46, 1, c_level_1);

    DrawTextEx(custom_font, "Dejavu",(Vector2){ Level_2.x + (Level_2.width/2 - MeasureTextEx(custom_font, "Dejavu", 46 , 1).x/2) ,
        Level_2.y + Level_2.height},
               46, 1, c_level_2);


    DrawTextEx(custom_font, "Crystal Cove",(Vector2){ Level_3.x + (Level_3.width/2 - MeasureTextEx(custom_font, "Crystal Cove", 46 , 1).x/2) ,
        Level_3.y + Level_3.height},
               46, 1, c_level_3);

    DrawTextEx(custom_font, "Exit", (Vector2){screen.width - 68, screen.height - 53}, 25, 1, c_sair_level2);

    EndDrawing();


}



