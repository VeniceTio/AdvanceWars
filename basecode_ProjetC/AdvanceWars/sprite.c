#include "sprite.h"

sprite* LoadSprite(char* p_spritePath, SDL_Rect p_src, SDL_Rect p_dest)
{
	sprite* result = NULL;

	result = (sprite*)calloc(1, sizeof(sprite));
	if (!result)
		return NULL;

	result->m_image = IMG_Load(p_spritePath);
	if (!result->m_image)
	{
		free(result);
		return NULL;
	}

	result->m_destRect = p_dest;
	result->m_srcRect = p_src;

	result->m_image = zoomSurface(result->m_image, p_dest.w / (double)p_src.w, p_dest.h / (double)p_src.h, SMOOTHING_ON);

	result->m_srcRect.w = result->m_destRect.w;
	result->m_srcRect.h = result->m_destRect.h;

	return result;
}

sprite* LoadSpriteWithImage(char* p_spritePath, SDL_Surface* p_image, SDL_Rect p_src, SDL_Rect p_dest)
{
	sprite* result = NULL;

	result = (sprite*)calloc(1, sizeof(sprite));
	if (!result)
		return NULL;

	result->m_image = p_image;

	result->m_destRect = p_dest;
	result->m_srcRect = p_src;

	result->m_srcRect.w = result->m_destRect.w;
	result->m_srcRect.h = result->m_destRect.h;

	return result;
}

sprite* CopySprite(sprite* p_sprite)
{
	sprite* result;

	if (!p_sprite)
		return NULL;

	result = (sprite*)calloc(1, sizeof(sprite));
	if (!result)
		return NULL;

	result->m_image		= p_sprite->m_image;
	result->m_srcRect	= p_sprite->m_srcRect;
	result->m_destRect	= p_sprite->m_destRect;

	return result;
}

void FreeSprite(sprite* p_sprite)
{
	if (!p_sprite)
		return;

	if (p_sprite->m_image)
		SDL_FreeSurface(p_sprite->m_image);

	free(p_sprite);
}

void DrawSprite(SDL_Surface* p_window, sprite* p_sprite)
{
	SDL_BlitSurface(p_sprite->m_image, &(p_sprite->m_srcRect), p_window, &(p_sprite->m_destRect));
}

void MoveSprite(sprite* p_sprite, unsigned int p_newPosX, unsigned int p_newPosY)
{
	p_sprite->m_destRect.x = p_newPosX;
	p_sprite->m_destRect.y = p_newPosY;
}
