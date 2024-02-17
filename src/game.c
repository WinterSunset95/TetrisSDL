#include "game.h"
#include "structs.h"
#include "init.h"
#include "assets/Game.xpm"
#include "assets/Small.xpm"
#include "assets/red.xpm"
#include "assets/blue.xpm"
#include "assets/green.xpm"
#include "assets/yellow.xpm"
#include "assets/cyan.xpm"
#include "assets/pink.xpm"

#ifdef _WIN32
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_log.h>
#else
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_log.h>
#endif

// Lets define some tetrominos here
Tetromino sqBlock = {
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2+1,0,1,0},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2+1,1,1,0},
	0,
	SQ_BLOCK
};

Tetromino tBlock = {
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2-1,1,1,0},
	{GRID_WIDTH/2+1,1,1,0},
	0,
	T_BLOCK
};

Tetromino jBlock={
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2,2,1,0},
	{GRID_WIDTH/2-1,2,1,0},
	0,
	J_BLOCK
};

Tetromino lBlock={
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2,2,1,0},
	{GRID_WIDTH/2+1,2,1,0},
	0,
	L_BLOCK
};

Tetromino sBlock={
	{GRID_WIDTH/2+1,0,1,0},
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2-1,1,1,0},
	0,
	S_BLOCK
};

Tetromino zBlock={
	{GRID_WIDTH/2-1,0,1,0},
	{GRID_WIDTH/2,0,1,1},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2+1,1,1,0},
	0,
	Z_BLOCK
};

Tetromino iBlock={
	{GRID_WIDTH/2,3,1,0},
	{GRID_WIDTH/2,2,1,0},
	{GRID_WIDTH/2,1,1,0},
	{GRID_WIDTH/2,0,1,1},
	0,
	I_BLOCK
};

Tetromino *tetrominos[] = {&sqBlock, &tBlock, &jBlock, &lBlock, &sBlock, &zBlock, &iBlock};


int prepareBoard(App *app) {
	// Push the backgrounds to the render list
	addXpmToRenderList(app, Game_xpm, LEFT_DIV_X, LEFT_DIV_Y, LEFT_DIV_WIDTH, LEFT_DIV_HEIGHT);
	addXpmToRenderList(app, Small_xpm, TOP_RIGHT_DIV_X, TOP_RIGHT_DIV_Y, TOP_RIGHT_DIV_WIDTH, TOP_RIGHT_DIV_HEIGHT);
	addXpmToRenderList(app, Small_xpm, BOTTOM_RIGHT_DIV_X, BOTTOM_RIGHT_DIV_Y, BOTTOM_RIGHT_DIV_WIDTH, BOTTOM_RIGHT_DIV_HEIGHT);
	return 0;
}

int handleInput(App *app, Tetromino *currblock) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return SDL_QUIT;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if (currblock->cell1.x > 0 && currblock->cell2.x > 0 && currblock->cell3.x > 0 && currblock->cell4.x > 0) {
						currblock->cell1.x--;
						currblock->cell2.x--;
						currblock->cell3.x--;
						currblock->cell4.x--;
					}
					break;
				case SDLK_RIGHT:
					if (currblock->cell1.x < GRID_WIDTH - 1 && currblock->cell2.x < GRID_WIDTH - 1 && currblock->cell3.x < GRID_WIDTH - 1 && currblock->cell4.x < GRID_WIDTH - 1) {
						currblock->cell1.x++;
						currblock->cell2.x++;
						currblock->cell3.x++;
						currblock->cell4.x++;
					}
					break;
				case SDLK_DOWN:
					if (currblock->cell1.y < GRID_HEIGHT - 1 && currblock->cell2.y < GRID_HEIGHT - 1 && currblock->cell3.y < GRID_HEIGHT - 1 && currblock->cell4.y < GRID_HEIGHT - 1) {
						currblock->cell1.y++;
						currblock->cell2.y++;
						currblock->cell3.y++;
						currblock->cell4.y++;
					}
					break;
				case SDLK_UP:
					rotateTetromino(currblock);
					break;
			}
		}
	}
	return 0;
}

