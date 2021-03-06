#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <sstream>
#include "include\SDL.h"
#include "include\SDL_ttf.h"
#include "Sprite.h"
#include "Enemy.h"
class ShapeCounter:public Sprite{
protected:
	float _initial, _current;
	float _width,_height;
	Enemy* _target;
	Location _original_size;
	std::function<float ()> _fnc;
public:
	ShapeCounter(std::function<float ()> f = nullptr, Enemy* trgt = nullptr):_initial(0),_current(0),_fnc(f),_target(trgt){
		if(f){
			_initial = f();
			_current = _initial;
		}
	}
	void setSize(Location l){
		_original_size = l;
		Sprite::setSize(l);
	}
	bool genTexture(SDL_Renderer* rndr){
		SDL_Surface* s = nullptr;
		s = SDL_CreateRGBSurface(0, 32, 32, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		if(s==nullptr)return false;
		if(SDL_FillRect(s,nullptr,SDL_MapRGB(s->format,0,255,0)) != 0){
			SDL_FreeSurface(s);
			return false;
		}
		auto tex = SDL_CreateTextureFromSurface(rndr, s);
		if(tex == nullptr)return false;
		_texture = tex;
		return true;
	}
	virtual void draw(SDL_Renderer* rndr){
		if(_target!=nullptr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
		}
	}
	Enemy* getTarget(){
		return _target;
	}
	virtual void update(){
		if(_target!=nullptr){
			auto loc = _target->getLocation();
			if(loc.y - 32 > 0){
			loc.y -= 32;
			}
			setLocation(loc);
		}
		if(_fnc){
			_current = _fnc();
			auto size_before = getLocation();
			size_before.w = (_current/_initial)*_original_size.w;
			if(size_before.w>_original_size.w){
				size_before = _original_size;
			}
			Sprite::setSize(size_before);
		}
	}
};
class TextCounter:public Sprite{
protected:
	std::function<int ()> _funct;
	int _value;
	std::string _prefix,_suffix;
	std::stringstream _strgen;
	TTF_Font* _font;
	SDL_Color _color;
	SDL_Surface* _tmp;
	SDL_Renderer* _rndr;

public:
	TextCounter(std::function<int ()> fnc = nullptr,int val = 0, std::string pref = "",std::string suff = ""):_funct(fnc),_value(val),_prefix(pref),_suffix(suff){
		_font = TTF_OpenFont("revalia.ttf", 20);
		_color.r = _color.g = _color.b = _color.a = 255;
	}
	void update(){
		if(_rndr!=nullptr&&_funct&&_funct()!=_value){
			_value = _funct();
			_strgen.str("");
			_strgen << _prefix << _value << _suffix;
			std::string tstr = _strgen.str();
			_tmp= TTF_RenderText_Blended_Wrapped(_font, tstr.c_str(), _color, 25*tstr.size());
			setSize(Location(0,0,_tmp->w,_tmp->h));
			_texture = SDL_CreateTextureFromSurface(_rndr, _tmp);	
		}
	}
	void draw(SDL_Renderer* rndr){
		if(_rndr==nullptr){
			_rndr = rndr;
		}else{
			SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
		}
	}
	~TextCounter(){
		SDL_FreeSurface(_tmp);
		TTF_CloseFont(_font);
	}
};

/*
*Animoitu sprite.
*/
class ImageSprite:public Sprite{
protected:
	std::vector<Location> _frames;
	std::vector<Location>::iterator _frame_iterator;
	bool _loop,_is_done;
	unsigned int _columns, _rows,_animation_delay,_delay;
public:
	ImageSprite():_loop(false),_columns(0),_rows(0),_animation_delay(0),_delay(0),_is_done(false){}
	virtual void draw(SDL_Renderer* rndr){
		if(_frame_iterator!=_frames.end()){
			SDL_RenderCopy(rndr,_texture,&(*_frame_iterator).toSDL_Rect(),&_location.toSDL_Rect());
		}else if(_frames.size()==0){
			SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
		}
	}
	bool done(){
		return _is_done;
	}
	void setSpriteSheetSize(int columns, int rows){
		_columns = columns;
		_rows = rows;
	}
	void addFrames(std::vector<Location> args){
		_frames = std::move(args);
		_frame_iterator = _frames.begin();
	}

