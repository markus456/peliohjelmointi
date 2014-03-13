#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include <string>
#include <vector>
#include <memory>
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
	virtual void onClick(int x, int y){}
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
	int _text_wrap,_text_size;
	SDL_Texture* _text_texture;
	SDL_Renderer* renderer;
	TTF_Font* font;
public:
	/**
	*Luo TextButton olion, jolla on teksti.
	*/
	TextButton<T>(std::string string,std::string texture, SDL_Renderer* rndr) : _text(string), _text_wrap(20),
		_text_size(20), renderer(rndr), ImageButton(nullptr, nullptr){
		Button::setTexture(texture,rndr);
		if (TTF_Init() != 0){
			std::cout << "Error initializing SDL_ttf.\n";
		}
		setTextSize(_text_size);
		setText(string);
	}
	/**
	*Luo TextButton olion, jolla on teksti ja funktio, jota se kutsuu onClick() metodissa.
	*/
	TextButton<T>(std::string string,std::string texture, SDL_Renderer* rndr, T* t, void(T::*fnc)(void)) : _text(string), _text_wrap(20),
		_text_size(20), renderer(rndr), ImageButton(t,fnc){
		Button::setTexture(texture,rndr);
		if (TTF_Init() != 0){
			std::cout << "Error initializing SDL_ttf.\n";
		}
		setTextSize(_text_size);
		setText(string);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n*/

	virtual void setText(std::string s){
		_text = s;
		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Rect loc;
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, _text_wrap);
		loc.h = tmp->h;
		loc.w = tmp->w;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n parametrinä annetulla värillä*/
	virtual void setText(std::string s, SDL_Color color){
		_text = s;
		SDL_Rect loc;
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, _text_wrap);
		loc.h = tmp->h;
		loc.w = tmp->w;
		setSize(loc);
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa SDL_Renderer kohteen tekstin generoimista varten*/
	virtual void setRenderer(SDL_Renderer* rndr){ renderer = rndr; }
	virtual void setTextWrap(int i){_text_wrap = i;}
	virtual void setTextSize(int i){
		_text_size = i;
		TTF_CloseFont(font);
		font = nullptr;
		font = TTF_OpenFont("revalia.ttf", _text_size);
		if (font == nullptr){
			std::cout << "Error opening font.\n";
		}
	}
	virtual std::string getText(){ return _text; }	
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr, _texture, nullptr, &_location);
		SDL_RenderCopy(rndr, _text_texture, nullptr, &_location);
	}
	virtual ~TextButton(){

	}
};
class Menu :public Button{
protected:
	std::vector<std::shared_ptr<Button>> _buttons;
public:
	Menu(){}
	virtual void addButton(Button* b){
		if (_buttons.size() > 0){
			SDL_Rect l = _buttons.back()->getLocation();
			SDL_Point p = { l.x, l.y + l.h };
			b->setLocation(p);
		}
		else{
			SDL_Rect l = getLocation();
			SDL_Point p = { l.x, l.y + l.h };
		}
		_buttons.push_back(std::shared_ptr<Button>(b));
	}
	virtual Button* getButton(unsigned int i){
		if (i < _buttons.size()){
			return _buttons[i].get();
		}
		return nullptr;
	}
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr, _texture, nullptr, &_location);
		for (auto& a : _buttons){
			a->draw(rndr);
		}
	}
	virtual void onClick(int x, int y){
		for (auto& a : _buttons){
			if (a->isInside(x,y)){
				a->onClick();
				return;
			}
		}
	}
	virtual void update(){}
	virtual ~Menu(){
		_buttons.clear();
	}
};
#endif
