#pragma once

#include "SDL.h"
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
	void teePolku();
	bool isEmpty();
	void setSpeed(int);
	int getSpeed();
	void setAttack(int);
	int getAttack();
	void setHP(int);
	int getHP();
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
private:
	int HP, ATK, speed,n,m;
	double angle;
	Location tmp;
	std::deque<Location> polku;
	float distance(float,float,float,float);
	float distance(Location,Location);
};

