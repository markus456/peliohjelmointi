#pragma once
#include "SDL.h"
#include <vector>
#include "Tiili.h"
#include "Road.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using std::vector;

//const int TILE_COUNT = 4;
const int MAP_HEIGHT = 19;		//kartan koko tiileiss�
const int MAP_WIDTH = 25;
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;


class TileMap
{
private:
	vector <Tiili> map;				//sis�lt�� kaikki kartan tiilet
	vector <Road> roadmap;
	vector <int> typeMap;
	SDL_Texture* tileTexture;		//spritesheet
	//SDL_Rect clips[ TILE_COUNT ];	//pilkotut kuvat
	SDL_Renderer* rndr;

public:
	TileMap(void);
	virtual ~TileMap(void);
	void addTiles();
	void addRoads();
	void drawMap();
	void setTexture(std::string filename, SDL_Renderer* rndr);
	void setRenderer(SDL_Renderer* rndr);
	void setClips();
	void setMap(std::string filename);
	std::vector<Tiili>& getMap();
	std::vector<Road>& getRoad();
};
