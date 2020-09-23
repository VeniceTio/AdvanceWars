#pragma once

#include "utils_SDL.h"

typedef struct sSprite
{
	SDL_Surface*	m_image;
	SDL_Rect		m_srcRect;
	SDL_Rect		m_destRect;
}sprite;

sprite* LoadSprite(char* p_spritePath, SDL_Rect p_src, SDL_Rect p_dest);
sprite* LoadSpriteWithImage(char* p_spritePath, SDL_Surface * p_image, SDL_Rect p_src, SDL_Rect p_dest);
sprite* CopySprite(sprite* p_sprite);
void FreeSprite(sprite* p_sprite);
void DrawSprite(SDL_Surface* p_window, sprite* p_sprite);
void MoveSprite(sprite* p_sprite, unsigned int p_newPosX, unsigned int p_newPosY);
