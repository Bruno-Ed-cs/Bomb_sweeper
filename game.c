#include "globals.h"

// função para criar a tela de vitoria quando terminar o nível
void VictoryScreen()
{
    GetFinalScore(); //funcao para pegar a pontuacao

    //cores personalizadas para os butoes e background
    Color background_color = {51, 255, 51, 120};
    Color button_color = {129, 129, 129 ,200};

    // stings para serem usadas na ui
    char exit_message[50] = "Exit";
    char respawn_message[50] = "Respawn";
    char score_message[100];
    char mine_message[100];
    char tile_message[100];
    char time_message[100];
    
    // agregamos aos buffers as strings com as variaveis
    sprintf(tile_message, "Revealed Tiles : %d", GetRevealedTiles());
    sprintf(time_message, "Time Bonus : %02d:%02d +%d $", (int)(player.final_time) / 60, (int)(player.final_time) % 60, GetTimeBonus());
    sprintf(mine_message, "Mines : %d/%d +%d $", GetFlagedMines(), mine_index, GetFlagedMines() * 150);
    sprintf(score_message, "Salary : %d $", final_score);

    Vector2 win_pos = {screen.width/2 - (MeasureText("You Win!", 128) + MeasureText("", 128))/2.0f , screen.height/5.0f};

    // retangulos dos botoes
    Rectangle respawn_button = {(screen.width/2) -150, screen.height /2 + 100, 300, 60};
    Rectangle exit_button = {respawn_button.x, respawn_button.y + respawn_button.height +10, 300, 60};

    // posisoes dos textos dos botoes
    Vector2 exit_text_pos = {exit_button.x + 10, exit_button.y - 5};
    Vector2 respawn_text_pos = {respawn_button.x + 10, respawn_button.y - 5};

    // desenha o verde transparente no fundo
    DrawRectangleRec(screen, background_color);

    //desenha os botoes
    DrawRectangleRec(respawn_button, button_color);
    DrawRectangleRec(exit_button, button_color);

    DrawTextEx(custom_font, "You Win!", win_pos, 128, 0, WHITE);

    // desenha as estatisticas da pontuação
    DrawTextEx(custom_font, tile_message, (Vector2){win_pos.x, win_pos.y + 150 + 32}, 32, 0, WHITE);
    DrawTextEx(custom_font, time_message, (Vector2){win_pos.x, win_pos.y + 150}, 32, 0, WHITE);
    DrawTextEx(custom_font, mine_message, (Vector2){win_pos.x, win_pos.y + 150 + (32 *2)}, 32, 0, WHITE);
    DrawTextEx(custom_font, score_message, (Vector2){win_pos.x, win_pos.y + 150 + (32 *3)}, 32, 0, WHITE);

    // desenha as palavras nos botoes
    DrawTextEx(custom_font, exit_message, exit_text_pos, 64, 0, WHITE);
    DrawTextEx(custom_font, respawn_message, respawn_text_pos, 64, 0, WHITE);


    // ifs para checar se o mause esta nos botoes e se foi clicado

    if( CheckCollisionPointRec( mouse_pos, respawn_button) ){



        DrawRectangleLinesEx(respawn_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            // para o tema de vitoria se ainda tiver tocando
            if (IsSoundPlaying(win_theme)) StopSound(win_theme);
            PlaySound(button_click);
            ResetLevel();// reinicia o nivel
        }


    }

    if( CheckCollisionPointRec( mouse_pos, exit_button) ){



        DrawRectangleLinesEx(exit_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if (IsSoundPlaying(win_theme)) StopSound(win_theme);
            PlaySound(button_click);
            UnloadLevel();// decarrega o nivel
            state = START_MENU;// volta para o menu inicial


        }


    }



}

void DeathScreen()
{
    // cores
    Color background_color = {229, 57, 53, 120};
    Color button_color = {129, 129, 129 ,200};

    // mensagens para mostrar ao jogador
    char death_message[50] = "You Died";
    char exit_message[50] = "Exit";
    char respawn_message[50] = "Respawn";

    Vector2 death_message_pos = {screen.width/2 - (MeasureText(death_message, 128) + MeasureText("", 128))/2.0f , screen.height/4.0f};

    // botoes
    Rectangle respawn_button = {(screen.width/2) -150, screen.height /2 + 100, 300, 60};
    Rectangle exit_button = {respawn_button.x, respawn_button.y + respawn_button.height +10, 300, 60};


    // posicoes de texto para os botoes
    Vector2 exit_text_pos = {exit_button.x + 10, exit_button.y - 5};
    Vector2 respawn_text_pos = {respawn_button.x + 10, respawn_button.y - 5};

    // desenha o fundo transparente 
    DrawRectangleRec(screen, background_color);

    // desenha os botoes
    DrawRectangleRec(respawn_button, button_color);
    DrawRectangleRec(exit_button, button_color);

    DrawTextEx(custom_font, "You Died", death_message_pos, 128, 0, WHITE);

    // desenha os rotulos dos botoes
    DrawTextEx(custom_font, exit_message, exit_text_pos, 64, 0, WHITE);
    DrawTextEx(custom_font, respawn_message, respawn_text_pos, 64, 0, WHITE);

    // ifs para verificar as colisoes dos botoes com o mouse e aplica seu efeito se clicado
    if( CheckCollisionPointRec( mouse_pos, respawn_button) ){



        DrawRectangleLinesEx(respawn_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if (IsSoundPlaying(lose_theme)) StopSound(lose_theme);
            PlaySound(button_click);
            ResetLevel();
        }


    }
    
    // atalho para renascer
    if (IsKeyPressed(KEY_R))
    {
        pause = false;
        ResetLevel();
    }

    if( CheckCollisionPointRec( mouse_pos, exit_button) ){



        DrawRectangleLinesEx(exit_button, 5.0f, WHITE);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if (IsSoundPlaying(lose_theme)) StopSound(lose_theme);
            PlaySound(button_click);
            UnloadLevel();
            state = START_MENU;


        }


    }

}

