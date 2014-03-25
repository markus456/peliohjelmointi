#include "Controller.h"
Controller::~Controller(){
	_render_targets_game.clear();
	_render_targets_others.clear();
	_update_targets.clear();
	_ui_targets.clear();
}
void Controller::update(){
	_menu->update();
	if(_game_state!=Controller::GAME)return;
	for(auto& a:_update_targets){
		a->update();
	}
}
void Controller::draw(){
	switch(_game_state){
	case Controller::GAME:
		if(_map.get() != nullptr){
			_map->drawMap();
		}
		for(const auto& a:_render_targets_game){
			a->draw(_renderer);
		}
		break;
	case Controller::MAIN_MENU:
		for(const auto& a:_render_targets_others){
			a->draw(_renderer);
		}
		if(_menu.get() != nullptr){
			_menu->draw(_renderer);
		}
		break;
	case Controller::PAUSED:
		for(const auto& a:_render_targets_others){
			a->draw(_renderer);
		}
		if(_menu.get() != nullptr){
			_menu->draw(_renderer);
		}
		break;
	}
}
void Controller::onClick(int x,int y){
	
	for(const auto& a:_ui_targets){
		if(a->isInside(x,y)){
			a->onClick(x,y);
			return;
		}
	}
	_menu->onClick(x,y);
}

void Controller::add(Button* b){
	std::shared_ptr<Button>shptr(b);
	_ui_targets.push_back(shptr);
	_render_targets_others.push_back(shptr);
}
void Controller::add(ImageSprite* b){
	std::shared_ptr<Sprite>shptr(b);
	_update_targets.push_back(shptr);
	_render_targets_others.push_back(shptr);
}
void Controller::add(Bullet* b){
	std::shared_ptr<Sprite>shptr(b);
	_render_targets_game.push_back(shptr);
	_update_targets.push_back(shptr);
}
void Controller::add(Enemy* b){
	std::shared_ptr<Sprite>shptr(b);
	_render_targets_game.push_back(shptr);
	_update_targets.push_back(shptr);
}
void Controller::add(Tower* b){
	std::shared_ptr<Sprite>shptr(b);
	_render_targets_game.push_back(shptr);
	_update_targets.push_back(shptr);
}
void Controller::add(TileMap* b){
	_map = std::unique_ptr<TileMap>(b);
	_map->setRenderer(_renderer);
}
void Controller::loadMap(std::string s){
	if(_map.get() != nullptr){
		_map->setMap(s);
	}
}
unsigned int Controller::getGameState(){
	return _game_state;
}
void Controller::setGameState(unsigned int i){
	_game_state = i;
}
void Controller::buildMenu(){
	SDL_Rect size;
	SDL_Rect first = {0,0,200,200};
	SDL_Rect second = {200,0,200,200};
	SDL_Rect third = {0,200,200,200};
	SDL_Rect fourth = {200,200,200,200};
	std::vector<SDL_Rect> frames;
	SDL_Point position;
	std::shared_ptr<ImageSprite> sprt;
	ImageSprite* s = nullptr;
	switch(_game_state){
	case Controller::PAUSED:
		size.w = System::SCREEN_WIDTH;
		size.h = System::SCREEN_HEIGHT;
		position.x = 0;
		position.y = 0;
		s = new ImageSprite();
		s->setTexture("main_menu.png",_renderer);
		s->setSize(size);
		s->setLocation(position);
		s->setSpriteSheetSize(1,1);
		s->setLoop(true);		
		frames.push_back(first);
		frames.push_back(second);
		frames.push_back(third);
		frames.push_back(fourth);
		s->addFrames(frames);
		s->setAnimationDelay(60*5);
		add(s);
		_menu = std::unique_ptr<Menu>(new Menu());
		size.w = System::SCREEN_WIDTH/2;
		size.h = System::SCREEN_HEIGHT/2;
		position.x = System::SCREEN_WIDTH/4;
		position.y = System::SCREEN_HEIGHT/4;
		_menu->setTexture("menu_background.png",_renderer);
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->standardize(true);
		_menu->addButton(new TextButton("Resume Game","button_background.png",_renderer,[this]{
			this->setGameState(Controller::GAME);
			this->initGame();
		}));
		_menu->addButton(new TextButton("Exit","button_background.png",_renderer,[=]{
			_parent->exit();
		}));
		break;
	case Controller::MAIN_MENU:
		size.w = System::SCREEN_WIDTH;
		size.h = System::SCREEN_HEIGHT;
		position.x = 0;
		position.y = 0;
		s = new ImageSprite();
		s->setTexture("main_menu.png",_renderer);
		s->setSize(size);
		s->setLocation(position);
		s->setSpriteSheetSize(1,1);
		s->setLoop(true);		
		frames.push_back(first);
		frames.push_back(second);
		frames.push_back(third);
		frames.push_back(fourth);
		s->addFrames(frames);
		s->setAnimationDelay(60*5);
		add(s);
		_menu = std::unique_ptr<Menu>(new Menu());
		size.w = System::SCREEN_WIDTH/2;
		size.h = System::SCREEN_HEIGHT/2;
		position.x = System::SCREEN_WIDTH/4;
		position.y = System::SCREEN_HEIGHT/4;
		_menu->setTexture("menu_background.png",_renderer);
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->standardize(true);
		_menu->addButton(new TextButton("New Game","button_background.png",_renderer,[this]{
			this->setGameState(Controller::GAME);
			this->initGame();
		}));
		_menu->addButton(new TextButton("Exit","button_background.png",_renderer,[=]{
			_parent->exit();
		}));
		break;
	}
}
void Controller::initGame(){
	if(_game_state==Controller::GAME){
		_map = std::unique_ptr<TileMap>(new TileMap());
		_map->setMap("Level1temp.txt");
		_map->addTiles();
		_map->setRenderer(_renderer);
		_map->setTexture("terrain.png",_renderer);
		for(int i = 0;i<_enemy_cap;i++){
			SDL_Point epos = {System::SCREEN_WIDTH/10,System::SCREEN_HEIGHT/4};
			_update_targets.push_back(std::shared_ptr<Sprite>(new Enemy));
			switch(rand() % 3){
			case 0:
				_update_targets.back()->setTexture("enemy1.png",_renderer);
				break;
			case 1:
				_update_targets.back()->setTexture("enemy2.png",_renderer);
				break;
			case 2:
				_update_targets.back()->setTexture("enemy3.png",_renderer);
				break;
			}
			_update_targets.back()->setLocation(epos);
			_render_targets_game.push_back(_update_targets.back());
		}
	
	}else if(_game_state==Controller::MAIN_MENU||_game_state==Controller::PAUSED){
		buildMenu();
	}
}
void Controller::setEnemyCap(int i){
	_enemy_cap = i;
}
void Controller::setTowerCap(int i){
	_tower_cap = i;
}