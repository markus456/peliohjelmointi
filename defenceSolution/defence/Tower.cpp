#include "Tower.h"

Tower::Tower(void) {
	_location.x = 0;
	_location.y = 0;
	this->towerRange=0;
	this->towerProjectileSpeed=0;
	cooldown = 0;
	readyToShoot = false;
	//loadedProjectile = 0;
}

Tower::Tower(int locationX, int locationY, int towerRange, int projSpeed){
	_location.x = locationX;
	_location.y = locationY;
	cooldown = 0;
	readyToShoot = false;
	this->towerRange=towerRange;
	this->towerProjectileSpeed = projSpeed;
	//loadedProjectile = 0;
}

Tower::~Tower(){
	//delete loadedProjectile;
}

// point = piste mihin ammutaan.
// speed = ammuksen nopeus.
// projectile = pointteri ammuttavaan ammukseen.
// toteusta muutettava myöhemmin.
void Tower::loadProjectile(std::shared_ptr<Bullet> projectile){
	loadedProjectile = projectile;
	readyToShoot = true;
}

void Tower::shoot(Location target, double speed){
	//loadedProjectile->setVisible(true);
	Location tempPoint((getLocation().x+(getLocation().x+getLocation().w))/2,(getLocation().y+(getLocation().y+getLocation().h))/2);
	loadedProjectile->setLocation(tempPoint);
	loadedProjectile->dirTo(target, speed);
	loadedProjectile->setSpeed(towerProjectileSpeed);
	cooldown = 60;
	readyToShoot = false;
}

void Tower::placeAt(Location location){

}

void Tower::setTowerRange(double range){
	this->towerRange=range;
}

bool Tower::needsBullet(){
	if(!readyToShoot)return true;
	return false;
}

void Tower::setTowerProjSpeed(double towerProjSpeed){
	this->towerProjectileSpeed=towerProjSpeed;
}


//Sprite listalta skannataan lähellä ovat viholliset
//Projectilella ammutaan vihollisella
void Tower::addEnemies(std::vector<std::shared_ptr<Enemy>> spriteList){
	enemies = spriteList;
}

//laskee pythagoralla tornin ja kohteen etäisyyden
//ATM: laskee kummankin kohteen vasemmasta yläkulmasta
//TODO: laskee kummankin osapuolen toisiaan lähimmät pisteet.
double Tower::getTargetDistance(Location enemyLocation){

	int thisX = this->_location.x;
	int thisY = this->_location.y;
	double distance = abs(sqrt(pow(enemyLocation.x-thisX,2)+pow(enemyLocation.y-thisY,2))); 
	return distance;

}


void Tower::draw(SDL_Renderer* rndr){
	Location p(_location.w / 2, _location.h / 2);
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location.toSDL_Rect(), 0, &p.toSDL_Point(), SDL_FLIP_NONE);
}
void Tower::update(){
	if(cooldown>0){
		cooldown--;
	}else {
		if(readyToShoot){
			std::sort(enemies.begin(),enemies.end(),[=](const std::shared_ptr<Enemy>& a,const std::shared_ptr<Enemy>& b){
				return this->getTargetDistance(a->getLocation())<this->getTargetDistance(b->getLocation());
			});
			if(getTargetDistance(enemies.front()->getLocation())<towerRange){
				shoot(enemies.front()->getLocation(),towerProjectileSpeed);
			}
		}
	}
}