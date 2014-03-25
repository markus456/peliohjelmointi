#pragma once
#include "sprite.h"
#include "SDL.h"

class Tiili :
	public Sprite
{
private:
	bool isPassable;	//voiko t‰st‰ menn‰ vihulaiset ja/tai hero
	bool isBuildable;	//voiko tornin rakentaa t‰h‰n
	int tileType;
	//int type;
	Location source;	//mik‰ osa sprite sheetist‰ piirret‰‰n
	
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

