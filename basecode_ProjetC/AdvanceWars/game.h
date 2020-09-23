#pragma once

#include "graph_SDL.h"
#include "unit.h"
#include "graph.h"

typedef struct sGame game;
typedef struct sPlayer player;

struct sGame
{
	sprite*			m_groundSpritesTab[NB_GROUND];
	unitType*		m_unitTab[NB_UNIT_TYPE];

	player*			m_players[2];
	int				m_playerTurn;

	graph*			m_graph;

	SDL_Surface*	m_surfaceWalk;

	TTF_Font *		m_font;
	TTF_Font *		m_fontHP;
	SDL_Surface *	m_textP1;
	SDL_Surface *	m_textP2;

	int				m_mousePosX;
	int				m_mousePosY;
	unsigned char	m_lclic;
	unsigned char	m_rclic;
};

struct sPlayer
{
	int			m_nbUnit;
	unit**		m_units;
};

game* InitGame();
int LoadSprites(game* p_game, const char* p_path);
int LoadUnitType(game * p_game, const char* p_path);
int LoadPlayer(game* p_game, int p_idPLayer, const char* p_path);

void DrawGame(SDL_Surface* p_window, game* p_game);
unit* GetSelectedUnit(game* p_game);
unit* GetUnitFromPos(game* p_game, int p_posX, int p_posY, int *p_playerID);


void CalculateMovement(graph* p_graph, unit* p_unit);
void ResetPlayers(game* p_game);

void Atttack(game* p_game, unit* p_attacker, unit* p_defender);