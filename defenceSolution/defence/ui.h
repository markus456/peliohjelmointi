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
	SDL_Rect _text_location;
	SDL_Color _color;
	bool _centered, _center;
	SDL_Texture* _text_texture;
	SDL_Renderer* renderer;
	TTF_Font* font;
	void alignText(){
		_text_location.x = _location.x + (_location.w-_text_location.w)/2;
		_text_location.y = _location.y + (_location.h - _text_location.h) / 2;
		_centered = true;
	}
public:
	/**
	*Luo TextButton olion, jolla on teksti.
	*/
	TextButton<T>(std::string string,std::string texture, SDL_Renderer* rndr) : _text(string), _text_wrap(20),
		_text_size(20), _centered(false), _center(false), renderer(rndr), ImageButton(nullptr, nullptr){
		color = {255,255,255,255};
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
		_text_size(20), _centered(false), _center(false), renderer(rndr), ImageButton(t, fnc){
		_color = { 255, 255, 255, 255 };
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
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), _color, _text_wrap);
		if (loc.w > tmp->w){
			loc.w = tmp->w;
		}
		if (loc.h > tmp->h){
			loc.h = tmp->h;
		}		
		setSize(loc);
		_text_location.w = tmp->w;
		_text_location.h = tmp->h;
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n parametrinä annetulla värillä*/
	virtual void setText(std::string s, SDL_Color color){
		_text = s;
		_color = color;
		SDL_Rect loc = getLocation();
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, s.c_str(), color, _text_wrap);
		if (loc.w > tmp->w){
			loc.w = tmp->w;
		}
		if (loc.h > tmp->h){
			loc.h = tmp->h;
		}
		setSize(loc);
		_text_location.w = tmp->w;
		_text_location.h = tmp->h;
		_text_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	/*Asettaa SDL_Renderer kohteen tekstin generoimista varten*/
	virtual void setRenderer(SDL_Renderer* rndr){ renderer = rndr;}
	virtual void setTextWrap(int i){
		_text_wrap = i;
		setText(_text);
	}
	virtual void centerText(bool b){ 
		_center = b;
		_centered = false;
	}
	virtual void setTextSize(int i){
		_text_size = i;
		TTF_CloseFont(font);
		font = nullptr;
		font = TTF_OpenFont("revalia.ttf", _text_size);
		if (font == nullptr){
			std::cout << "Error opening font.\n";
		}else{
			setText(_text);
		}
		
	}
	virtual std::string getText(){ return _text; }	
	virtual void draw(SDL_Renderer* rndr){
		if (_center&&!_centered){
			alignText();
		}
		SDL_RenderCopy(rndr, _texture, nullptr, &_location);
		SDL_RenderCopy(rndr, _text_texture, nullptr, &_text_location);
	}
	virtual ~TextButton(){

	}
	void setLocation(SDL_Point p){
		ImageButton::setLocation(p);
		_text_location.x = p.x;
		_text_location.y = p.y;
	}
	void setSize(SDL_Rect r){
		ImageButton::setSize(r);
		_text_location.x = _location.x + (_location.w - _text_location.w) / 2;
		_text_location.y = _location.y + (_location.h - _text_location.h) / 2;
	}
};
class Menu :public Button{
protected:
	bool _standardize, _resized;
	std::vector<std::shared_ptr<Button>> _buttons;
public:
	Menu():_standardize(false), _resized(false){}
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
	void standardize(bool b){
		_standardize = b;
	}
	void setLocation(SDL_Point p){
		SDL_Point pt = p;
		for (auto it = _buttons.begin(); it != _buttons.end();it++){
			(*it)->setLocation(p);
			p.y += (*it)->getLocation().h;
		}
	}
	virtual void update(){
		if (!_resized&&_standardize){
			int maxw = 0;
			int maxh = 0;
			for (auto& b : _buttons){
				if (b->getLocation().w > maxw){
					maxw = b->getLocation().w;
				}
				if (b->getLocation().h > maxh){
					maxh = b->getLocation().h;
				}
			}
			SDL_Rect loc = {0,0,maxw,maxh};
			for (auto& b : _buttons){
				b->setSize(loc);
			}
			_resized = true;
		}
	}
	virtual ~Menu(){
		_buttons.clear();
	}
};
#endif