	void setLoop(bool b){_loop = b;}
	void setAnimationDelay(unsigned int i){
		_animation_delay = i;
		_delay = _animation_delay;
	}
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
					}else{
						_is_done = true;
					}
				}
			}else{
				_is_done = true;
			}
		}
	}
};
/*
*Animoitu sprite p��ll� olevalla tekstill�
*/
class TextSprite:public ImageSprite{
protected:
	std::string _text;
	SDL_Texture* _text_texture;
	Location _text_location;
	bool _tex_created,_transparent;
	void genTextTex(SDL_Renderer* rndr){
		TTF_Font* font = TTF_OpenFont("revalia.ttf", 20);
		SDL_Color color = {255,255,255};
		SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, _text.c_str(), color, _text.size()*20);
		_text_location.w = tmp->w;
		_text_location.h = tmp->h;
		if(_transparent){
			_location.w = tmp->w;
			_location.h = tmp->h;
		}
		_text_texture = SDL_CreateTextureFromSurface(rndr, tmp);
		SDL_FreeSurface(tmp);
		TTF_CloseFont(font);
	}
public:
	TextSprite(std::string text = "",bool transparent = true):_text(text),_tex_created(false),_transparent(transparent){
		_location.w = text.size()*20;
	}
	virtual void draw(SDL_Renderer* rndr){
		if(!_tex_created){
			genTextTex(rndr);
			_tex_created = true;
		}
		SDL_RenderCopy(rndr,_text_texture,nullptr,&_text_location.toSDL_Rect());
		if(!_transparent){
			ImageSprite::draw(rndr);
		}
	}
	virtual void setLocation(Location l){
		_text_location = l;
		ImageSprite::setLocation(l);
	}
};
class Button:public Sprite{
public:
	virtual void draw(SDL_Renderer* rndr){
		SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
	}
	virtual void update(){}
	virtual void onClick(int x = 0, int y = 0){}
};

class ImageButton :public Button{
protected:
	std::function<void ()> _fnc;
public:
	ImageButton(std::function<void()> fnc):_fnc(fnc){}
	virtual void onClick(int,int){ if(_fnc!=nullptr)_fnc(); }
	virtual void setCallback(std::function<void ()> f){_fnc = f;}
};

class TextButton :public ImageButton{
protected:
	std::string _text;
	int _text_wrap,_text_size;
	Location _text_location;
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
		Location loc = getLocation();
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
	/*Asettaa TextButton olion tekstin parametrin tekstiksi ja luo SDL_Texture:n parametrin� annetulla v�rill�*/
	virtual void setText(std::string s, SDL_Color color){
		_text = s;
		_color = color;
		Location loc = getLocation();
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
		SDL_RenderCopy(rndr, _texture, nullptr, &_location.toSDL_Rect());
		SDL_RenderCopy(rndr, _text_texture, nullptr, &_text_location.toSDL_Rect());
	}
	virtual ~TextButton(){
		SDL_DestroyTexture(_text_texture);
	}
	void setLocation(Location p){
		ImageButton::setLocation(p);
		_text_location.x = p.x;
		_text_location.y = p.y;
	}
	void setSize(Location r){
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
	Location largest, title_pos;
	SDL_Texture* title;

public:
	Menu():_standardize(false), _resized(false){
		largest = Location(0,0,0,0);
	}
	unsigned int size(){
		return _buttons.size();
	}
	virtual void addButton(Button* b){
		if (_buttons.size() > 0){
			Location l = _buttons.back()->getLocation();
			l.y += l.h;
			b->setLocation(l);
		}
		else{
			b->setLocation(getLocation());
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
		SDL_RenderCopy(rndr, _texture, nullptr, &_location.toSDL_Rect());
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

	Tasaa kaikki elementit leveimm�n elementin kokoiseksi.
	*/
	void standardize(bool b){
		_standardize = b;
		_resized = false;
	}
	void setLocation(Location p){
		Sprite::setLocation(p);
		for (auto it = _buttons.begin(); it != _buttons.end();it++){
			(*it)->setLocation(p);
			p.y += (*it)->getLocation().h;
		}
	}
	virtual void update(){
		if (!_resized&&_standardize){
			Location center = this->getLocation();
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
			Location loc (center.x-maxw/2,center.y,maxw,maxh);
			for (auto& b : _buttons){
				b->setLocation(loc);
				b->setSize(loc);
				loc.y += b->getLocation().h;
			}
			_resized = true;
		}
	}
	virtual ~Menu(){
		_buttons.clear();
	}
};
#endif

