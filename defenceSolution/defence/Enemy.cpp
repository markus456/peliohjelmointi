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

float Enemy::distance(float x1,float y1,float x2,float y2){
	return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}
float Enemy::distance(Location a,Location b){
	return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}