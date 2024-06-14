# Bomb_sweeper
Trabalho para introdução de programação, intodução a programação 

**Compilação 

Windows:
gcc main.c player.c tilemap.c globals.c libW\lib\raylib.dll libW\lib\libraylibdll.a libW\lib\libraylib.a -lm -lgdi32 -lwinmm -Wall -o bin/jooj.exe

Linux:
gcc main.c player.c tilemap.c globals.c -L ./lib/lib -lraylib -Wl,-R ./lib/lib -lm -Wall -o bin/jooj.bin


