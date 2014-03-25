#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include "include\SDL.h"
#include "include\SDL_ttf.h"
#include "Sprite.h"
class ImageSprite:public Sprite{
protected:
	std::vector<SDL_Rect> _frames;
	std::vector<SDL_Rect>::iterator _frame_iterator;
	bool _loop;
	unsigned int _columns, _rows,_animation_delay,_delay;
public:
	ImageSprite():_loop(false),_columns(0),_rows(0),_animation_delay(0),_delay(0){}
	virtual void draw(SDL_Renderer* rndr){
		if(_frame_iterator!=_frames.end()){
			SDL_RenderCopy(rndr,_texture,&(*_frame_iterator),&_location);
		}
	}
	void setSpriteSheetSize(int columns, int rows){
		_columns = columns;
		_rows = rows;
	}
	void addFrames(std::vector<SDL_Rect> args){
		_frames = std::move(args);
		_frame_iterator = _frames.begin();
	}

	void setLoop(bool b){_loop = b;}
	void setAnimationDelay(unsigned int i){_animation_delay = i;}
	virtual void update(){
		if(_delay>0){
			_delay--;
		}else{
			_delay = _animation_delay;
			if(_frames.size()>0){
				_frame_iterator++;
				if(_frame_iterator==_frames.end()){
					if(_loop){
						_frame_iterator = _frames.begin();
					}
				}
			}
		}
	}
};
class Button:public Sprite{
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location);
	}
	virtual void update(){}
	virtual void onClick(){}
	virtual void onClick(int x, int y){}
};

class ImageButton :public Button{
protected:
	std::function<void ()> _fnc;
public:
	ImageButton(std::function<void()> fnc):_fnc(fnc){}
	virtual void onClick(){ if(_fnc!=nullptr)_fnc(); }
	virtual void setCallback(std::function<void ()> f){_fnc = f;}
};

class TextButton :public ImageButton{
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
	TextButton(std::string string,std::string texture, SDL_Renderer* rndr) : _text(string), _text_wrap(150),
		_text_size(20), _centered(false), _center(false), renderer(rndr), ImageButton(nullptr){
			_color.r = 255;
			_color.g = 255;
			_color.b = 255;
			_color.a = 255;
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
	TextButton(std::string string,std::string texture, SDL_Renderer* rndr, std::function<void ()> fnc ): _text(string), _text_wrap(150),
		_text_size(20), _centered(false), _center(false), renderer(rndr), ImageButton(fnc){
			_color.r = 255;
			_color.g = 255;
			_color.b = 255;
			_color.a = 255;
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
		_location.w = _text_location.w;
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
		_location.w = _text_location.w;
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
		SDL_DestroyTexture(_text_texture);
	}
	void setLocation(SDL_Point p){
		ImageButton::setLocation(p);
		_text_location.x = p.x;
		_text_location.y = p.y;
	}
	void setSize(SDL_Rect r){
		if(_location.w<_text_location.w){
			_location.w = _text_location.w;
		}
		ImageButton::setSize(r);
		_text_location.x = _location.x + (_location.w - _text_location.w) / 2;
		_text_location.y = _location.y + (_location.h - _text_location.h) / 2;
	}
};
class Menu :public Button{
protected:
	bool _standardize, _resized;
	std::vector<std::shared_ptr<Button>> _buttons;
	SDL_Rect largest;
public:
	Menu():_standardize(false), _resized(false){
		SDL_Rect l = {0,0,0,0};
		largest = l;
	}
	virtual void addButton(Button* b){
		if (_buttons.size() > 0){
			SDL_Rect l = _buttons.back()->getLocation();
			SDL_Point p = { l.x, l.y + l.h };
			b->setLocation(p);
		}
		else{
			SDL_Rect l = getLocation();
			SDL_Point p = { l.x, l.y};
			b->setLocation(p);
		}
		_buttons.push_back(std::shared_ptr<Button>(b));
		if(!_standardize)return;
		for(auto& a:_buttons){
			if(a->getLocation().w>largest.w){
				largest.w = a->getLocation().w;
			}
			if(a->getLocation().h>largest.h){
				largest.h = a->getLocation().h;
			}
		}
		for(auto& a:_buttons){
			a->setSize(largest);
		}
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

	/**
	Elementtien koon standardointi.

	Tasaa kaikki elementit leveimmän elementin kokoiseksi.
	*/
	void standardize(bool b){
		_standardize = b;
		_resized = false;
	}
	void setLocation(SDL_Point p){
		SDL_Point pt = p;
		Sprite::setLocation(pt);
		for (auto it = _buttons.begin(); it != _buttons.end();it++){
			(*it)->setLocation(p);
			p.y += (*it)->getLocation().h;
		}
	}
	virtual void update(){
		if (!_resized&&_standardize){
			SDL_Rect center = this->getLocation();
			center.x += center.w/2;
			center.y += center.h/2;
			int maxw = 0;
			int maxh = 0;
			for (auto& b : _buttons){
				center.y -= b->getLocation().h/2;
				if (b->getLocation().w > maxw){
					maxw = b->getLocation().w;
				}
				if (b->getLocation().h > maxh){
					maxh = b->getLocation().h;
				}
			}
			SDL_Rect loc = {0,0,maxw,maxh};
			SDL_Point npos = {center.x-maxw/2,center.y};
			for (auto& b : _buttons){
				b->setLocation(npos);
				b->setSize(loc);
				npos.y += b->getLocation().h;
			}
			_resized = true;
		}
	}
	virtual ~Menu(){
		_buttons.clear();
	}
};
#endif

