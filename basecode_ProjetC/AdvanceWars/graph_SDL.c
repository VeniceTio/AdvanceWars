#include "graph_SDL.h"

nodeSDL* CreateNodeSDL(sprite* p_sprite)
{
	nodeSDL* result = NULL;

	result = (nodeSDL*)calloc(1, sizeof(nodeSDL));
	if (!result)
		return NULL;

	result->m_sprite = p_sprite;

	return result;
}

void SetNodeSDL(node* p_node, nodeSDL* p_nodeSDL)
{
	SetNodeData(p_node, p_nodeSDL);
}

nodeSDL* GetNodeSDL(node* p_node)
{
	return (nodeSDL*)GetNodeData(p_node);
}
