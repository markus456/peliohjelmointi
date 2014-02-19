#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include "include\SDL_ttf.h"
#include <string>
class Button{
protected:
	std::string _text;
	void (*_f_ptr)(void);
	SDL_Renderer* _surface;
	SDL_Texture* _texture;
	SDL_Rect _rect;
	TTF_Font* _font;
public:
	Button():_text(nullptr),_f_ptr(nullptr),_surface(nullptr){
		_rect.x = 0;
		_rect.y = 0;
		_rect.w = 0;
		_rect.h = 0;
	}

	//konstruktori pelk‰ll‰ paikkatiedolla
	Button(float x,float y,float w,float h):_text(nullptr),_f_ptr(nullptr){
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
	}

	//konstruktori paikkatiedolla ja tekstill‰
	Button(float x,float y,float w,float h,const char* text):_text(text),_f_ptr(nullptr),_surface(nullptr){
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Surface* tmp;
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,w),nullptr,tmp,nullptr);
		_texture = SDL_CreateTextureFromSurface(_surface,tmp);
		SDL_FreeSurface(tmp);
	}

	//konstruktori paikkatiedolla, tekstill‰ ja funktiolla
	Button(float x,float y,float w,float h,const char* text, void(*function_pointer)(void)):_text(text),_f_ptr(function_pointer){
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Surface* tmp;
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,w),nullptr,tmp,nullptr);
		_texture = SDL_CreateTextureFromSurface(_surface,tmp);
		SDL_FreeSurface(tmp);
	}

	/**Konstruktori paikkatiedolla, tekstill‰, funktiolla ja taustakuvalla
	*Lataa kuvan tiedostosta, jonka j‰lkeen piirt‰‰ siihen tekstin
	*/
	Button(float x,float y,float w,float h,const char* text, void(*function_pointer)(void),const char* image):_text(text),_f_ptr(function_pointer){
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
		SDL_Surface* tmp = SDL_LoadBMP(image);
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,w),nullptr,tmp,nullptr);
		_texture = SDL_CreateTextureFromSurface(_surface,tmp);
		SDL_FreeSurface(tmp);
	}
	virtual ~Button(){
		SDL_DestroyTexture(_texture);
		SDL_DestroyRenderer(_surface);
	}
	virtual void render();
	virtual void onClick(float,float);
	virtual bool isInside(int,int);
	void setRectangle(SDL_Rect);
	SDL_Rect getRectangle()const;
	void setRenderer(SDL_Renderer*);
	void setText(const char*);
	std::string getText()const;
	void setCallback(void(*function_pointer)(void));
};
#endif
