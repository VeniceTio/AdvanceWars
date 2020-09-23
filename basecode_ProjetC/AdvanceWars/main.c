#include <stdio.h>

#include "renderLoop.h"

int main(int argc, char** argv)
{
	SDL_Surface* window = NULL;
	SDL_Event e;
	game* g;

	window = init("basecode", 1216, 768);
	if (!window)
		return EXIT_FAILURE;

	g = InitGame();

	while (!interaction(&e, g))
	{
		update(g);

		draw(window, g);
	}

	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
