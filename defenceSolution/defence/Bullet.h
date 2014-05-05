#ifndef BULLET_H
#define BULLET_H

#ifdef SYSTEM_LIBS
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include "Sprite.h"

class Bullet : public Sprite {
private:
	double dir, speed;
	unsigned int damage;
public:
	Bullet(void);
	~Bullet(void);
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
	void setDirection(double direction, double speed);
	void dirTo(Location point, double speed);
	void setStartLocation(Location point);
	void setSpeed(double speed);
	unsigned int getDamage();
	void setDamage(unsigned int);
};
#endif
