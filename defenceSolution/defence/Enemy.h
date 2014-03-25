#pragma once

#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);
	void attack();
	void teePolku();
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
private:
	int HP, ATK, speed,n,m;
	double angle;
	SDL_Point tmp;
	std::deque<SDL_Point> polku;
};

