#include "Tile.h"
/*
Tile::Tile(SDL_Surface& image1)
{
	image = image1;
}
*/
Tile::~Tile()
{

}

void Tile::draw(int x, int y, SDL_Surface* dest)
{
	SDL_Rect DestR;
	DestR.x = x;
	DestR.y = y;

	//SDL_BlitSurface(&image, NULL, dest, &DestR);
}