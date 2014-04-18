#ifndef SPRITE_HEADER_GUARD
#define SPRITE_HEADER_GUARD
#include "SDL.h"
#include "include\SDL_image.h"
#include <iostream>
#include <string>
class Location{
public:
	double x,y,w,h;
	Location():x(0),y(0),w(0),h(0){}
	Location(const SDL_Rect& r):x(r.x),y(r.y),w(r.w),h(r.h){}
	Location(double x_, double y_):x(x_),y(y_),w(0),h(0){}
	Location(double x_, double y_,double w_, double h_):x(x_),y(y_),w(w_),h(h_){}
	SDL_Rect toSDL_Rect(){
		SDL_Rect tmp = {x,y,w,h};
		return tmp;
	}
	SDL_Point toSDL_Point(){
		SDL_Point tmp = {x,y};
		return tmp;
	}
};
class Sprite{
protected:
	SDL_Texture* _texture;
	Location _location;
public:
	virtual void draw(SDL_Renderer*) = 0;
	virtual void update() = 0;
	virtual void setLocation(SDL_Point point){
		_location.x = point.x;
		_location.y = point.y;
	}
	virtual void setLocation(Location point){
		_location.x = point.x;
		_location.y = point.y;
	}
	Location getLocation()const{
		return _location;
	}
	virtual void setSize(SDL_Rect rect){
		_location.w = rect.w;
		_location.h = rect.h;
	}
	virtual void setSize(Location rect){
		_location.w = rect.w;
		_location.h = rect.h;
	}
	void setTexture(std::string filename, SDL_Renderer* rndr){
		SDL_Surface* tmp = IMG_Load(filename.c_str());
		if(tmp==0){
			std::cout << "Error loading file: " << filename << std::endl;
			return;
		}
		_location.w = tmp->w;
		_location.h = tmp->h;
		_texture = SDL_CreateTextureFromSurface(rndr, tmp);
		SDL_FreeSurface(tmp);
	}
	bool isInside(int x, int y){
		if(x<_location.x||x>_location.x+_location.w||y<_location.y||y>_location.y+_location.h)return false;
		return true;
	}
	bool isInside(Location l){
		if(l.x<_location.x||l.x>_location.x+_location.w||l.y<_location.y||l.y>_location.y+_location.h)return false;
		return true;
	}
	bool collideTest(Sprite &other) {
		Location other_loc = other.getLocation();
		if(other_loc.x + other_loc.w < _location.x || other_loc.x > _location.x + _location.w ||
			other_loc.y + other_loc.h < _location.y || other_loc.y > _location.y + _location.h) {
			return false;
		}
		return true;
	}
	float distance(Sprite &other) {
		Location a, b;
		a.x = other.getLocation().x + other.getLocation().w / 2;
		a.y = other.getLocation().y + other.getLocation().h / 2;
		b.x = _location.x + _location.w / 2;
		b.y = _location.y + _location.h / 2;
		return distance(a, b);
	}
	float distance(float x1, float y1, float x2, float y2){
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}
	float distance(Location a, Location b){
		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	}
	virtual ~Sprite(){
		SDL_DestroyTexture(_texture);
	}
};
class TestTile:public Sprite{
protected:
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
	}
	virtual void update(){

	}
};
#endif