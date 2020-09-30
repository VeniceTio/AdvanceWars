#include "game.h"
#define TAILLE_MAX 10000

int LoadSprites(game* p_game, const char* p_path)
{
	char pathSprite[255];
	SDL_Rect src, dest;
	FILE* file;

	fopen_s(&file, p_path, "r");
	if (!file)
		return 0;

	dest.x = dest.y = 0;
	dest.w = dest.h = 64;

	//////////
	//	GROUND LOADING
	/////////////////////

	fscanf_s(file, "%s\n", pathSprite, 255);
	fscanf_s(file, "%hd %hd\n", &src.w, &src.h);

	for (size_t i = 0; i < NB_GROUND; i++)
	{
		char c;
		fscanf_s(file, "%c %hd %hd\n", &c, 1, &src.x, &src.y);

		if (i == 0)
			p_game->m_groundSpritesTab[GetLayerIDFromChar(c)] = LoadSprite(pathSprite, src, dest);
		else
			p_game->m_groundSpritesTab[GetLayerIDFromChar(c)] = LoadSpriteWithImage(pathSprite, p_game->m_groundSpritesTab[0]->m_image, src, dest);
	}

	fclose(file);

	return 1;
}

int LoadUnitType(game* p_game, const char* p_path)
{
	// TODO :	Chargement des types d'unit�s
	
	FILE* file;
	
	SDL_Rect src, src2, dest, dest2;
	char pathSprite[255];

	fopen_s(&file, p_path, "r");
	if (!file)
	{
		printf("ERREUR LOADUNIT\n");
		return -1;
	}
		
	
	for (int i = 0; i < NB_UNIT_TYPE; i++)
	{
		p_game->m_unitTab[i] = (unitType*)calloc(1,sizeof(unitType));
		if (!p_game->m_unitTab[i])
			return -1;
	}

	dest.x = dest.y = 0;
	dest.w = dest.h = 64;

	dest2.x = 0;
	dest2.y = 64;
	dest2.w = dest2.h = 64;

	fscanf_s(file, "%s\n", pathSprite, 255); //chemin Sprite
	fscanf_s(file, "%hd %hd\n", &src.w, &src.h); //largeur et hauteur Sprite

	for (int i = 0; i < NB_UNIT_TYPE; i++)
	{
		char c;
		fscanf_s(file, "%c %hd %hd %d %d\n", &c, 1, &src.x, &src.y, &p_game->m_unitTab[i]->m_layerMask, &p_game->m_unitTab[i]->m_pmMax);
		//printf("I=%d | PM = %d\n", i, p_game->m_unitTab[0]->m_pmMax);
		p_game->m_unitTab[i]->m_type = i;

		src2.w = src.w;
		src2.h = src.h;
		src2.x = src.x;
		src2.y = src.y + 64;
		if (i == 0)
		{
			p_game->m_unitTab[i]->m_sprite[0] = LoadSprite(pathSprite, src, dest);
			p_game->m_unitTab[i]->m_sprite[1] = LoadSprite(pathSprite, src2, dest2);
		}
		else
		{
			p_game->m_unitTab[i]->m_sprite[0] = LoadSpriteWithImage(pathSprite, p_game->m_unitTab[0]->m_sprite[0]->m_image, src, dest);
			p_game->m_unitTab[i]->m_sprite[1] = LoadSpriteWithImage(pathSprite, p_game->m_unitTab[0]->m_sprite[1]->m_image, src2, dest2);
		}
	}
	fclose(file);
	return 1;
}

int LoadPlayer(game* p_game, int p_idPLayer, const char* p_path)
{
	// TODO :	Chargement des joueurs
	FILE* fileLoadPlayer = NULL;
	fopen_s(&fileLoadPlayer,p_path, "r");

	if (!fileLoadPlayer)
	{
		printf("ERREUR LOADPLAYER");
		return -1;
	}
	player* joueur;
	joueur = (player*)malloc(sizeof(player));
	p_game->m_players[p_idPLayer] = joueur;
	if (!p_game->m_players[p_idPLayer])
		return -1;

	int nbUnit = 0;
	fscanf_s(fileLoadPlayer, "%d\n", &nbUnit); //nombre d'unit�s
	p_game->m_players[p_idPLayer]->m_nbUnit = nbUnit;
	printf("NbUnit : %d\n", nbUnit);

	if (!fileLoadPlayer)
	{
		printf("ERREUR");
		return -1;
	}
		
	p_game->m_players[p_idPLayer]->m_units = (unit**)calloc(nbUnit, sizeof(unit*));
	for (int i = 0; i < nbUnit; i++)
	{
		p_game->m_players[p_idPLayer]->m_units[i] = (unit*)calloc(1,sizeof(unit));
		if (!p_game->m_players[p_idPLayer]->m_units[i])
			return -1;
	}

	int typeUnit;
	int posX, posY;
	for (int i = 0; i < nbUnit; i++)
	{
		fscanf_s(fileLoadPlayer, "%d %d %d\n", &typeUnit, &posX, &posY); //TypeUnit� / posX / posY
		p_game->m_players[p_idPLayer]->m_units[i]->m_type = p_game->m_unitTab[typeUnit];
		p_game->m_players[p_idPLayer]->m_units[i]->m_posX = posX;
		p_game->m_players[p_idPLayer]->m_units[i]->m_posY = posY;
		printf("P[%d] : I=%d | POSX = %d | POSY = %d\n", p_idPLayer, i, p_game->m_players[p_idPLayer]->m_units[i]->m_posX, p_game->m_players[p_idPLayer]->m_units[i]->m_posY);
	}

	fclose(fileLoadPlayer);
	return 1;
}

