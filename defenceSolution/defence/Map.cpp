#include "Map.h"
#include <vector>
#include <string>

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadImage(std::string imagename, SDL_Surface* screenSurface)	//lataa kuvan tiedostosta, optimoi sen ja lisää taulukkoon
{
	SDL_Surface* loadedImage = NULL;

	loadedImage = SDL_LoadBMP(imagename.c_str());

	if(loadedImage == NULL)
	{
		printf("Kuvaa ei ladattu");
	}
	else
	{
		terrainTiles = SDL_ConvertSurface(loadedImage, screenSurface->format, NULL);
		SDL_FreeSurface(loadedImage);
		printf("Kuva ladattu");
	}
}