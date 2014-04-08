#include "Road.h"


Road::Road(void)
{
}


Road::~Road(void)
{
}

void Road::draw(SDL_Renderer* rndr)
{
	SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
}

void Road::draw(SDL_Renderer* rndr, SDL_Texture* texture)
{
	SDL_RenderCopyEx(rndr, texture, &source, &_location.toSDL_Rect(), 0, NULL, SDL_FLIP_NONE);
}

void Road::update()
{

}

void Road::setSourceRect(int w, int h, int x, int y)
{
	source.w = w;
	source.h = h;
	source.x = x;
	source.y = y;
}

void Road::setType(int type)
{
	tileType = type;
}

int Road::getType()
{
	return tileType;
}