int renderBlock(App *app, Tetromino *currblock) {
	// Push a block to the render list
	// This function will be called with each render cycle
	int x, y;
	Cell arr[4] = {currblock->cell1, currblock->cell2, currblock->cell3, currblock->cell4};

	// First for cell1
	for (int i=0; i<4; i++) {
		x = arr[i].x * CELL_SIZE + 5;
		y = arr[i].y * CELL_SIZE + 5;
		switch (currblock->type) {
			case SQ_BLOCK:
				addXpmToRenderList(app, red_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case T_BLOCK:
				addXpmToRenderList(app, blue_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case L_BLOCK:
				addXpmToRenderList(app, green_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case J_BLOCK:
				addXpmToRenderList(app, yellow_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case S_BLOCK:
				addXpmToRenderList(app, cyan_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case Z_BLOCK:
				addXpmToRenderList(app, pink_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
			case I_BLOCK:
				addXpmToRenderList(app, red_xpm, x, y, CELL_SIZE, CELL_SIZE);
				break;
		}

	}
	return 0;
}

int makeNewTetromino(Tetromino *currblock, int *nextTetromino) {
	// Get a random number from 0 to 6
	*currblock = *tetrominos[*nextTetromino];
	int r = rand() % 7;
	*nextTetromino = r;

	return 0;
}

int pushTetromino(Cell *grid, Tetromino *currblock) {
	// Push the current block to the grid
	grid[currblock->cell1.y * GRID_WIDTH + currblock->cell1.x] = currblock->cell1;
	grid[currblock->cell2.y * GRID_WIDTH + currblock->cell2.x] = currblock->cell2;
	grid[currblock->cell3.y * GRID_WIDTH + currblock->cell3.x] = currblock->cell3;
	grid[currblock->cell4.y * GRID_WIDTH + currblock->cell4.x] = currblock->cell4;

	return 0;
}

int rotateTetromino(Tetromino *currblock) {
	Cell *arr[3] = {&currblock->cell1, &currblock->cell3, &currblock->cell4};
	Cell *cell2 = &currblock->cell2;

	if (currblock->type == SQ_BLOCK) {
		return 0;
	}

	if (currblock->type == I_BLOCK) {
		// if horizontal
		if (arr[0]->y == cell2->y) {
			arr[0]->x++;
			arr[0]->y++;
			arr[1]->x--;
			arr[1]->y--;
			arr[2]->x -= 2;
			arr[2]->y -= 2;
		} else if (arr[0]->x == cell2->x) {
			arr[0]->x--;
			arr[0]->y--;
			arr[1]->x++;
			arr[1]->y++;
			arr[2]->x += 2;
			arr[2]->y += 2;
		}
		return 0;
	}

	// The cells rotate around cell2
	// Down is +
	// Right is +
	for (int i=0; i<3; i++) {
		Cell *currCell = arr[i];
		if (currCell->x < cell2->x && currCell->y < cell2->y) {
			// top left cell, move down 2 cells
			currCell->y += 2;
		} else if (currCell->x < cell2->x && currCell->y == cell2->y) {
			// left cell, move down and right
			currCell->y++;
			currCell->x++;
		} else if (currCell->x < cell2->x && currCell->y > cell2->y) {
			// bottom left cell, move right 2 cells
			currCell->x += 2;
		} else if (currCell->x == cell2->x && currCell->y > cell2->y) {
			// bottom cell, move up and right
			currCell->y--;
			currCell->x++;
		} else if (currCell->x > cell2->x && currCell->y > cell2->y) {
			// bottom right cell, move up 2 cells
			currCell->y -= 2;
		} else if (currCell->x > cell2->x && currCell->y == cell2->y) {
			// right cell, move up and left
			currCell->y--;
			currCell->x--;
		} else if (currCell->x > cell2->x && currCell->y < cell2->y) {
			// top right cell, move left 2 cells
			currCell->x -= 2;
		} else if (currCell->x == cell2->x && currCell->y < cell2->y) {
			// top cell, move down and left
			currCell->y++;
			currCell->x--;
		}
	}
	return 0;
}

int renderGrid(App *app, Cell *grid) {
	// Push every cell from the grid to the render list
	// If and only if they are active
	for (int i=0; i<GRID_AREA; i++) {
		if (grid[i].filled) {
			int x = grid[i].x * CELL_SIZE + 5;
			int y = grid[i].y * CELL_SIZE + 5;
			addXpmToRenderList(app, red_xpm, x, y, CELL_SIZE, CELL_SIZE);
		}
	}

	return 0;
}

int collision(Cell *grid, Tetromino currblock) {
	int coll = 0;
	Cell arr[4] = {currblock.cell1, currblock.cell2, currblock.cell3, currblock.cell4};
	for (int a=0; a<4; a++) {
		Cell tetCell = arr[a];
		for (int i=0; i<GRID_AREA; i++) {
			Cell gridCell = grid[i];
			if (tetCell.x == gridCell.x && tetCell.y == gridCell.y-1) {
				coll = 1;
				break;
			}
		}
	}
	return coll;
}

int clearLines(Cell *grid) {
	// Firstly we need to check if any lines are full
	// If they are, we need to remove them and move the rest down
	// And return the number of lines cleared
	int linesCleared = 0;
	for (int y=0; y<GRID_HEIGHT; y++) {
		// Start by assuming the line is full
		int lineFull = 1;
		for (int x=0; x<GRID_WIDTH; x++) {
			if (!grid[y*GRID_WIDTH + x]. filled) {
				// If any cell is not filled, the line is not full
				lineFull = 0;
				break;
			}
		}

		if (lineFull) {
			// increment the number of lines cleared
			linesCleared++;
			// Clear the line
			for (int x=0; x<GRID_WIDTH; x++) {
				grid[y*GRID_WIDTH + x] = (Cell) {0, 0, 0, 0};
			}
			// replace every grid cell with the one above it
			// move every cell down
			for (int a=y; a>0; a--) {
				for (int b=0; b<GRID_WIDTH; b++) {
					grid[a*GRID_WIDTH + b] = grid[(a-1)*GRID_WIDTH + b];
					grid[a*GRID_WIDTH + b].y++;
				}
			}
		}
	}

	return linesCleared;
}
