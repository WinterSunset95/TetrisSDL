ifeq ($(OS), windows)
	OUT=./build/windows/tetris
	SDL2 = $(shell /home/autumn/Desktop/SDL/SDL2/bin/sdl2-config --static-libs --cflags)
	SDL2_IMAGE = -L/home/autumn/Desktop/SDL/SDL_Image/lib /home/autumn/Desktop/SDL/SDL_Image/lib/libSDL2_image.a
	CC = x86_64-w64-mingw32-gcc
else
	OUT=./build/linux/tetris
	SDL2 = $(shell sdl2-config --libs --cflags)
	SDL2_IMAGE = -lSDL2_image
	CC = gcc
endif

all:
	$(CC) -o $(OUT) ./src/*.c $(SDL2) $(SDL2_IMAGE)
