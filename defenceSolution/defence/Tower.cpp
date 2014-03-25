#include "Tower.h"

Tower::Tower(void) {
	_location.x = 0;
	_location.y = 0;
	//loadedProjectile = 0;
}

Tower::Tower(int tX, int tY){
	_location.x = tX;
	_location.y = tY;
	//loadedProjectile = 0;
}

Tower::~Tower(){
}

/*
//Bullet parametrinä tulisi projectilen type
Tower::Tower(int tX, int tY, Bullet* proj){
	projectile = proj;
	_location.x = tX;
	_location.y = tY;
}
*/


// point = piste mihin ammutaan.
// speed = ammuksen nopeus.
// projectile = pointteri ammuttavaan ammukseen.
// toteusta muutettava myöhemmin.
void Tower::loadProjectile(SDL_Point target, double speed, Bullet* projectile){
	bool isFinished = false;
	SDL_Point tempPoint = {(getLocation().x+(getLocation().x+getLocation().w))/2,(getLocation().y+(getLocation().y+getLocation().h))/2};
	projectile->dirTo(target, speed);
	projectile->setLocation(tempPoint);
	loadedProjectile = projectile;
}

void Tower::shoot(){
	loadedProjectile->setSpeed(5);
}

void Tower::draw(SDL_Renderer* rndr){
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location, 0, &p, SDL_FLIP_NONE);
}
void Tower::update(){
}