#ifndef TOWER_H
#define TOWER_H

#include "SDL.h"
#include "Bullet.h"
#include "sprite.h"

class Tower : public Sprite {
private:
	Bullet* loadedProjectile;
	
public:
	Tower(void);
	Tower(int tX, int tY);
	~Tower(void);
	void loadProjectile(SDL_Point target, double speed, Bullet* projectile);
	void shoot();
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();

};

#endif