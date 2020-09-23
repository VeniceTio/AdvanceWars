#pragma once

//#include "../GraphLib/include/graph.h"
#include "sprite.h"
#include "graph.h"

typedef struct sNodeSDL nodeSDL;

struct sNodeSDL
{
	sprite* m_sprite;
};

nodeSDL* CreateNodeSDL(sprite * p_sprite);
void SetNodeSDL(node* p_node, nodeSDL* p_nodeSDL);
nodeSDL* GetNodeSDL(node* p_node);
