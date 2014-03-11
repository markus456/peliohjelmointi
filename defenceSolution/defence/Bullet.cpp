<<<<<<< HEAD
#include "Bullet.h"


Bullet::Bullet(void) {
	dir = 0;
	speed = 0;
	_location.x = 0;
	_location.y = 0;
	//setDirection(M_PI/3, 5);
	//SDL_Point p = {500, 500};
	//dirTo(p, 5);
}


Bullet::~Bullet(void) {
}

void Bullet::draw(SDL_Renderer* rndr){
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location, dir / M_PI * 180, &p, SDL_FLIP_NONE);
}

void Bullet::update(){
	_location.x += cos(dir) * speed;
	_location.y += sin(dir) * speed;
}

void Bullet::setDirection(double dir, double speed) {
	this->dir = dir;
	this->speed = speed;

}

void Bullet::dirTo(SDL_Point point, double speed) {
	double dir = atan2(point.y - _location.y, point.x - _location.x);
	setDirection(dir, speed);
}

void Bullet::setStartLocation(SDL_Point point){
	_location.x=point.x;
	_location.y=point.y;
}

void Bullet::setSpeed(double speed){
	this->speed = speed;
=======
#include "Bullet.h"


Bullet::Bullet(void) {
	dir = 0;
	speed = 0;
	_location.x = 0;
	_location.y = 0;
	//setDirection(M_PI/3, 5);
	//SDL_Point p = {500, 500};
	//dirTo(p, 5);
}


Bullet::~Bullet(void) {
}

void Bullet::draw(SDL_Renderer* rndr){
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location, dir / M_PI * 180, &p, SDL_FLIP_NONE);
}

void Bullet::update(){
	_location.x += cos(dir) * speed;
	_location.y += sin(dir) * speed;
}

void Bullet::setDirection(double dir, double speed) {
	this->dir = dir;
	this->speed = speed;

}

void Bullet::dirTo(SDL_Point point, double speed) {
	double dir = atan2(point.y - _location.y, point.x - _location.x);
	setDirection(dir, speed);
>>>>>>> uiproto2
}