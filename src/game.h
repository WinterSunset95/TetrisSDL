#ifndef GAME_H
#define GAME_H

#include "structs.h"

int prepareBoard(App *app);
int handleInput(App *app, Tetromino *currblock);
int renderBlock(App *app, Tetromino *currblock);
int renderGrid(App *app, Cell grid[]);
int pushTetromino(Cell grid[], Tetromino *currblock);
int makeNewTetromino(Tetromino *currblock, int *nextTetromino);
int rotateTetromino(Tetromino *currblock);
int collision(Cell grid[], Tetromino currblock);
int clearLines(Cell grid[]);

#endif
