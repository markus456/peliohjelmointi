#include "Enemy.h"


Enemy::Enemy(void):HP(1),ATK(1),speed(1),angle(1)
{
	_location.x=0;
	_location.y=0;
	//teePolku();
}


Enemy::~Enemy(void)
{
}

void Enemy::attack()
{
}

void Enemy::teePolku(int pathnumber){
	if(pathnumber == 0){
		std::ifstream read("polku.txt");
		while(read>>n>>m){
			tmp.x=n * 32;
			tmp.y=m * 32;
				if(tmp.x==0){
					setLocation(Location(tmp.x, tmp.y));
				}
			polku.push_back(tmp);
		}
	}
		if(pathnumber == 1){
		std::ifstream read("polku2.txt");
		while(read>>n>>m){
			tmp.x=n * 32;
			tmp.y=m * 32;
				if(tmp.x==0){
					setLocation(Location(tmp.x, tmp.y));
				}
			polku.push_back(tmp);
		}
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
		if(distance(_location,polku.front())<speed*2){
			if(!polku.empty()){
				polku.pop_front();
			}
		}else if(_location.x<polku.front().x){
			_location.x+=speed;
		}
		else if(_location.x>polku.front().x){
			_location.x-=speed;
		}
		if(_location.y<polku.front().y){
			_location.y+=speed;
		}
		else if(_location.y>polku.front().y){
			_location.y-=speed;
		}
		
	}
}
bool Enemy::isEmpty(){
	return polku.empty();
}
void Enemy::setSpeed(int i){
	speed = i;
}
int Enemy::getSpeed(){
	return speed;
}
void Enemy::setAttack(int i){
	ATK = i;
}
int Enemy::getAttack(){
	return ATK;
}
void Enemy::setHP(int i){
	HP = i;
}
int Enemy::getHP(){
	return HP;
}
void Enemy::setPath(std::deque<Location>& path){
	polku = path;
}