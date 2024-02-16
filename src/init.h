#ifndef INIT_H
#define INIT_H

#include "structs.h"
int initSdl(App *app);
int closeSdl(App *app);
int renderGame(App *app);
int addXpmToRenderList(App *app, char *xpm[], int x, int y, int w, int h);

#endif
