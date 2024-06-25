
OS := Windows

WINE := false
CC:= gcc
WINECC := x86_64-w64-mingw32-gcc
TARGET := bombsweeper.exe
INCLUDE ?= WINDOWS 
X11 ?= true
OLEVEL := -Og

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

CFLAGS := -Wall $(OLEVEL) -g

./build/$(TARGET) : player.o main.o globals.o tilemap.o cJSON.o system.o game.o menus.o ./build/
	echo "$(OS)"
ifeq ($(X11), true)
	cp -r ./lib/Linux/x11/lib ./build/
endif

	$(CC) player.o main.o globals.o tilemap.o cJSON.o system.o game.o menus.o -D$(INCLUDE) $(libs) $(CFLAGS) -o ./build/$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -D$(INCLUDE) $(libs) -c $< -o $@

./build/ :
	mkdir build
	cp -r ./assets ./build/


clean :
	rm -rf build
	rm -r *.o
