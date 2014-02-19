#include "ui.h"
void Button::render(SDL_Surface* dest){
	SDL_BlitSurface(_surface,nullptr,dest,nullptr);
}
//kutsuu asetettua funktiopointteria, jos x ja y ovat nappulan sisäpuolella
void Button::onClick(float x, float y){
	if(isInside(x,y)){
		_f_ptr();
	}
}
bool Button::isInside(int x, int y){
if(_x<x&&_x+_w>x&&_y<y&&_y+_h>y){
	return true;	
}
return false;
}

void Button::setX(float x){
	_x = x;
}

float Button::getX()const{
	return _x;
}

void Button::setY(float y){
	_y = y;
}

float Button::getY()const{
	return _y;
}

void Button::setW(float w){
	_w = w;
}

float Button::getW()const{
	return _w;
}

void Button::setH(float h){
	_h = h;
}

float Button::getH()const{
	return _h;
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