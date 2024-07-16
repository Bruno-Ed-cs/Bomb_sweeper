
OS := Windows

WINE := false
CC:= gcc
WINECC := x86_64-w64-mingw32-gcc
TARGET := bombsweeper.exe
INCLUDE ?=
X11 ?= true
OLEVEL := -Og
RELEASE ?= false

ifeq ($(WINE), true)
	CC := $(WINECC)
endif

ifeq ($(OS), Windows)
	libs :=  -L ./lib/Windows/ -lraylib -lm -lgdi32 -lwinmm
	X11 = false

else ifeq ($(X11), true)

	libs :=-Wl,-R ./lib -L ./lib/Linux/x11/lib -lraylib -lm
	TARGET := bombsweeper.bin

else
	libs :=-L ./lib/Linux/wayland -lraylib -lm
	TARGET := bombsweeper.bin

endif

ifeq ($(RELEASE), true)

	OLEVEL := -O3
	CFLAGS := -Wall $(OLEVEL)
	INCLUDE := RELEASE
else

	OLEVEL := -Og
	CFLAGS := -Wall $(OLEVEL) -g
	INCLUDE := DEV
endif

./build/$(TARGET) : ./build/ score.o bombs.o explosions.o player.o main.o globals.o tilemap.o cJSON.o system.o game.o menus.o
	echo "$(OS)"


	$(CC) player.o main.o bombs.o score.o explosions.o globals.o tilemap.o cJSON.o system.o game.o menus.o -D$(INCLUDE) $(libs) $(CFLAGS) -o ./build/$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -D$(INCLUDE) $(libs) -c $< -o $@

./build/ :
	mkdir build
	cp -r ./assets ./build/

ifeq ($(X11), true)
	cp -r ./lib/Linux/x11/lib ./build/
endif


clean :
	rm -rf build
	rm -r *.o
