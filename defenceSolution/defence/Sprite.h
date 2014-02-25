#ifndef SPRITE_HEADER_GUARD
#define SPRITE_HEADER_GUARD
#include "SDL.h"
#include <iostream>
class Sprite{
protected:
	SDL_Texture* _texture;
	SDL_Rect _location;
public:
	virtual void draw(SDL_Renderer*) = 0;
	virtual void update() = 0;
	void setLocation(SDL_Point point){
		_location.x = point.x;
		_location.y = point.y;
	}
	SDL_Rect getLocation()const{
		return _location;
	}
	void setSize(SDL_Rect rect){
		_location.w = rect.w;
		_location.h = rect.h;
	}
	void setTexture(std::string filename, SDL_Renderer* rndr){
		SDL_Surface* tmp = SDL_LoadBMP(filename.c_str());
		if(tmp==0){
			std::cout << "Error loading file: " << filename << std::endl;
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
};
class Tile:public Sprite{
protected:
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location);
	}
	virtual void update(){

	}
};
#endif