<<<<<<< HEAD
#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"

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
=======
#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"

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
>>>>>>> origin/Mappi2
#endif