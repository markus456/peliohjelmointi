#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include <string>
#include "include\SDL.h"
#include "include\SDL_ttf.h"
#include "Sprite.h"
class Button:public Sprite{
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location);
	}
	virtual void update(){}
	virtual void onClick(){}
};
template <class T> class ImageButton :public Button{
protected:
	void (T::*_fnc)(void);
	T* _t;
public:
	ImageButton<T>(T* t, void(T::*fnc)(void)):_t(t),_fnc(fnc){}
	virtual void onClick(){ (_t->*_fnc)(); }
	virtual void setCallbackFunction(void(T::*fptr)(void)){ _fnc = fptr; }
	virtual void setCallbackObject(T* t){ _t = t; }
};
template <class T> class TextButton :public ImageButton<T>{
protected:
	std::string _text;
	SDL_Texture* _text_texture;
	SDL_Renderer* renderer;
	TTF_Font* font;
public:
	/**
	*Luo TextButton olion, jolla on teksti.
	*/
	TextButton<T>(std::string s, SDL_Renderer* rndr) : _text(s), renderer(rndr), ImageButton(nullptr, nullptr){
		if (TTF_Init() != 0){
			std::cout << "Error initializing SDL_ttf.\n";
		}
		font = nullptr;
		font = TTF_OpenFont("revalia.ttf", 20);
		if (font == nullptr){
			std::cout << "Error opening font.\n";
		}
		SDL_Color color = { 255, 255, 255, 255};
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, getLocation().w);
		_location.h = tmp->h;
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/**
	*Luo TextButton olion, jolla on teksti ja funktio, jota se kutsuu onClick() metodissa.
	*/
	TextButton<T>(std::string s, SDL_Renderer* rndr, T* t, void(T::*fnc)(void)) : _text(s), renderer(rndr), ImageButton(t,fnc){
		if (TTF_Init() != 0){
			std::cout << "Error initializing SDL_ttf.\n";
		}
		font = nullptr;
		font = TTF_OpenFont("revalia.ttf", 20);
		if (font == nullptr){
			std::cout << "Error opening font.\n";
		}
		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, 30);
		loc.h = tmp->h;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n*/
	virtual void setText(std::string s){
		_text = s;
		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, 30);
		loc.h = tmp->h;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n parametrinä annetulla värillä*/
	virtual void setText(std::string s, SDL_Color color){
		_text = s;
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, 30);
		loc.h = tmp->h;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi annetulla fontilla muotoiltuna ja luo SDL_Texture:n*/
	virtual void setText(std::string s, TTF_Font* font){
		_text = s;
		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, 30);
		loc.h = tmp->h;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
		
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi annetulla fontilla muotoiltuna
	ja luo SDL_Texture:n parametrinä annetulla värillä*/
	virtual void setText(std::string s, SDL_Color color, TTF_Font* font){
		_text = s;
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, 30);
		loc.h = tmp->h;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa SDL_Renderer kohteen tekstin generoimista varten*/
	virtual void setRenderer(SDL_Renderer* rndr){ renderer = rndr; }
	virtual std::string getText(){ return _text; }
	/*Kutsutaan asetettua funktiota, kun TextButton:ia painetaan*/
	
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr, _texture, nullptr, &_location);
		SDL_RenderCopy(rndr, _text_texture, nullptr, &_location);
	}
};
#endif
