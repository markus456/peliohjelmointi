#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"

#include "Sprite.h"

class Bullet : public Sprite {
private:
	double dir, speed;
public:
	Bullet(void);
	~Bullet(void);
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
	void setDirection(double direction, double speed);
	void dirTo(SDL_Point point, double speed);
	void setStartLocation(SDL_Point point);
	void setSpeed(double speed);
};
#endif