#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#define WINDOW_WIDTH 815
#define WINDOW_HEIGHT 610

#define LEFT_DIV_WIDTH 610
#define LEFT_DIV_HEIGHT 610
#define LEFT_DIV_X 0
#define LEFT_DIV_Y 0
#define TOP_RIGHT_DIV_WIDTH 210
#define TOP_RIGHT_DIV_HEIGHT 310
#define TOP_RIGHT_DIV_X 605
#define TOP_RIGHT_DIV_Y 0
#define BOTTOM_RIGHT_DIV_WIDTH 210
#define BOTTOM_RIGHT_DIV_HEIGHT 310
#define BOTTOM_RIGHT_DIV_X 605
#define BOTTOM_RIGHT_DIV_Y 300

#define GAME_SCREEN_WIDTH 300
#define GAME_SCREEN_HEIGHT 600
#define GAME_SCREEN_X 5
#define GAME_SCREEN_Y 5

#define SCORE_SCREEN_WIDTH 200
#define SCORE_SCREEN_HEIGHT 300
#define SCORE_SCREEN_X 600
#define SCORE_SCREEN_Y 5

#define HELP_SCREEN_WIDTH 200
#define HELP_SCREEN_HEIGHT 300
#define HELP_SCREEN_X 600
#define HELP_SCREEN_Y 305

#define CELL_SIZE 20
#define GRID_WIDTH (GAME_SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (GAME_SCREEN_HEIGHT / CELL_SIZE)
#define GRID_AREA (GRID_WIDTH * GRID_HEIGHT)

#define SQ_BLOCK 0
#define T_BLOCK 1
#define J_BLOCK 2
#define L_BLOCK 3
#define S_BLOCK 4
#define Z_BLOCK 5
#define I_BLOCK 6

typedef struct {
	int x;
	int y;
	int filled;
	int center;
} Cell;

typedef struct {
	Cell cell1;
	Cell cell2;
	Cell cell3;
	Cell cell4;
	int orientation;
	int type;
} Tetromino;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} App;

#endif
