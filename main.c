#include "globals.h"

int main()
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen.width, screen.height, "Bombsweeper 1.0 Alpha");

    SetWindowMinSize(INIT_WIDTH, INIT_HEIGHT);

    Color taint = RED;
    Tile** tilemap = InitMap();

    PopulateTilemap(tilemap);

    PlayerInit(tilemap);

    camera.target = (Vector2){player.position.x, player.position.y};
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screen.width /2, screen.height /2};
    camera.rotation = 0.0f;

    Mine *minefild = MineListInit();
    GenerateMinefild(minefild, tilemap);
    MapMines(minefild, tilemap);
    GetSorroundingMines(tilemap);

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
                minefild = ResetLevel(minefild, tilemap);

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

            PlayerUpdate(tilemap);
            camera.target = (Vector2){player.position.x, player.position.y};
            camera.offset = (Vector2){screen.width /2, screen.height /2};
            camera.zoom = (screen.width / INIT_WIDTH) + 3;
        }

        if (IsKeyReleased(KEY_F3))
        {
            debug = !debug;    
        }


        BeginDrawing();

        ClearBackground(WHITE);
        BeginMode2D(camera);

        DrawText("Isso definitivamente funciona",
                 100 - ((strlen("Isso definitivamente funciona") / 2.0f) * 10),
                 50 - 10,
                 20,
                 GREEN);
        for (int i = 0; i < map_height; i++) 
        {
            for (int j = 0; j < map_width; j++) {

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

                if (tilemap[i][j].type == FLOOR && tilemap[i][j].sorrounding_mines > 0 && tilemap[i][j].visible)
                {
                    DrawText(num, (tilemap[i][j].tile.x + (TILE_SIZE /2.0f)) -2, (tilemap[i][j].tile.y + (TILE_SIZE /2.0f)) - 5, 11, WHITE);
                }



            }

        }

        RenderMines(minefild);


        DrawTexturePro(player.sprite,
                       player.frame,
                       player.view,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        if (debug)
        {
            DrawRectangleLinesEx(player.hitbox, 1.0f, RED);
            DrawCircleV(player.position, 2.0f, RED);
            for (int i = 0; i < map_height; i++) 
            {
                for (int j = 0; j < map_width; j++) {

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

            DrawFPS(0, 0);

        }
        if (pause)
        {
            DrawText("Pause", screen.width /2, screen.height /2, 50, WHITE);

        }
        EndDrawing();

    }

    free(minefild);
    for (int i = 0; i < map_height; i++) {
        free(tilemap[i]);
    }
    free(tilemap);

    CloseWindow();
    return 0;
}
