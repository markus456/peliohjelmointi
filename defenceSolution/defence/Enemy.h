#pragma once

#include "SDL.h"
#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);
	void attack();
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
private:
	int HP, ATK, speed;
};

