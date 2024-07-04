#include "globals.h"

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

            InitGame("./assets/levels/dejavu.json");

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

            CloseWindow();

        }



    }else{

        c_sair_menu2 = BLACK;

    }

    BeginDrawing();

    ClearBackground(WHITE);

    DrawText("Jogar", screen.width - 250, 200, 60, c_jogar);

    DrawText("Sair", screen.width - 68, screen.height - 50, 25, c_sair_menu2);

    EndDrawing();
}

void menu_levels()
{


    Rectangle Level_1 = {screen.width / 2 - 600, 80, 280, 280};

    Rectangle Level_2 = {screen.width / 2 - 135, 80, 280, 280};

    Rectangle Level_3 = {screen.width / 2 + 300, 80, 280, 280};

    Rectangle Tutorial = {screen.width / 2 - 115, screen.height - 300, 220, 220};

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

            state = START_MENU;

        }

    }

    //Botao da fase 1
    if(CheckCollisionPointRec(mouse_pos, Level_1)){

            c_level_1 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state = GAME;

        }

    }

    //Botao da fase 2
    if(CheckCollisionPointRec(mouse_pos, Level_2)){

            c_level_2 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Level 2...

        }

    }

    //Botao da fase 3
    if(CheckCollisionPointRec(mouse_pos, Level_3)){

            c_level_3 = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Level 3...

        }

    }

    //Botao do tutorial
    if(CheckCollisionPointRec(mouse_pos, Tutorial)){

            c_tutorial = GREEN;


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            //Tutorial...

        }

    }


    BeginDrawing();


    ClearBackground(WHITE);

    DrawRectangleRec(Level_1, BLACK);

    DrawRectangleRec(Level_2, BLACK);

    DrawRectangleRec(Level_3, BLACK);

    DrawRectangleRec(Tutorial, BLACK);


    DrawText("LEVEL 1", screen.width / 2 - 530, 50, 30, c_level_1);

    DrawText("LEVEL 2", screen.width / 2 - 50, 50, 30, c_level_2);

    DrawText("LEVEL 3", screen.width / 2 + 370, 50, 30, c_level_3);


    DrawText("Dejavu", screen.width / 2 - 540, 365, 40, c_level_1);

    DrawText("Beach Day", screen.width / 2 - 100, 365, 40, c_level_2);

    DrawText("Crystal Cove", screen.width / 2 + 310, 365, 40, c_level_3);

    

    DrawText("Tutorial", screen.width / 2 - 70, screen.height - 80, 30, c_tutorial);

    DrawText("Sair", screen.width - 68, screen.height - 50, 25, c_sair_level2);

    

    DrawRectangle(screen.width / 2 ,  0 , 1 , 1000 , RED );


    EndDrawing();


}



