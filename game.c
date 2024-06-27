#include "globals.h"

void Game()
{

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

    if (!pause)
    {

        PlayerUpdate();
        CameraUpdate();
        MinesUpdate();
        ExplosionsUpdate();
        BombUpdate();
        
    }

    BeginDrawing();

    ClearBackground(WHITE);

    BeginMode2D(camera);

    DrawTiles(mat_begin, mat_end);

    RenderMines();

    DrawPlayer(); 

    //DrawRectangle(0, 0, 320, 180, BLUE);

    for (int i = 0; i < explosion_qtd; i++)
    {

        DrawRectangleRec(explosion_buffer[i].center, RED);
        DrawRectangleRec(explosion_buffer[i].right, GREEN);
        DrawRectangleRec(explosion_buffer[i].left, YELLOW);
        DrawRectangleRec(explosion_buffer[i].top, PURPLE);
        DrawRectangleRec(explosion_buffer[i].bottom, BLUE);

    }

    for (int i = 0; i < bombs_qtd; i++)
    {
        DrawRectangleRec(bombs[i].hitbox, DARKBLUE);

    }

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

        PauseMenu();
    }



    DrawFPS(0, 0);

    char clock[100];
    sprintf(clock,"Time = %.2lf", timer);
    int str_size = strlen(clock) -1;

    DrawText(clock, (screen.width/2) - (str_size / 2.0f) *10, 10, 20, GREEN);

    EndDrawing();

}
