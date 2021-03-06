#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "Sprite.h"
#include <deque>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);
	void attack();
	void teePolku(int pathnumber);
	bool isEmpty();
	void setSpeed(int);
	int getSpeed();
	void setAttack(int);
	int getAttack();
	void setHP(int);
	int getHP();
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
	void setPath(std::deque<Location>& roadmap);
private:
	int HP, ATK, speed,n,m;
	double angle;
	Location tmp;
	std::deque<Location> polku;
	
};

