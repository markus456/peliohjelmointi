#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include <memory>
#include <Math.h>
#include "SDL.h"
#include "Bullet.h"
#include "Sprite.h"

class Tower : public Sprite {
private:
	Bullet* loadedProjectile;
	double towerRange;
	double towerProjectileSpeed;
public:
	Tower(void);
	Tower(int locationX, int locationY, int towerRange, int projSpeed);
	~Tower(void);
	void loadProjectile(SDL_Point target, double speed, Bullet* projectile);
	void shoot();
	void placeAt(SDL_Point location);
	void setTowerRange(double range);
	void setTowerProjSpeed(double towerProjSpeed);
	void scanAndShoot(std::vector<std::shared_ptr<Sprite>> spriteList, Bullet* projectile);
	double getTargetDistance(SDL_Rect enemyLocation);
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
};

#endif