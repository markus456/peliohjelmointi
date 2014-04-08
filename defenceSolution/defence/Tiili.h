#pragma once
#include "sprite.h"
#include "SDL.h"

const int TILE_WATER_NW = 0;
const int TILE_WATER_N = 1;
const int TILE_WATER_NE = 2;
const int TILE_WATER_SW = 11;
const int TILE_WATER_S = 12;
const int TILE_WATER_SE = 13;
const int TILE_WATER = 1;
const int TILE_ROAD = 2;
const int TILE_TREE = 3;

class Tiili :
	public Sprite
{
private:
	bool isPassable;	//voiko t‰st‰ menn‰ vihulaiset ja/tai hero
	bool isBuildable;	//voiko tornin rakentaa t‰h‰n
	int tileType;
	//int type;
	SDL_Rect source;	//mik‰ osa sprite sheetist‰ piirret‰‰n
	
public:
	Tiili(void);
	virtual ~Tiili(void);
	void draw(SDL_Renderer* rndr);
	void draw(SDL_Renderer* rndr, SDL_Texture* texture);
	void update();
	void setType(int type);
	void setSourceRect(int w, int h, int x, int y);
	int getType();
};

