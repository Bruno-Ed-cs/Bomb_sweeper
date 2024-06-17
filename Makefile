
OS := Windows

WINE := false
CC:= gcc
WINECC := x86_64-w64-mingw32-gcc
TARGET := bombsweeper.exe

ifeq ($(WINE), true)
	CC := $(WINECC)
endif

ifeq ($(OS), Windows)
	libs :=  -L ./lib/Windows/ -lraylib -lm -lgdi32 -lwinmm 

else
	libs := -L ./lib/Linux/x11 -lraylib -lm
	TARGET := bombsweeper.bin
endif

CFLAGS := -Wall -O3 -g

./build/$(TARGET) : clean player.c main.c globals.c tilemap.c 
	echo "$(OS)"
	mkdir build
	cp -r ./assets ./build/
	$(CC) main.c player.c tilemap.c globals.c $(libs) $(CFLAGS) -o ./build/$(TARGET)

clean :
	rm -rf build
