#include "globals.h"
#include "include/cJSON.h"
#include "include/raylib.h"
#include <stdio.h>

int GetLevelScore(char * level)
{

    FILE *file = fopen("./save.json", "r");

    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);

    cJSON *score = cJSON_GetObjectItem(json, level);

    int level_score = score->valueint;

    cJSON_Delete(json);

    return level_score;
}   



void RegisterScore(char *level, int score)
{
    FILE *file = fopen("./save.json", "r");
        
    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);

    cJSON *level_score = cJSON_GetObjectItem(json, level);

    cJSON_SetNumberValue(level_score, score);
    
    char *json_string = cJSON_Print(json);



    file = fopen("./save.json", "w");

    printf("%s\n", json_string);

    fputs(json_string, file);
    fclose(file);

    cJSON_free(json_string);
    cJSON_Delete(json);

}

bool IsScoreHigher(char *level)
{

    FILE *file = fopen("./save.json", "r");

    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), file);
    printf("%d\n", len);
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);

    cJSON *score = cJSON_GetObjectItem(json, level);

    if (final_score > score->valueint)
    {
        cJSON_Delete(json);
        return true;
    } else {
    
        cJSON_Delete(json);
        return false;
    }

}

void CreateSavefile()
{
    FILE *file = fopen("./save.json", "w");

    cJSON *json = cJSON_CreateObject();
    

    cJSON_AddNumberToObject(json, "beach_day", 0);
    cJSON_AddNumberToObject(json, "dejavu", 0);
    cJSON_AddNumberToObject(json, "crystal_cove", 0);

    char *json_string = cJSON_Print(json);

    printf("%s\n", json_string);

    fputs(json_string, file);
    fclose(file);

    cJSON_free(json_string);
    cJSON_Delete(json);

}

// função para atualizar o volume dos sons
// Usa as variaveis globais music_list e sfx_list
void UpdateVolume()
{

    if (general_volume > 1) general_volume = 1;
    if (sfx_volume > 1) sfx_volume = 1;
    if (music_volume > 1) music_volume = 1;


    if (general_volume < 0) general_volume = 0;
    if (sfx_volume < 0) sfx_volume = 0;
    if (music_volume < 0) music_volume = 0;


    int size_arr;

    SetMasterVolume(general_volume);

    size_arr = sizeof(music_list)/ sizeof(music_list[0]);

    for (int i = 0; i < size_arr; i++)
    {
        SetMusicVolume(*music_list[i], music_volume);
    }

    size_arr = sizeof(sfx_list) / sizeof(sfx_list[0]);

    for (int i = 0; i < size_arr; i++)
    {
        SetSoundVolume(*sfx_list[i], sfx_volume);

    }

}

//funcao para inicializar o jogo
void InitGame(char * level_path)
{
    LoadLevel(level_path);
    ResetLevel();
}

// funcao para reiniciar / inicia as variaveis do nivel 
void ResetLevel() 
{
    mine_index = 0;
    bombs_qtd = 0;
    explosion_qtd = 0;
    minutes = 0;
    seconds = 0;
    timer = 0;
    pause = false;
    final_score = 0;

    // for pra resetar todas as tiles do jogo
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (tilemap[y][x].type == FLOOR)
            {
                tilemap[y][x].visible = false;
                tilemap[y][x].flaged = false;
                tilemap[y][x].bombed = false;
            }
        }
    }

    // funcoes para inicializar as minas
    MineListInit(); 
    GenerateMinefild();
    MapMines();
    GetSorroundingMines();
    
    // funcao de inicializacao do jogador
    PlayerInit();


};

// funcao para desenhar o cenario baseado no tamnho do nivel
void DrawBackground()
{
    double x ,y;

    x = world_origin.x - ((background.width/2.0f) - (level_bounds.width/2.0f)); 
    y = world_origin.y - ((background.height/2.0f) - (level_bounds.height/2.0f)); 

    DrawTextureV(background,(Vector2){x, y} , WHITE);

}

// funcao para lidar com inputs extras nao relacionados diretamente com a gamelay 
void InputHandler(int input)
{
    switch (input) {

        case KEY_P:
            pause = !pause;
            break;


        case KEY_R:

            if(pause) ResetLevel();

            break;

        case KEY_F3:
            debug = !debug;
            break;


    }

};

