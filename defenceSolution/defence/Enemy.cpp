#include "Enemy.h"


Enemy::Enemy(void):HP(1),ATK(1),speed(1),angle(1)
{
	_location.x=0;
	_location.y=0;
	teePolku();
}


Enemy::~Enemy(void)
{
}

void Enemy::attack()
{
}

void Enemy::teePolku(){
	std::ifstream read("polku.txt");
	while(read>>n>>m){
		tmp.x=n;
		tmp.y=m;
		polku.push_back(tmp);
	}
}

void Enemy::draw(SDL_Renderer* rndr)
{
	SDL_Point p = {_location.w / 2, _location.h / 2};
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location.toSDL_Rect(), 0, &p, SDL_FLIP_NONE);
}

void Enemy::update()
{
	if(!polku.empty()){
		if(_location.x<polku.front().x && _location.x!=polku.front().x){
			_location.x+=speed;
		}
		else if(_location.x>polku.front().x && _location.x!=polku.front().x){
			_location.x-=speed;
		}
		if(_location.y<polku.front().y && _location.y!=polku.front().y){
			_location.y+=speed;
		}
		else if(_location.y>polku.front().y && _location.x!=polku.front().y){
			_location.y-=speed;
		}
		if(_location.x==polku.front().x && _location.y==polku.front().y){
			if(!polku.empty()){
				polku.pop_front();
			}
		}
	}
}