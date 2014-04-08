#include "Tiili.h"


Tiili::Tiili(void)
{
}


Tiili::~Tiili(void)
{
}

void Tiili::draw(SDL_Renderer* rndr)
{
	SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
}

void Tiili::draw(SDL_Renderer* rndr, SDL_Texture* texture)
{
	SDL_RenderCopyEx(rndr, texture, &source, &_location.toSDL_Rect(), 0, NULL, SDL_FLIP_NONE);
}

void Tiili::update()
{

}

void Tiili::setType(int type)
{
	tileType = type;
}

void Tiili::setSourceRect(int w, int h, int x, int y)
{
	source.w = w;
	source.h = h;
	source.x = x;
	source.y = y;
}

int Tiili::getType()
{
	return tileType;
}