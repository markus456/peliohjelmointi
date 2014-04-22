#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include <string>
#include "include\SDL.h"
#include "Sprite.h"
class Button:public Sprite{
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location);
	}
	virtual void update(){

	}
};
#endif
