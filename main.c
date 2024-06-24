#include "globals.h"
#include "include/Linux/wayland/raylib.h"


void ResetGame()//Fiz uma funcao para a inicializaçao, para que eu pudesse usar pra reiniciar toda vez que entra no menu
{
    LoadLevel("./assets/levels/mapa1.json");
    PlayerInit();

    camera_bounds.x = player.position.x - (camera_bounds.width / 2);
    camera_bounds.y = player.position.y - (camera_bounds.height / 2);
    camera.rotation = 0.0f;

    MineListInit();
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();

    timer = 0;
    pause = false;
}


 
int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    //SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(INIT_WIDTH, INIT_HEIGHT, "Bombsweeper 1.0 Alpha");

    SetWindowMinSize(INIT_WIDTH, INIT_HEIGHT);


    Color taint = RED;

    ResetGame();

    //Nao sei como colocar nos globals e ficar funcional


    //Tela de Menu
    Rectangle exit_menu = {INIT_WIDTH / 2 - 55, INIT_HEIGHT  / 2 - 10, 127, 60};
    Rectangle exit_menu2 = {(INIT_WIDTH / 2 - 55) - 5, (INIT_HEIGHT  / 2 - 10) - 5, 137, 75};
    Color c_exit_menu = WHITE;
    Color c_exit_menu2 = WHITE;

    //Tela de Pausa
    Rectangle exit_pause = {(INIT_WIDTH /2 - 70) + 20, INIT_HEIGHT / 2 - 15, 118, 50};
    Rectangle exit_pause2 = {((INIT_WIDTH /2 - 70) + 20) - 5, (INIT_HEIGHT / 2 - 15) - 5, 118 + 10, 50 + 10};
    Rectangle continue_pause = {INIT_WIDTH /2 - 100, 245, 215, 50};
    Rectangle continue_pause2 = {(INIT_WIDTH /2 - 100) - 5, 240, 225, 60};
    Color c_exit_pause = LIGHTGRAY;
    Color c_continue_pause = LIGHTGRAY;
    Color c_continue_pause2 = WHITE;
    Color c_jogar = BLACK;
    Color c_sair = BLACK;

    

   
    



    SetTargetFPS(-1);

    while (!WindowShouldClose()) {

         
         
    Vector2 mouse = GetMousePosition();



        //Trouxe a configuraçao de fullScreen aqui para funcionar no menu
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


            SetWindowSize(INIT_WIDTH, INIT_HEIGHT); //quando a tela cheia é ativada ou desativada atualizamos o tamanho da janela para que todos os valores dependent delas continuem corretos

        }

        switch(CurrentScreen){

           

            case MENU:

            

             
            if( CheckCollisionPointRec( mouse, exit_menu ) ){

                c_exit_menu2 = GREEN;

                c_jogar = GREEN;



                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

                    ResetGame();

                    CurrentScreen = GAME;

                }

            }else{

                c_exit_menu2 = WHITE;

                c_jogar = BLACK;

            }

                BeginDrawing();

                ClearBackground(WHITE);

                DrawText("BETA",INIT_WIDTH - 100 , INIT_HEIGHT - 50, 20, BLACK);

                DrawText("MENU", INIT_WIDTH / 2 - 70, 20, 50, BLACK);

                DrawRectangleRec(exit_menu2, c_exit_menu2);

                DrawRectangleRec(exit_menu, c_exit_menu);

                DrawText("Jogar", INIT_WIDTH / 2 - 50, INIT_HEIGHT  / 2, 40, c_jogar);

                EndDrawing();

            

             
                
                break;
            
            //case MENU


    case GAME:

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


                DrawText(debug_grid, INIT_WIDTH -200, INIT_HEIGHT - 100, 20, GREEN);
                DrawText(debug_pos, INIT_WIDTH -200, INIT_HEIGHT -40, 20, GREEN);
                DrawText(debug_move, INIT_WIDTH -200, INIT_HEIGHT -60, 20, GREEN);



            }
            if (pause)
            {

                 if( CheckCollisionPointRec( mouse, exit_pause ) ){

                c_exit_pause = BLACK;

                c_sair = RED;


                DrawRectangleRec(exit_pause2, RED);

                DrawRectangleRec(exit_pause, c_exit_pause);
                

                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

                    CurrentScreen = MENU;

                }


                }else{

                     c_sair = WHITE;

                }


                 if( CheckCollisionPointRec( mouse, continue_pause ) ){

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

                

                DrawText("Pause", INIT_WIDTH /2 - 64, 100, 50, BLACK );



                

                DrawText("Continuar", INIT_WIDTH /2 - 90, 250, 40, c_continue_pause2);



              

                DrawText("Sair", (INIT_WIDTH /2  - 50) + 20, 350, 40, c_sair);

            

            
            }

            DrawFPS(0, 0);

            char clock[100];
            sprintf(clock,"Time = %.2lf", timer);
            int str_size = strlen(clock) -1;

            DrawText(clock, (INIT_WIDTH /2) - (str_size / 2.0f) *10, 10, 20, GREEN);
            
        EndDrawing();
        
        break;
        
            

        }//Switch
    
    }

    free(minefild);
    UnloadLevel();
    free(tilemap);

    CloseWindow();
    return 0;
}
