#pragma once

#include "graph.h"
#include "sprite.h"	

typedef struct sUnit unit;
typedef struct sUnitType unitType;

enum eUnitType
{
	SOLDIER,
	HEAVY_SOLDIER,
	TANK,
	ROCKET_LAUNCHER,
	DCA,
	COPTER,
	NB_UNIT_TYPE
};

static char s_unitChar[NB_UNIT_TYPE] = {
	'S',
	'H',
	'T',
	'R',
	'D',
	'C'
};

static int s_damageChart[6][6] = {
	{55, 45, 5, 15, 5, 7},
	{65, 55, 55, 85, 65, 9},
	{75, 70, 55, 85, 65, 10},
	{95, 90, 85, 85, 85, 0},
	{105, 105, 25, 65, 25, 120},
	{75, 75, 55, 65, 25, 65}
};

static int s_defenseGround[NB_GROUND] = {
	1,
	2,
	4,
	3,
	0,
	0
};

struct sUnit
{
	unitType *		m_type;
	dijkstraNode**	m_walkGraph;

	int				m_hp;
	int				m_pm;

	int				m_posX;
	int				m_posY;

	unsigned char	m_canFire;
	unsigned char	m_selected;
};

struct sUnitType
{
	sprite*		m_sprite[2];

	int			m_pmMax;
	int			m_layerMask;
	int			m_type;
};

int GetUnitIDFromChar(char p_unitChar);