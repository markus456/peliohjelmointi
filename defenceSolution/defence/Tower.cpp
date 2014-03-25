#include "Tower.h"

Tower::Tower(void) {
	_location.x = 0;
	_location.y = 0;
	this->towerRange=0;
	this->towerProjectileSpeed=0;
	//loadedProjectile = 0;
}

Tower::Tower(int locationX, int locationY, int towerRange, int projSpeed){
	_location.x = locationX;
	_location.y = locationY;
	this->towerRange=towerRange;
	this->towerProjectileSpeed = projSpeed;
	//loadedProjectile = 0;
}

Tower::~Tower(){
	delete loadedProjectile;
}

// point = piste mihin ammutaan.
// speed = ammuksen nopeus.
// projectile = pointteri ammuttavaan ammukseen.
// toteusta muutettava myöhemmin.
void Tower::loadProjectile(SDL_Point target, double speed, Bullet* projectile){
	SDL_Point tempPoint = {(getLocation().x+(getLocation().x+getLocation().w))/2,(getLocation().y+(getLocation().y+getLocation().h))/2};
	projectile->dirTo(target, speed);
	projectile->setLocation(tempPoint);
	loadedProjectile = projectile;
}

void Tower::shoot(){
	loadedProjectile->setSpeed(towerProjectileSpeed);
}

void Tower::placeAt(SDL_Point location){

}

void Tower::setTowerRange(double range){
	this->towerRange=range;
}

void Tower::setTowerProjSpeed(double towerProjSpeed){
	this->towerProjectileSpeed=towerProjSpeed;
}


//Sprite listalta skannataan lähellä ovat viholliset
//Projectilella ammutaan vihollisella
void Tower::scanAndShoot(std::vector<std::shared_ptr<Sprite>> spriteList, Bullet *projectile){
	
	for(auto& a: spriteList){

		//shared_ptr<Sprite> vaihdettava Enemy*
		if ( typeid(a) == typeid(std::shared_ptr<Sprite>) && getTargetDistance(a->getLocation()) < this->towerRange ){
			
			//targetlocation on keskelle targettia toistaiseksi
			SDL_Point targetLocation = { (a->getLocation().x+(a->getLocation().x+a->getLocation().w ))/2,
					(a->getLocation().y+(a->getLocation().y+a->getLocation().h))/2 }; 

			loadProjectile(targetLocation,towerProjectileSpeed,projectile);
			shoot();
		}
	}
}


//laskee pythagoralla tornin ja kohteen etäisyyden
//ATM: laskee kummankin kohteen vasemmasta yläkulmasta
//TODO: laskee kummankin osapuolen toisiaan lähimmät pisteet.
double Tower::getTargetDistance(SDL_Rect enemyLocation){
	
	int thisX = this->_location.x;
	int thisY = this->_location.y;
	double distance = abs(sqrt(pow(enemyLocation.x-thisX,2)+pow(enemyLocation.y-thisY,2))); 
	return distance;
	
}


void Tower::draw(SDL_Renderer* rndr){
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location, 0, &p, SDL_FLIP_NONE);
}
void Tower::update(){
}