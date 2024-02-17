#include "init.h"
#include "structs.h"

#ifdef _WIN32
#include <SDL_error.h>
#include <SDL_log.h>
#include <SDL_stdinc.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_image.h>
#endif

int initSdl(App *app) {

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}

	// Create window
	app->window = SDL_CreateWindow("Tetris SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(app->window == NULL) {
		SDL_Log("Unable to create window: %s\n", SDL_GetError());
		return -1;
	}

	// Create the renderer
	app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(app->renderer == NULL) {
		SDL_Log("Unable to create renderer: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int closeSdl(App *app) {
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	return 0;
}

int renderGame(App *app) {
	SDL_RenderPresent(app->renderer);
	return 0;
}

int addXpmToRenderList(App *app, char *xpm[], int x, int y, int w, int h) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect rect = {0, 0, 0, 0};

	surface = IMG_ReadXPMFromArray(xpm);
	if (surface == NULL) {
		SDL_Log("Unable to create surface: %s\n", SDL_GetError());
		return -1;
	}

	texture = SDL_CreateTextureFromSurface(app->renderer, surface);
	if (texture == NULL) {
		SDL_Log("Unable to create texture: %s\n", SDL_GetError());
		return -1;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(app->renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	return 0;
}