void PauseMenu()
{
    Vector2 origin = {camera_bounds.x + camera_bounds.width/2, camera_bounds.y + camera_bounds.height/2};

    DrawCircleV(origin, 10.0f, RED);

    double win_width = 150;
    double win_height = 200;
    double gap = 20;
    double button_width = 100;
    double button_height = 25;
    double font_size = 20;


    Rectangle window = {origin.x - win_width/2, origin.y - win_height/2 - 6, win_width, win_height};
    Rectangle backdrop = {window.x, window.y + button_height + 10, win_width -5, win_height - button_height - 10};
    Rectangle backdrop_top = {window.x +4, window.y + 5, 61, 30};
    Rectangle frame = {0, 0, win_width, win_height};

    Rectangle button1 = {window.x + win_width/2 - button_width/2, window.y + 50, button_width, button_height};
    Rectangle button2 = {button1.x, button1.y + button_height + gap, button_width, button_height};
    Rectangle button3 = {button2.x, button2.y + button_height + gap, button_width, button_height};

    Rectangle *button_list[3] = {&button1, &button2, &button3};

    char text[3][50] = {"Continue", "Audio", "Exit"};


    DrawRectangleRec(backdrop, BLACK);
    DrawRectangleRec(backdrop_top, BLACK);
    /**
    DrawRectangleRec(button1, GRAY);
    DrawRectangleRec(button2, GRAY);
    DrawRectangleRec(button3, GRAY);
    **/

    DrawTextEx(custom_font, "Pause", (Vector2){window.x + 8, window.y + 8}, 20, 1, RED);

    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), *button_list[i]))
        {
            DrawTextPro(custom_font, text[i], (Vector2){button_list[i]->x + button_width/2, button_list[i]->y + button_height/2},
                        (Vector2){ MeasureTextEx(custom_font, text[i], 20, 1).x / 2.0f, MeasureTextEx(custom_font, text[i], font_size, 1).y / 2.0f},
                        0, font_size, 1, GREEN);
            //printf("aaa\n");

        } else 
    {
            DrawTextPro(custom_font, text[i], (Vector2){button_list[i]->x + button_width/2, button_list[i]->y + button_height/2},
                        (Vector2){ MeasureTextEx(custom_font, text[i], 20, 1).x / 2.0f, MeasureTextEx(custom_font, text[i], font_size, 1).y / 2.0f},
                        0, font_size, 1, WHITE);

        }
    }

    DrawTexturePro(pause_ui, frame, window, (Vector2){0, 0}, 0, WHITE);

    if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), button1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        PlaySound(button_click);
        pause = false;

    }

    if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), button2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        PlaySound(button_click);
        game_ui = AUDIO;

    }

    if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), button3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        PlaySound(button_click);
        UnloadLevel();
        state = SELECT_MENU;

    }
}

