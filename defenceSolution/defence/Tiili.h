#pragma once
#include "sprite.h"
#include "SDL.h"

const int TILE_WATER_NW = 11;
const int TILE_WATER_SW = 12;
const int TILE_WATER_S = 13;
const int TILE_WATER_SE = 14;
const int TILE_WATER_N = 15;
const int TILE_WATER_NE = 16;
const int TILE_WATER = 10;
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
	bool buildable();
	bool passable();
};

