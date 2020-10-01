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
	unit* us = GetSelectedUnit(p_game);
	int playerId = -1;
	unit* u = GetUnitFromPos(p_game, p_game->m_mousePosX / 64, p_game->m_mousePosY / 64, &playerId);
	if (p_game->m_lclic)
	{
		// TODO :	Action(s) suite à un clic gauche
		if (us == NULL) {
			//printf("clique : %d %d \n", p_game->m_mousePosX/64, p_game->m_mousePosY/64);
			if (u != NULL) {
				if (playerId == p_game->m_playerTurn) {
					u->m_selected = 1;
					CalculateMovement(p_game->m_graph, u);

				}
				//printf(" click droit : SelectedUnit %d playerId %d \n", u->m_type->m_type, playerId);
			}
		}
		else {
			int caseX, caseY, caseGlobal, distance;
			caseX = (p_game->m_mousePosX / 64) % p_game->m_graph->m_sizeX;
			caseY = (p_game->m_mousePosY / 64);
			caseGlobal = caseX + (caseY * p_game->m_graph->m_sizeX);
			//printf("X : %d | Y: %d | Global : %d\n", caseX, caseY, caseGlobal);
			if (u == NULL) {
				distance = us->m_walkGraph[caseGlobal]->m_distance;
				if (distance <= us->m_pm && us->m_walkGraph[caseGlobal]->m_distance > 0)
				{
					us->m_posX = caseX;
					us->m_posY = caseY;
					us->m_pm -= distance;
					CalculateMovement(p_game->m_graph, us);
				}
			}
			else {
				if (playerId == p_game->m_playerTurn) {
					us->m_selected = 0;
					u->m_selected = 1;
					CalculateMovement(p_game->m_graph, u);
				}
				else if (us->m_canFire) {
					distance = GetManhattanDistance(p_game->m_graph->m_data[us->m_posX + us->m_posY * p_game->m_graph->m_sizeX], p_game->m_graph->m_data[u->m_posX + u->m_posY * p_game->m_graph->m_sizeX]);
					if (us->m_type->m_type == 3) {
						if (distance < 6 && distance > 1) {
							Atttack(p_game, us, u);
							us->m_canFire = 0;
							printf("attack d'artilerie à %d de distance \n", distance);
						}
						else {
							u->m_selected = 1;
							CalculateMovement(p_game->m_graph, u);
						}
					}
					else {
						if (distance == 1) {
							Atttack(p_game, us, u);
							if (u->m_type->m_type != 3) {
								Atttack(p_game, u, us);
							}
							us->m_canFire = 0;
							printf("attack d'artilerie à %d de distance \n", distance);
						}
						else {
							u->m_selected = 1;
							CalculateMovement(p_game->m_graph, u);
						}
					}
					us->m_selected = 0;
				}
				
			}
		}
	}

	if (p_game->m_rclic)
	{
		// TODO :	Action(s) suite à un clic droit
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