game* InitGame()
{
	game* result = NULL;
	int i;

	result = (game*)calloc(1, sizeof(game));
	if (!result)
		return NULL;

	result->m_font = TTF_OpenFont("./data/fonts/font_1.ttf", 65);
	result->m_fontHP = TTF_OpenFont("./data/fonts/font_1.ttf", 20);
	result->m_textP1 = TTF_RenderText_Blended(result->m_font, "Joueur 1", (SDL_Color){ 0, 0, 0 });
	result->m_textP2 = TTF_RenderText_Blended(result->m_font, "Joueur 2", (SDL_Color){ 0, 0, 0 });

	LoadSprites(result, "./data/sprites.ini");
	LoadUnitType(result, "./data/unitType.ini");

	result->m_graph = LoadGraphFromFile("./data/1_map.ini");
	if (!result->m_graph)
		return NULL;

	for (i = 0; i < result->m_graph->m_sizeX * result->m_graph->m_sizeY; i++)
	{
		sprite* s = CopySprite(result->m_groundSpritesTab[result->m_graph->m_data[i]->m_layerID]);
		MoveSprite(s, result->m_graph->m_data[i]->m_posX * 64, result->m_graph->m_data[i]->m_posY * 64);
		SetNodeSDL(result->m_graph->m_data[i], CreateNodeSDL(s));
	}

	LoadPlayer(result, 0, "./data/1_player1.ini");
	LoadPlayer(result, 1, "./data/1_player2.ini");

	result->m_surfaceWalk = SDL_LoadBMP("./data/walkLayer.bmp");
	SDL_SetAlpha(result->m_surfaceWalk, SDL_SRCALPHA, 128);

	result->m_playerTurn = 0;

	return result;
}

void DrawGame(SDL_Surface* p_window, game* p_game)
{
	int i, j, k, l;
	int index = 0;

	// Affichage du niveau
	for (i = 0; i < p_game->m_graph->m_sizeY; i++)
	{
		for (j = 0; j < p_game->m_graph->m_sizeX; j++)
		{
			nodeSDL* n = GetNodeSDL(p_game->m_graph->m_data[index]);
			DrawSprite(p_window, n->m_sprite);
			index++;
		}
	}

	// TODO :	Affichage des cases semi-transparentes pour indiquer la possibilit� de marcher
	unit* u = GetSelectedUnit(p_game);
	if (u != NULL) {
		CalculateMovement(p_game->m_graph, u);
		int size = p_game->m_graph->m_sizeX * p_game->m_graph->m_sizeY;
		graph* g = p_game;
		for (size_t i = 0; i < size; i++) {
			if (u->m_walkGraph[i]->m_distance <= u->m_pm) {
				//mettre cette case i en transparent
			}
		}
	}
	
	// TODO :	Affichage des unit�s
	//DrawSprite(p_window, p_game->m_players[1]->m_units[1]->m_type->m_sprite[1]);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < p_game->m_players[i]->m_nbUnit; j++)
		{
			MoveSprite(p_game->m_players[i]->m_units[j]->m_type->m_sprite[i], (p_game->m_players[i]->m_units[j]->m_posX)*64, (p_game->m_players[i]->m_units[j]->m_posY)*64);
			DrawSprite(p_window, p_game->m_players[i]->m_units[j]->m_type->m_sprite[i]);
		}
	}
	

	// Affichage du texte
	if(p_game->m_playerTurn == 0)
		SDL_BlitSurface(p_game->m_textP1, NULL, p_window, NULL);
	else
	{
		SDL_Rect dest;
		dest.x = p_window->w - p_game->m_textP2->w;
		dest.y = 0;

		SDL_BlitSurface(p_game->m_textP2, NULL, p_window, &dest);
	}
}

unit* GetSelectedUnit(game* p_game)
{
	int index, j;
	index = p_game->m_playerTurn;

	for (size_t j = 0; j < p_game->m_players[index]->m_nbUnit; j++)
	{
		if (p_game->m_players[index]->m_units[j]->m_selected)
			return p_game->m_players[index]->m_units[j];
	}

	return NULL;
}

unit* GetUnitFromPos(game* p_game, int p_posX, int p_posY, int* p_playerID)
{
	// TODO :	Fonction retournant le pointeur vers l'unit� � la position pass�e en param�tre
	//			p_playerID est une variable retourn�e s'il existe une unit� � la position demand�e
	unit* u = NULL;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < p_game->m_players[i]->m_nbUnit; j++)
		{
			if (p_game->m_players[i]->m_units[j]->m_posX == p_posX && p_game->m_players[i]->m_units[j]->m_posY == p_posY) {
				u = p_game->m_players[i]->m_units[j];
				p_playerID = i;
			}
		}
	}
	return u;
}

void CalculateMovement(graph* p_graph, unit* p_unit)
{
	p_unit->m_walkGraph = Dijkstra(p_graph, GetNodeFromPosition(p_graph, p_unit->m_posX, p_unit->m_posY), p_unit->m_type->m_layerMask);
}

void ResetPlayers(game* p_game)
{
	// TODO :	Initialises les variables des unit� en d�but de tour

}

void Atttack(game* p_game, unit* p_attacker, unit* p_defender)
{
	// TODO :	Calculer les d�gats des l'attaquand sur le d�fenseur
}
