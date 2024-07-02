#include "globals.h"
#include "include/raylib.h"

void VictoryScreen()
{
    GetFinalScore();

    Color background_color = {51, 255, 51, 120};
    Color button_color = {129, 129, 129 ,200};

    char exit_message[50] = "Exit";
    char respawn_message[50] = "Respawn";
    char score_message[100];
    char mine_message[100];
    char tile_message[100];
    char time_message[100];
    
    sprintf(tile_message, "Revealed Tiles : %d", GetRevealedTiles());
    sprintf(time_message, "Time Bonus : %02d:%02d +%d $", (int)(player.final_time) / 60, (int)(player.final_time) % 60, GetTimeBonus());
    sprintf(mine_message, "Mines : %d/%d +%d $", GetFlagedMines(), mine_index, GetFlagedMines() * 150);
    sprintf(score_message, "Salary : %d $", final_score);

    Vector2 win_pos = {screen.width/2 - (MeasureText("You Win!", 128) + MeasureText("", 128))/2.0f , screen.height/5.0f};

    Rectangle respawn_button = {(screen.width/2) -150, screen.height /2 + 100, 300, 60};
    Rectangle exit_button = {respawn_button.x, respawn_button.y + respawn_button.height +10, 300, 60};

    Vector2 exit_text_pos = {exit_button.x + 10, exit_button.y - 5};
    Vector2 respawn_text_pos = {respawn_button.x + 10, respawn_button.y - 5};

    DrawRectangleRec(screen, background_color);

    DrawRectangleRec(respawn_button, button_color);
    DrawRectangleRec(exit_button, button_color);

    DrawTextEx(custom_font, "You Win!", win_pos, 128, 0, WHITE);

    DrawTextEx(custom_font, tile_message, (Vector2){win_pos.x, win_pos.y + 150 + 32}, 32, 0, WHITE);
    DrawTextEx(custom_font, time_message, (Vector2){win_pos.x, win_pos.y + 150}, 32, 0, WHITE);
    DrawTextEx(custom_font, mine_message, (Vector2){win_pos.x, win_pos.y + 150 + (32 *2)}, 32, 0, WHITE);
    DrawTextEx(custom_font, score_message, (Vector2){win_pos.x, win_pos.y + 150 + (32 *3)}, 32, 0, WHITE);

    DrawTextEx(custom_font, exit_message, exit_text_pos, 64, 0, WHITE);
    DrawTextEx(custom_font, respawn_message, respawn_text_pos, 64, 0, WHITE);

    if( CheckCollisionPointRec( mouse_pos, respawn_button) ){



        DrawRectangleLinesEx(respawn_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            ResetLevel();
        }


    }

    if( CheckCollisionPointRec( mouse_pos, exit_button) ){



        DrawRectangleLinesEx(exit_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            UnloadLevel();
            state = START_MENU;


        }


    }



}

void DeathScreen()
{
    Color background_color = {229, 57, 53, 120};
    Color button_color = {129, 129, 129 ,200};

    char death_message[50] = "You Died";
    char exit_message[50] = "Exit";
    char respawn_message[50] = "Respawn";

    Vector2 death_message_pos = {screen.width/2 - (MeasureText(death_message, 128) + MeasureText("", 128))/2.0f , screen.height/4.0f};

    Rectangle respawn_button = {(screen.width/2) -150, screen.height /2 + 100, 300, 60};
    Rectangle exit_button = {respawn_button.x, respawn_button.y + respawn_button.height +10, 300, 60};


    Vector2 exit_text_pos = {exit_button.x + 10, exit_button.y - 5};
    Vector2 respawn_text_pos = {respawn_button.x + 10, respawn_button.y - 5};

    DrawRectangleRec(screen, background_color);

    DrawRectangleRec(respawn_button, button_color);
    DrawRectangleRec(exit_button, button_color);

    DrawTextEx(custom_font, "You Died", death_message_pos, 128, 0, WHITE);

    DrawTextEx(custom_font, exit_message, exit_text_pos, 64, 0, WHITE);
    DrawTextEx(custom_font, respawn_message, respawn_text_pos, 64, 0, WHITE);

    if( CheckCollisionPointRec( mouse_pos, respawn_button) ){



        DrawRectangleLinesEx(respawn_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            ResetLevel();
        }


    }
    
    if (IsKeyPressed(KEY_R))
    {
        pause = false;
        ResetLevel();
    }

    if( CheckCollisionPointRec( mouse_pos, exit_button) ){



        DrawRectangleLinesEx(exit_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            UnloadLevel();
            state = START_MENU;


        }


    }

}

