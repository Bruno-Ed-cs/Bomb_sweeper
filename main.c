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

    camera.target = (Vector2){player.position.x, player.position.y};
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screen.width /2, screen.height /2};
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

        if (IsKeyReleased(KEY_P))
        {
            pause = !pause;
        }


        if (debug)
        {
            if (IsKeyReleased(KEY_R)) 
            {
                ResetLevel();

            }
        }

        if (IsWindowFullscreen())
        {

            screen.height = GetMonitorHeight(GetCurrentMonitor());
            screen.width = GetMonitorWidth(GetCurrentMonitor());

        } else 
        {
            screen.height = GetScreenHeight();
            screen.width = GetScreenWidth();

        }


        if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT))
        {

            ToggleFullscreen();

            SetWindowSize(screen.width, screen.height); //quando a tela cheia é ativada ou desativada atualizamos o tamanho da janela para que todos os valores dependent delas continuem corretos
        }

        if (!pause)
        {

            PlayerUpdate();
        }
        camera.target = (Vector2){player.position.x, player.position.y};
        camera.offset = (Vector2){screen.width /2, screen.height /2};
        camera.zoom = (screen.width / INIT_WIDTH) * 3.5;


        if (IsKeyReleased(KEY_F3))
        {
            debug = !debug;    
        }
        
        GridPos mat_begin = GetMatrixBegin(player.grid_pos, 13);
        GridPos mat_end = GetMatrixEnd(player.grid_pos, 13);


        BeginDrawing();

        ClearBackground(WHITE);
        BeginMode2D(camera);

        DrawText("Isso definitivamente funciona",
                 100 - ((strlen("Isso definitivamente funciona") / 2.0f) * 10),
                 50 - 10,
                 20,
                 GREEN);


        for (int i = mat_begin.y; i < mat_end.y; i++) 
        {
            for (int j = mat_begin.x; j < mat_end.x; j++) {



                tile_view = tilemap[i][j].tile;
                if (tilemap[i][j].type == WALL)
                {
                    tile_frame.x = TILE_SIZE;

                }else {

                    tile_frame.x = 0;
                }

                if (tilemap[i][j].visible)
                {


                    DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, PURPLE);

                } else {

                    DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, ColorTint(PURPLE, GRAY));

                }

                char num[10];
                sprintf(num, "%d" ,tilemap[i][j].sorrounding_mines);

                if (tilemap[i][j].type == FLOOR && tilemap[i][j].sorrounding_mines > 0 && tilemap[i][j].visible && !tilemap[i][j].flaged)
                {
                    DrawText(num, (tilemap[i][j].tile.x + (TILE_SIZE /2.0f)) -2, (tilemap[i][j].tile.y + (TILE_SIZE /2.0f)) - 5, 11, WHITE);
                }


                if (tilemap[i][j].flaged == true)
                {

                    tile_frame.x = TILE_SIZE * 3;
                    DrawTexturePro(tileset, tile_frame, tile_view, (Vector2){0,0}, 0.0f, WHITE);
                }


            }

        }

        RenderMines();

        DrawPlayer();

        if (debug)
        {
            DrawRectangleLinesEx(player.hitbox, 1.0f, RED);
            DrawCircleV(player.position, 2.0f, RED);

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
        EndDrawing();

    }

    free(minefild);
    UnloadLevel();
    free(tilemap);

    CloseWindow();
    return 0;
}
