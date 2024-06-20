
OS := Windows

WINE := false
CC:= gcc
WINECC := x86_64-w64-mingw32-gcc
TARGET := bombsweeper.exe
INCLUDE ?= WINDOWS 
X11 ?= true

ifeq ($(WINE), true)
	CC := $(WINECC)
endif

ifeq ($(OS), Windows)
	libs :=  -L ./lib/Windows/ -lraylib -lm -lgdi32 -lwinmm
	X11 = false

else ifeq ($(X11), true)
	
	libs :=-Wl,-R ./lib -L ./lib/Linux/x11/lib -lraylib -lm 
	TARGET := bombsweeper.bin
	INCLUDE := X11

else 
	libs :=-L ./lib/Linux/wayland -lraylib -lm
	TARGET := bombsweeper.bin
	INCLUDE := WAYLAND

endif

CFLAGS := -Wall -O3 -g

./build/$(TARGET) : clean player.c main.c globals.c tilemap.c cJSON.c system.c
	echo "$(OS)"
	mkdir build
	cp -r ./assets ./build/

ifeq ($(X11), true)
	cp -r ./lib/Linux/x11/lib ./build/
endif

	$(CC) main.c player.c tilemap.c globals.c cJSON.c system.c -D$(INCLUDE) $(libs) $(CFLAGS) -o ./build/$(TARGET)

clean :
	rm -rf build
