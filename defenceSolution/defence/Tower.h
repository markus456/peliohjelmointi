#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include <memory>
#include <Math.h>
#include <algorithm>
#include "SDL.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Sprite.h"

class Tower : public Sprite {
private:
	std::shared_ptr<Bullet> loadedProjectile;
	double towerRange;
	double towerProjectileSpeed;
	bool readyToShoot;
	int cooldown;
	int cost;
	std::vector<std::shared_ptr<Enemy>> enemies;
public:
	Tower(void);
	Tower(int locationX, int locationY, int towerRange, int projSpeed, int cost);
	~Tower(void);
	void addEnemies(std::vector<std::shared_ptr<Enemy>>);
	void loadProjectile(std::shared_ptr<Bullet> projectile);
	void shoot(Location target, double speed);
	void placeAt(Location location);
	void setTowerRange(double range);
	void setTowerProjSpeed(double towerProjSpeed);
	//void scanAndShoot(std::vector<std::shared_ptr<Enemy>> spriteList);
	bool needsBullet();
	double getTargetDistance(Location enemyLocation);
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
};

#endif