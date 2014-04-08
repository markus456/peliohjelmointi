#pragma once
#include "sprite.h"
#include "SDL.h"

class Road :
	public Sprite
{
private:
	SDL_Rect source;	//mik‰ osa sprite sheetist‰ piirret‰‰n
	
public:
	Road(void);
	virtual ~Road(void);
	void draw(SDL_Renderer* rndr);
	void draw(SDL_Renderer* rndr, SDL_Texture* texture);
	int tileType;
	void update();
	void setSourceRect(int w, int h, int x, int y);
	void setType(int type);
	int getType();
};