// funcao para carregar as imagens e sons
void LoadAssets()
{
    footstep_sfx = LoadSound("./assets/audio/sfx/Retro FootStep 03.wav");
    custom_font = LoadFontEx("./assets/fonts/Hardpixel.OTF",  128, NULL, 0);
    tileset = LoadTexture("./assets/sprites/tileset.png");
    bomb_sheet = LoadTexture("./assets/sprites/bomb.png");
    menu_theme = LoadMusicStream("./assets/audio/music/menu_theme.mp3");
    level_music = LoadMusicStream("./assets/audio/music/tutorial_theme.mp3");
    explosion_sheet = LoadTexture("./assets/sprites/explosion.png");
    background = LoadTexture("./assets/sprites/background_dejavu.png");
    clock_sprite = LoadTexture("./assets/sprites/clock.png");
    wallet_sprite = LoadTexture("./assets/sprites/wallet.png");
    MenuTela = LoadTexture("./assets/sprites/menumap.png");
    thumb_beach = LoadTexture("./assets/sprites/beach_thumb.png");
    pause_ui = LoadTexture("./assets/sprites/pause_ui.png");
    volume_slide = LoadTexture("./assets/sprites/volume.png");
    guide_ui = LoadTexture("./assets/sprites/guide.png");

    explosion_sfx = LoadSound("./assets/audio/sfx/explosion.mp3");
    flag_sfx = LoadSound("./assets/audio/sfx/flag.mp3");
    place_bomb_sfx = LoadSound("./assets/audio/sfx/place_bomb.mp3");
    button_click = LoadSound("./assets/audio/sfx/Som de clique de mouse menu.WAV");
    fuse_sfx = LoadSound("./assets/audio/sfx/fuse.mp3");
    win_theme = LoadSound("./assets/audio/sfx/tema_vitoria.mp3");
    lose_theme = LoadSound("./assets/audio/sfx/tema_derrota.mp3");
}

// funcao para liberar as imagens e sons da memoria
void UnloadAssets()
{
    UnloadSound(footstep_sfx);
    UnloadTexture(tileset);
    UnloadFont(custom_font);
    UnloadTexture(bomb_sheet);
    UnloadMusicStream(menu_theme);
    UnloadMusicStream(level_music);
    UnloadTexture(explosion_sheet);
    UnloadTexture(background);
    UnloadTexture(clock_sprite);
    UnloadTexture(wallet_sprite);
    UnloadTexture(MenuTela);
    UnloadTexture(thumb_beach);
    UnloadTexture(volume_slide);
    UnloadTexture(guide_ui);

    UnloadSound(explosion_sfx);
    UnloadSound(flag_sfx);
    UnloadSound(place_bomb_sfx);
    UnloadSound(button_click);
    UnloadSound(fuse_sfx);
    UnloadSound(win_theme);
    UnloadSound(lose_theme);

}

// funcao para pegar o inicio da submatriz de renderização
GridPos GetMatrixBegin(GridPos origin, int radius)
{
    GridPos begining;

    begining.x = origin.x - radius;
    begining.y = origin.y - radius;

    if (begining.x < 0) begining.x = 0;
    if (begining.y < 0) begining.y = 0;

    return begining;

};

// funcao para pegar o final da submatriz de renderização
GridPos GetMatrixEnd(GridPos origin, int radius)
{
    GridPos end;

    end.x = origin.x + radius;
    end.y = origin.y + radius;

    if (end.x >= map_width) end.x = map_width;
    if (end.y >= map_height) end.y = map_height;

    return end;

};

// funcao para comparar o tipo de um tile
int GetTileType(GridPos tile, int type)
{

    // if para validar se a posicao na matriz é valida
    if (!ValidateGridPos(tile)) return 0;

    return tilemap[tile.y][tile.x].type;

};

//funcao para verificar se uma posicao na matriz é valida para evitar segfaults
bool ValidateGridPos(GridPos posisition)
{
    if (posisition.y >= map_height || posisition.y < 0)
        return false;

    if (posisition.x >= map_width || posisition.x < 0)
        return false;

    return true;
};

// funcao para determinar a distancia entre duas posicoes na matriz
int TileDistance(GridPos a, GridPos b)
{
    return sqrt((pow(b.x - a.x, 2)) + (pow(b.y - a.y, 2)));

};
