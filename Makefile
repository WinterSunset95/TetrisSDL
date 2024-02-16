# for windows

SRC = $(wildcard ./src/*.c)
HDR = $(wildcard ./src/*.h)

ifeq ($(OS), windows)
	LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	CFLAGS = -Wall -g -std=c99
	CC = x86_64-w64-mingw32-gcc
else
	LIBS = -lSDL2 -lSDL2_image
	CFLAGS = -Wall -g -std=c99
	CC = gcc
endif

all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o ./build/tetris
