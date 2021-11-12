#include "sprite.hpp"
#include <stdio.h>

Sprite::Sprite(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surf = IMG_Load(path);
    if (!surf)
    {
		printf("error: %s\n", IMG_GetError());
        this->_texture = nullptr;
        return;
    }
    this->_texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
}

void Sprite::draw(SDL_Renderer* renderer, const int x, const int y, const int width, const int height, const int angle) const
{
	if (!this->_texture)
	{
		return;
	}
    SDL_Rect rect = 
    {
        x,
        y,
        width,
        height
    };
    SDL_RenderCopyEx(renderer, this->_texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

Sprite::~Sprite()
{
	if (this->_texture)
	{
		free(this->_texture);
	}
    delete this;
}