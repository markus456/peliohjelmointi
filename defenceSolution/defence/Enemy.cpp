#include "Enemy.h"


Enemy::Enemy(void):HP(1),ATK(1),speed(1)
{
	_location.x=0;
	_location.y=0;
}


Enemy::~Enemy(void)
{
}

void Enemy::attack()
{
}

void Enemy::draw(SDL_Renderer* rndr)
{
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location.toSDL_Rect(), 0, &p, SDL_FLIP_NONE);
}

void Enemy::update()
{
	if(_location.x<=180){
		_location.x+=speed;
	}
	else if(_location.y<=215){
		_location.y+=speed;
	}
	else if(_location.x<=660){
		_location.x+=speed;
	}
	else if(_location.y<=500){
		_location.y+=speed;
	}
}