void AudioMenu()
{
    Vector2 origin = {camera_bounds.x + camera_bounds.width/2, camera_bounds.y + camera_bounds.height/2};
    double *volumes[3] = {&music_volume, &sfx_volume, &general_volume};

    double win_width = 150;
    double win_height = 200;
    double gap = 20;
    double button_width = 100;
    double button_height = 16;
    double font_size = 16;


    Rectangle window = {origin.x - win_width/2, origin.y - win_height/2 - 6, win_width, win_height};
    Rectangle backdrop = {window.x, window.y + button_height + 10, win_width -5, win_height - button_height - 10};
    Rectangle backdrop_top = {window.x +4, window.y + 5, 61, 30};
    Rectangle frame = {0, 0, win_width, win_height};

    Rectangle vol_music = {window.x + win_width/2 - button_width/2, window.y + 60, (button_width -32) * music_volume, button_height};
    Rectangle music_plus = {vol_music.x + (button_width - 32), vol_music.y, TILE_SIZE, TILE_SIZE};
    Rectangle music_minus = {vol_music.x + (button_width - 32) + 16, vol_music.y, TILE_SIZE, TILE_SIZE};

    Rectangle vol_sfx = {vol_music.x, vol_music.y + button_height + gap, (button_width -32) * sfx_volume, button_height};
    Rectangle sfx_plus = {vol_sfx.x + (button_width - 32), vol_sfx.y, TILE_SIZE, TILE_SIZE};
    Rectangle sfx_minus = {vol_sfx.x + (button_width - 32) + 16, vol_sfx.y, TILE_SIZE, TILE_SIZE};

    Rectangle vol_master = {vol_sfx.x, vol_sfx.y + button_height + gap, (button_width -32) * general_volume, button_height};
    Rectangle master_plus = {vol_master.x + (button_width - 32), vol_master.y, TILE_SIZE, TILE_SIZE};
    Rectangle master_minus = {vol_master.x + (button_width - 32) + 16, vol_master.y, TILE_SIZE, TILE_SIZE};

    Rectangle button = {vol_master.x, vol_master.y + button_height + gap, button_width, 25};

    Rectangle* plus_button_list[3] = {&music_plus, &sfx_plus, &master_plus};
    Rectangle* minus_button_list[3] = {&music_minus, &sfx_minus, &master_minus};   
    Rectangle *button_list[4] = {&vol_music, &vol_sfx, &vol_master, &button};

    char labels[3][50];


    sprintf(labels[0], "Music: %.0lf", music_volume * 100);
    sprintf(labels[1], "Sfx: %.0lf", sfx_volume * 100);
    sprintf(labels[2], "Master: %.0lf", general_volume * 100);

    DrawRectangleRec(backdrop, BLACK);
    DrawRectangleRec(backdrop_top, BLACK);

    DrawTextEx(custom_font, "Audio", (Vector2){window.x + 8, window.y + 8}, 20, 1, RED);




    for (int i = 0; i < 3; i++)
    {

        DrawTexturePro(volume_slide, (Rectangle){0,0, (button_width -32) * *volumes[i], button_height}, *button_list[i], (Vector2){0, 0}, 0, WHITE);

        DrawTextPro(custom_font, labels[i], (Vector2){button_list[i]->x, button_list[i]->y - font_size},
                    (Vector2){0, 0},
                    0, font_size, 1, WHITE);

        //DrawRectangleRec(*plus_button_list[i], PINK);
        //DrawRectangleRec(*minus_button_list[i], RED);

        tile_frame.y = TILE_SIZE * 5;
        tile_frame.x = 0;

        if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), *plus_button_list[i]))
        {
            DrawTexturePro(tileset, tile_frame, *plus_button_list[i], (Vector2){0, 0}, 0, GREEN);
        } else {
            DrawTexturePro(tileset, tile_frame, *plus_button_list[i], (Vector2){0, 0}, 0, WHITE);
        }

        tile_frame.x = TILE_SIZE;

        if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), *minus_button_list[i]))
        {
            DrawTexturePro(tileset, tile_frame, *minus_button_list[i], (Vector2){0, 0}, 0, GREEN);
        } else {
            DrawTexturePro(tileset, tile_frame, *minus_button_list[i], (Vector2){0, 0}, 0, WHITE);
        }

        if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), *minus_button_list[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(button_click);
            *volumes[i] -= 0.1f;
        }

        if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), *plus_button_list[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(button_click);
            *volumes[i] += 0.1f;
        }

    }

    /**
    for (int i = 0; i < 4; i++)
    {
        DrawRectangleRec(*button_list[i], GRAY);

    }
    **/

    if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), button))
    {
        DrawTextPro(custom_font, "Back", (Vector2){button.x + button.width/2, button.y + button.height/2},
                    (Vector2){ MeasureTextEx(custom_font, "Back", 20, 1).x / 2.0f, MeasureTextEx(custom_font, "Back", font_size, 1).y / 2.0f},
                    0, font_size, 1, GREEN);

    }else {
        DrawTextPro(custom_font, "Back", (Vector2){button.x + button.width/2, button.y + button.height/2},
                    (Vector2){ MeasureTextEx(custom_font, "Back", 20, 1).x / 2.0f, MeasureTextEx(custom_font, "Back", font_size, 1).y / 2.0f},
                    0, font_size, 1, WHITE);

    }
    DrawTexturePro(pause_ui, frame, window, (Vector2){0, 0}, 0, WHITE);

    if (CheckCollisionPointRec(GetScreenToWorld2D(mouse_pos, camera), button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

        PlaySound(button_click);
        game_ui = PAUSE;
    }
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

    if (!player.win && !player.dead)
    {
        UpdateMusicStream(level_music);
    }

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

    GridPos mat_begin = GetMatrixBegin(player.grid_pos, RENDER_DISTANCE);
    GridPos mat_end = GetMatrixEnd(player.grid_pos, RENDER_DISTANCE);

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

        if (!player.dead && !player.win && !pause)
        {
            DrawUi();
        }

    if (pause && !player.dead && !player.win)
    {
        switch (game_ui) {
            case PAUSE:

            PauseMenu();
            break;

            case AUDIO:
                //printf("pa\n");
                AudioMenu();
            break;
        
        }

    }



    EndMode2D();


    #ifdef DEV
    
    DrawFPS(0, 0);
    #endif /* ifdef DEV */

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
