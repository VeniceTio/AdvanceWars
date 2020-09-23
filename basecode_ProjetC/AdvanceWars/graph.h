#pragma once

#ifdef _GRAPH_C_
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
LIB_API

#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable : 4996)

#define INFINITY_DIST		0xFFFF



typedef struct sDijkstraNode dijkstraNode;
typedef struct sGraph graph;
typedef struct sNode node;

enum eGroundMask
{
	NOTHING		= 0b00000000,

	GRASS		= 0b00000001,
	FOREST		= 0b00000010,
	MOUNTAIN	= 0b00000100,
	CITY		= 0b00001000,
	ROAD		= 0b00010000,
	WATER		= 0b00100000,

	EVERYTHING	= 0b11111111
};

enum eGroundID
{
	GRASS_ID,
	FOREST_ID,
	MOUNTAIN_ID,
	CITY_ID,
	ROAD_ID,
	WATER_ID,
	NB_GROUND
};

static const char s_groundChar[NB_GROUND] = {
	'G',
	'F',
	'M',
	'C',
	'R',
	'W'
};

struct sGraph
{
	// TODO
	unsigned char m_sizeX;
	unsigned char m_sizeY;
	node** m_data;
};

struct sNode
{
	// TODO
	int m_id;
	unsigned char m_posX;
	unsigned char m_posY;
	char m_layer;
	int m_layerID;
	node* m_neighbors[4];
	void* m_data;
};

struct sDijkstraNode
{
	// TODO
	node* m_node;
	int m_distance;
	char m_flag;
	dijkstraNode* m_prev;
};

// TODO
LIB_API graph* LoadGraphFromFile(char* file);

LIB_API void freeGraph(graph* graphe);
LIB_API int GetLayerIDFromChar(char terrain);
LIB_API dijkstraNode** Dijkstra(graph* graphe, node* noeud, unsigned char terrain);

LIB_API node* GetNodeFromPosition(graph* graphe, unsigned char x, unsigned char y);
LIB_API int GetManhattanDistance(node* start, node* end);
LIB_API char IsNeighbour(node* a, node* b);

LIB_API void SetNodeData(node* noeud, void* data);
LIB_API void* GetNodeData(node* noeud);

LIB_API void FreeDijkstra(dijkstraNode** p_node, int p_size);