void PauseMenu()
{
    Color c_exit_pause = BLACK;
    Color c_continue_pause = BLACK;
    Color c_continue_pause2 = BLACK;
    Color c_sair = BLACK;
    Color background_color = {130, 130, 130, 100};

    //Tela de Pausa
    
    Rectangle continue_pause = {screen.width /2 - 100, 245, 215, 50};
    Rectangle continue_pause2 = {(screen.width /2 - 100) - 5, 240, 225, 60};

    Rectangle exit_pause = {(screen.width /2 - 70) + 20, continue_pause.y + continue_pause.height *2, 118, 50};
    DrawRectangleRec(screen, background_color);

    if( CheckCollisionPointRec( mouse_pos, exit_pause ) ){

        c_exit_pause = BLACK;

        c_sair = RED;


        DrawRectangleRec(exit_pause, c_exit_pause);
        DrawRectangleLinesEx(exit_pause, 5.0f, RED);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            UnloadLevel();
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

void DrawUi()
{

    Vector2 clock_pos, score_pos, clock_ui_pos, score_ui_pos;
    char score[100];
    sprintf(score, "%d $", player.score);


    char clock[100];
    sprintf(clock,"%02.0lf:%02.0lf", minutes, seconds);

    clock_pos = (Vector2){camera_bounds.x + ((camera_bounds.width/2.0f) - (MeasureTextEx(custom_font, clock, 12, 1).x/2.0f) ),camera_bounds.y +1};
    score_pos = (Vector2){camera_bounds.x + ((camera_bounds.width) - MeasureTextEx(custom_font, score, 12, 1).x -1), camera_bounds.y + 5} ;
    clock_ui_pos =(Vector2){camera_bounds.x + (camera_bounds.width/2.0f) - (23),camera_bounds.y} ;
    score_ui_pos =(Vector2){camera_bounds.x + ((camera_bounds.width) - 60), camera_bounds.y} ;


    //DrawRectanglePro((Rectangle){clock_ui_pos.x, clock_ui_pos.y, 46, 16}, (Vector2){0,0}, 0, BLACK);
    //DrawRectanglePro((Rectangle){score_ui_pos.x, score_ui_pos.y, 60, 30}, (Vector2){0,0}, 0, BLACK);
    DrawTexturePro(clock_sprite, (Rectangle){0,0, clock_sprite.width, clock_sprite.height}, 
                   (Rectangle){clock_ui_pos.x, clock_ui_pos.y, clock_sprite.width, clock_sprite.height}, (Vector2){0,0}, 0, WHITE);

    DrawTexturePro(wallet_sprite, (Rectangle){0,0, wallet_sprite.width, wallet_sprite.height}, 
                   (Rectangle){score_ui_pos.x, score_ui_pos.y, wallet_sprite.width, wallet_sprite.height}, 
                   (Vector2){0,0}, 0, WHITE);
    //DrawText(clock, (screen.width/2) - (str_size / 2.0f) *15, 10, 30, BLACK);
    DrawTextEx(custom_font, score, score_pos, 12, 1, WHITE);
    DrawTextEx(custom_font, clock, clock_pos,12, 1, WHITE);


}

void Game()
{
    if (!IsMusicStreamPlaying(level_music)) PlayMusicStream(level_music);
    UpdateMusicStream(level_music);

    if (pause)
    {

        dt = 0; 

    } else 
    {

        dt = GetFrameTime();
    }

    timer += dt;

    seconds += dt;
    if (seconds >= 59) {

        seconds = 0;
        minutes++;
    
    }

    GridPos mat_begin = GetMatrixBegin(player.grid_pos, 20);
    GridPos mat_end = GetMatrixEnd(player.grid_pos, 20);

    InputHandler(GetKeyPressed()); //pega os inputs para o controle do sistema

    if (!pause)
    {

        if (!player.dead && !player.win)
        {
            PlayerUpdate();
        }
        MinesUpdate();
        ExplosionsUpdate();
        BombUpdate();
        
    }

    CameraUpdate();

    BeginDrawing();

    ClearBackground(WHITE);

    BeginMode2D(camera);

    DrawBackground();

    DrawTiles(mat_begin, mat_end);

    RenderMines();


    //DrawRectangle(0, 0, 320, 180, BLUE);

    DrawExplosions();

    DrawBombs();

    DrawPlayer(); 

    if (debug)
    {
        DrawRectangleLinesEx(player.hitbox, 1.0f, RED);
        DrawCircleV(player.position, 2.0f, RED);

        DrawRectangleLinesEx(camera_bounds, 5.0f, BLACK);

        DrawRectangleLinesEx(level_bounds, 2.0f, YELLOW);

        for (int i = mat_begin.y; i < mat_end.y; i++) 
        {
            Color taint = RED;
            for (int j = mat_begin.x; j < mat_end.x; j++) 
            {

                if (tilemap[i][j].type == WALL)
                {
                    taint = BLUE;

                }else {

                    taint = RED;
                }

                DrawRectangleLinesEx(tilemap[i][j].tile, 1.0f, taint);

            }

        }

        for (int i = 0; i < mine_index; i++) {

            DrawRectangleLinesEx(minefild[i].hitbox, 1.0f, GREEN);


        }


    }

    if (!player.dead && !player.win)
    {
        DrawUi();
    }



    EndMode2D();


    DrawFPS(0, 0);
    if (debug)
    {
        char debug_pos[200];
        char debug_move[200];
        char debug_grid[200];
        sprintf(debug_pos, "X = %.2lf\nY = %.2lf\n", player.position.x, player.position.y);
        sprintf(debug_move, "Moving = %d", player.move);
        sprintf(debug_grid, "Grid X = %d\nGrid Y = %d\n", player.grid_pos.x, player.grid_pos.y);

        DrawText(debug_grid, screen.width -200, screen.height - 100, 20, GREEN);
        DrawText(debug_pos, screen.width -200, screen.height -40, 20, GREEN);
        DrawText(debug_move, screen.width -200, screen.height -60, 20, GREEN);
    }

    if (pause && !player.dead && !player.win)
    {
        PauseMenu();
    }

    if (player.win)
    {
        VictoryScreen();
    }

    if (player.dead)
    {
        DeathScreen();

    }



    EndDrawing();

}
