#include "ui.h"
void Button::render(){
	if(_surface!=nullptr){
		SDL_RenderCopy(_surface,_texture,nullptr,&_rect);
	}
}
//kutsuu asetettua funktiopointteria, jos x ja y ovat nappulan sisäpuolella
void Button::onClick(float x, float y){
	if(isInside(x,y)&&_f_ptr!=nullptr){
		_f_ptr();
	}
}
bool Button::isInside(int x, int y){
if(_rect.x<x&&_rect.x+_rect.w>x&&_rect.y<y&&_rect.y+_rect.h>y){
	return true;	
}
return false;
}
void Button::setRectangle(SDL_Rect rect){
	_rect = rect;
}

SDL_Rect Button::getRectangle()const{
	return _rect;
}
void Button::setText(const char* text){
	_text = text;
}

std::string Button::getText()const{
	return _text;
}

void Button::setCallback(void(*function_pointer)(void)){
	_f_ptr = function_pointer;
}
void Button::setRenderer(SDL_Renderer* rndr){
	_surface = rndr;
}