#pragma once

#include "game.h"

enum ePosition
{
	DOWN,
	LEFT,
	UP,
	RIGHT,
	NB_POSITION
};

SDL_Surface* init(char* p_windowName, int p_resX, int p_resY);
int interaction(SDL_Event* p_e, game* p_game);
int update(game* p_game);
int draw(SDL_Surface* p_window, game* p_game);
