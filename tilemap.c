#if defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-w64 compiler
#include "libW/include/raylib.h"
#elif defined(__GNUC__)
// GCC compiler
#include "lib/raylib.h"
#else
#error "Unknown compiler. Please define the appropriate include file for your compiler."
#endif

#include "globals.h"
#include <stdbool.h>



int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 1, 1, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

Tile tilemap[10][10];

void PopulateTilemap(int size, Tile tilemap[size][size], int origin[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {

            tilemap[i][j].tile_pos = (Vector2){i, j};
            tilemap[i][j].tile = (Rectangle){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            
            switch (origin[i][j]) {

                case WALL: tilemap[i][j].type = WALL;
                break;
 
                case FLOOR: tilemap[i][j].type = FLOOR;
                break;           

                case AIR: tilemap[i][j].type = AIR;
                break;
            }

        
        }

    }
    

}



