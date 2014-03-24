#include "Controller.h"
Controller::~Controller(){
	_render_targets.clear();
	_update_targets.clear();
	_ui_targets.clear();
}
void Controller::update(){
	for(auto& a:_update_targets){
		a->update();
	}
}
void Controller::draw(){
	if(_map.get() != nullptr){
		_map->drawMap();
	}
	if(_menu.get() != nullptr){
		_menu->draw(_renderer);
	}
	for(const auto& a:_render_targets){
		a->draw(_renderer);
	}
}
void Controller::onClick(int x,int y){
	for(const auto& a:_ui_targets){
		if(a->isInside(x,y)){
			a->onClick(x,y);
			break;
		}
	}
}
void Controller::addRenderTarget(Sprite* s){
	_render_targets.emplace_back(std::shared_ptr<Sprite>(s));
}
void Controller::addUpdateTarget(Sprite* s){
	_update_targets.emplace_back(std::shared_ptr<Sprite>(s));
}
void Controller::addUiTarget(Button* b){
	_ui_targets.emplace_back(std::shared_ptr<Button>(b));
}
void Controller::add(Button* b){
	addUiTarget(b);
	addRenderTarget(b);
}
void Controller::add(Bullet* b){
	addRenderTarget(b);
	addUpdateTarget(b);
}
void Controller::add(Enemy* b){
	addRenderTarget(b);
	addUpdateTarget(b);
}
void Controller::add(Tower* b){
	addRenderTarget(b);
	addUpdateTarget(b);
}
void Controller::add(TileMap* b){
	_map.reset(b);
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
		s->setAnimationDelay(30);
		sprt = std::shared_ptr<ImageSprite>(s);
		_render_targets.insert(_render_targets.begin(),sprt);
		_update_targets.push_back(sprt);
		_menu.reset(new Menu());
		size.w = System::SCREEN_WIDTH/2;
		size.h = System::SCREEN_HEIGHT/2;
		position.x = System::SCREEN_WIDTH/4;
		position.y = System::SCREEN_HEIGHT/4;
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->setTexture("menu_background.png",_renderer);
		_menu->addButton(new TextButton("New Game","button_background.png",_renderer,[this]{
			this->setGameState(Controller::GAME);
			this->initGame();
		}));
		_menu->addButton(new TextButton("Exit","button_background.png",_renderer,[this]{
			_parent->exit();
		}));

		break;
	case Controller::PAUSED:

		break;
	}
}
void Controller::initGame(){
	if(_game_state==Controller::GAME){
	int rnd = rand() % 50;
	float a = rand() % 360;
	float speed = rand() % 5 + 5; 
	a = (3.141f*2.f)/a;
	SDL_Point pos = {0,0};
	for(int i = 0;i<rnd;i++){
		pos.x = rand() % System::SCREEN_WIDTH;
		pos.y = rand() % System::SCREEN_HEIGHT;
		Bullet* b = new Bullet();
		b->setDirection(a,speed);
		add(b);
	}
	}else if(_game_state==Controller::MAIN_MENU){
		buildMenu();
	}
}
