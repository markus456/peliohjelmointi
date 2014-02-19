#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include "include\SDL.h"
#include "include\SDL_ttf.h"
#include <string>
class Button{
protected:
	float _x,_y,_w,_h;
	std::string _text;
	void (*_f_ptr)(void);
	SDL_Surface* _surface;
	TTF_Font* _font;
public:
	Button():_x(0), _y(0),_w(0),_h(0),_text(nullptr),_f_ptr(nullptr),_surface(nullptr){}

	//konstruktori pelk‰ll‰ paikkatiedolla
	Button(float x,float y,float w,float h):_x(x), _y(y),_w(w),_h(h),_text(nullptr),_f_ptr(nullptr){}

	//konstruktori paikkatiedolla ja tekstill‰
	Button(float x,float y,float w,float h,const char* text):_x(x), _y(y),_w(w),_h(h),_text(text),_f_ptr(nullptr),_surface(nullptr){
		TTF_Init();
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,_w),nullptr,_surface,nullptr);
	}

	//konstruktori paikkatiedolla, tekstill‰ ja funktiolla
	Button(float x,float y,float w,float h,const char* text, void(*function_pointer)(void)):_x(x), _y(y),_w(w),_h(h),_text(text),_f_ptr(function_pointer),_surface(nullptr){
		TTF_Init();
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,_w),nullptr,_surface,nullptr);
	}

	/**Konstruktori paikkatiedolla, tekstill‰, funktiolla ja taustakuvalla
	*Lataa kuvan tiedostosta, jonka j‰lkeen piirt‰‰ siihen tekstin
	*/
	Button(float x,float y,float w,float h,const char* text, void(*function_pointer)(void),const char* image):_x(x), _y(y),_w(w),_h(h),_text(text),_f_ptr(function_pointer){
		TTF_Init();
		_surface = SDL_LoadBMP(image);
		_font = TTF_OpenFont("FreeMonoBold.ttf",20);
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b= 255;
		color.a = 255;
		SDL_BlitSurface(TTF_RenderText_Blended_Wrapped(_font,_text.c_str(),color,_w),nullptr,_surface,nullptr);
	}

	virtual void render(SDL_Surface*);
	virtual void onClick(float,float);
	virtual bool isInside(int,int);
	void setX(float);
	float getX()const;
	void setY(float);
	float getY()const;
	void setW(float);
	float getW()const;
	void setH(float);
	float getH()const;
	void setText(const char*);
	std::string getText()const;
	void setCallback(void(*function_pointer)(void));
};
#endif
