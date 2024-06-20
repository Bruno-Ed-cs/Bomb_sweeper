#include "globals.h"
#include "include/Linux/wayland/raylib.h"
 
int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    //SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screen.width, screen.height, "Bombsweeper 1.0 Alpha");

    SetWindowMinSize(INIT_WIDTH, INIT_HEIGHT);

    Color taint = RED;


    LoadLevel("./assets/levels/mapa1.json");
    PlayerInit();

    camera_bounds.x = player.position.x - (camera_bounds.width / 2);
    camera_bounds.y = player.position.y - (camera_bounds.height / 2);
    camera.rotation = 0.0f;

    MineListInit();
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();



    SetTargetFPS(-1);
    while (!WindowShouldClose()) {


        if (pause)
        {

            dt = 0; 

        } else 
        {

            dt = GetFrameTime();

        }

        timer += dt;

        GridPos mat_begin = GetMatrixBegin(player.grid_pos, 20);
        GridPos mat_end = GetMatrixEnd(player.grid_pos, 20);

        InputHandler(GetKeyPressed()); //pega os inputs para o controle do sistema
        
        //atualiza as dimensoes da tela
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

        if (!pause)
        {

            PlayerUpdate();
            CameraUpdate();
        }
              
        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode2D(camera);

                DrawTiles(mat_begin, mat_end);

                RenderMines();

                DrawPlayer(); 


                //DrawRectangle(0, 0, 320, 180, BLUE);
                

                if (debug)
                {
                    DrawRectangleLinesEx(player.hitbox, 1.0f, RED);
                    DrawCircleV(player.position, 2.0f, RED);

                    DrawRectangleLinesEx(camera_bounds, 5.0f, BLACK);
                    
                    DrawRectangleLinesEx(level_bounds, 2.0f, YELLOW);

                    for (int i = mat_begin.y; i < mat_end.y; i++) 
                    {
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

            EndMode2D();


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
            if (pause)
            {
                DrawText("Pause", screen.width /2, screen.height /2, 50, WHITE);

            }

            DrawFPS(0, 0);

            char clock[100];
            sprintf(clock,"Time = %.2lf", timer);
            int str_size = strlen(clock) -1;

            DrawText(clock, (screen.width /2) - (str_size / 2.0f) *10, 10, 20, GREEN);
            
        EndDrawing();

    }

    free(minefild);
    UnloadLevel();
    free(tilemap);

    CloseWindow();
    return 0;
}
