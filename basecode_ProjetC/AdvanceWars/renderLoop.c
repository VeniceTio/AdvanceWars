#include "renderLoop.h"
//#include "../GraphLib/include/graph.h"
#include "unit.h"

SDL_Surface* init(char* p_windowName, int p_resX, int p_resY)
{
	SDL_Surface* window;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("[-] ERROR - %s\n", SDL_GetError());
		return NULL;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("[-] ERROR - Failed to initialise SDL_Image (%s)\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	if (TTF_Init() == -1)
	{
		printf("[-] ERROR - Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		SDL_Quit();
		return NULL;
	}

	window = SDL_SetVideoMode(p_resX, p_resY, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if (!window)
	{
		printf("[-] ERROR - %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	SDL_WM_SetCaption(p_windowName, NULL);

	return window;
}

int interaction(SDL_Event* p_e, game* p_game)
{
	int quit = 0;

	SDL_GetMouseState(&p_game->m_mousePosX, &p_game->m_mousePosY);
	p_game->m_lclic = 0;
	p_game->m_rclic = 0;

	while (SDL_PollEvent(p_e))
	{
		switch (p_e->type)
		{
			// Appuie sur la croix rouge de la fenêtre
		case SDL_QUIT:
			quit = 1;
			break;

			// Appuie sur une touche du clavier
		case SDL_KEYDOWN:
			switch (p_e->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = 1;
				break;

			case SDLK_SPACE:
				p_game->m_playerTurn = (p_game->m_playerTurn + 1) % 2;
				ResetPlayers(p_game);

			default:
				break;
			}
			break;

			// Relachement d'une touche du clavier
		case SDL_KEYUP:
			switch (p_e->key.keysym.sym)
			{
			default:
				break;
			}
			break;

			// Appuie sur un bouton de la souris
		case SDL_MOUSEBUTTONDOWN:
			switch (p_e->button.button)
			{
			case SDL_BUTTON_LEFT:
				p_game->m_lclic = 1;
				break;

			case SDL_BUTTON_RIGHT:
				p_game->m_rclic = 1;
				break;

			case SDL_BUTTON_MIDDLE:
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	return quit;
}

int update(game* p_game)
{
	if (p_game->m_lclic)
	{
		// TODO :	Action(s) suite à un clic gauche
		int playerId = -1;
		//printf("clique : %d %d \n", p_game->m_mousePosX/64, p_game->m_mousePosY/64);
		unit* us = GetSelectedUnit(p_game);
		unit* u = GetUnitFromPos(p_game, p_game->m_mousePosX / 64, p_game->m_mousePosY / 64, &playerId);
		if (u != NULL) {
			if (us != NULL) {
				us->m_selected = 0;
			}
			if (playerId == p_game->m_playerTurn) {
				u->m_selected = 1;
			}
			//printf(" click droit : SelectedUnit %d playerId %d \n", u->m_type->m_type, playerId);
		}
		else {
			if (us != NULL) {
				us->m_selected = 0;
				//printf(" click droit : UnSelectedUnit %d \n", u->m_type->m_type);
			}
		}

	}

	if (p_game->m_rclic)
	{
		// TODO :	Action(s) suite à un clic droit
		int caseX, caseY, caseGlobal;
		caseX = (p_game->m_mousePosX/64) % p_game->m_graph->m_sizeX;
		caseY =  (p_game->m_mousePosY/64);
		caseGlobal = caseX + (caseY * p_game->m_graph->m_sizeX);
		//printf("X : %d | Y: %d | Global : %d\n", caseX, caseY, caseGlobal);

		unit* u = GetSelectedUnit(p_game);
		if (u != NULL)
			if (p_game->m_rclic == 1 && u->m_walkGraph[caseGlobal]->m_distance <= u->m_pm && u->m_walkGraph[caseGlobal]->m_distance >= 0)
			{
				u->m_posX = caseX;
				u->m_posY = caseY;
			}
	}

	return 0;
}

int draw(SDL_Surface* p_window, game* p_game)
{
	SDL_FillRect(p_window, NULL, SDL_MapRGBA(p_window->format, 0, 0, 0, 0));

	DrawGame(p_window, p_game);

	SDL_Flip(p_window);

	return 0;
}
