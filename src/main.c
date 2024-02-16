#include "blocks.h"
#include "game.h"
#include "structs.h"
#include "init.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>

int main(int argc, char *argv[]) {

	int score = 0;
	App app;
	Cell grid[GRID_AREA];
	Tetromino currblock;

	Tetromino tetromino = {
		(Cell){10,0,1,1},
		(Cell){11,0,1,1},
		(Cell){10,1,1,1},
		(Cell){11,1,1,1},
		0, SQ_BLOCK
	};

	currblock = tetromino;

	// zero out the cells
	for (int i=0; i<GRID_AREA; i++) {
		grid[i] = (Cell){0,0,0,0};
	}

	// Start the app
	if (initSdl(&app) < 0) {
		return -1;
	}

	while (1) {
		prepareBoard(&app);

		if(handleInput(&app, &currblock) == SDL_QUIT) {
			break;
		}

		// Check for lines
		score += clearLines(grid);

		// Update game state
		if (!collision(grid, currblock) && currblock.cell1.y < GRID_HEIGHT - 1 && currblock.cell1.y < GRID_HEIGHT - 1 && currblock.cell3.y < GRID_HEIGHT - 1 && currblock.cell4.y < GRID_HEIGHT - 1) {
			// If there are no collisions and the tetromino is not at the bottom
			currblock.cell1.y++;
			currblock.cell2.y++;
			currblock.cell3.y++;
			currblock.cell4.y++;
		} else {
			// Else, push the tetromino to the grid and make a new one
			pushTetromino(grid, &currblock);
			makeNewTetromino(&currblock);
		}

		// Render the current tetromino
		renderBlock(&app, &currblock);
		renderGrid(&app, grid);
		renderGame(&app);
		SDL_Delay(100);
	}
	
	closeSdl(&app);
	return 0;
}
