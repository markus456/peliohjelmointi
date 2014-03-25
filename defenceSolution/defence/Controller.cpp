#include "Controller.h"
Controller::~Controller(){
	_enemies.clear();
	_towers.clear();
	_bullets.clear();
	_buttons.clear();
}
void Controller::update(){
	_menu->update();
	if(_game_state!=Controller::GAME)return;
	for(auto& a:_enemies){
		a->update();
	}
	for(auto& a:_towers){
		a->update();
	}
	auto a = _bullets.begin();
	while(a!=_bullets.end()){
		(*a)->update();
		Location tmp =  (*a)->getLocation();
		if(tmp.x>System::SCREEN_WIDTH+100||tmp.x<-100||tmp.y<-100||tmp.y>System::SCREEN_HEIGHT+100){
			a = _bullets.erase(a);
		}else{
			a++;
		}
	}
	for(auto& a:_towers){
		if(a->needsBullet()){
			std::shared_ptr<Bullet> bullet(new Bullet);
			bullet->setTexture("bullet.png",_renderer);
			bullet->setSize(_tile_size);
			a->loadProjectile(bullet);
			_bullets.push_back(bullet);
		}		
	}
	_player->update();
}
void Controller::draw(){
	switch(_game_state){
	case Controller::GAME:
		if(_map.get() != nullptr){
			_map->drawMap();
		}
		for(const auto& a:_enemies){
			a->draw(_renderer);
		}
		for(const auto& a:_towers){
			a->draw(_renderer);
		}
		for(const auto& a:_bullets){
			a->draw(_renderer);
		}
		_player->draw(_renderer);
		break;
	case Controller::MAIN_MENU:
		for(const auto& a:_effects){
			a->draw(_renderer);
		}
		if(_menu.get() != nullptr){
			_menu->draw(_renderer);
		}
		break;
	case Controller::PAUSED:
		for(const auto& a:_effects){
			a->draw(_renderer);
		}
		if(_menu.get() != nullptr){
			_menu->draw(_renderer);
		}
		break;
	}
}
void Controller::onClick(int x,int y){
	if(_game_state==Controller::MAIN_MENU||_game_state==Controller::PAUSED){
	for(const auto& a:_buttons){
		if(a->isInside(x,y)){
			a->onClick(x,y);
			return;
		}
	}
	_menu->onClick(x,y);
	}else if(_game_state==Controller::GAME){
		_towers.push_back(std::shared_ptr<Tower>(new Tower(x,y,200,10)));		
		_towers.back()->setTexture("tower1.png",_renderer);
		_towers.back()->addEnemies(_enemies);
	}
}

void Controller::add(Button* b){
	std::shared_ptr<Button>shptr(b);
	_buttons.push_back(shptr);
}
void Controller::add(ImageSprite* b){
	_effects.push_back(std::shared_ptr<ImageSprite>(b));
}
void Controller::add(Bullet* b){
	_bullets.push_back(std::shared_ptr<Bullet>(b));
}
void Controller::add(Enemy* b){
	_enemies.push_back(std::shared_ptr<Enemy>(b));
}
void Controller::add(Tower* b){
	_towers.push_back(std::shared_ptr<Tower>(b));
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
	Location size;
	Location first(0,0,200,200);
	Location second(200,0,200,200);
	Location third (0,200,200,200);
	Location fourth (200,200,200,200);
	std::vector<Location> frames;
	Location position;
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
		_player = std::unique_ptr<Player>(new Player());
		_player->setTexture("player.png",_renderer);
		SDL_Point ppos = {9*System::SCREEN_WIDTH/10,System::SCREEN_HEIGHT/4};
		_player->setLocation(ppos);
		for(int i = 0;i<_enemy_cap;i++){
			SDL_Point epos = {System::SCREEN_WIDTH/10 + (rand() % 100),System::SCREEN_HEIGHT/4};
			_enemies.push_back(std::shared_ptr<Enemy>(new Enemy));
			switch(rand() % 3){
			case 0:
				_enemies.back()->setTexture("enemy1.png",_renderer);
				break;
			case 1:
				_enemies.back()->setTexture("enemy2.png",_renderer);
				break;
			case 2:
				_enemies.back()->setTexture("enemy3.png",_renderer);
				break;
			}
			_enemies.back()->setLocation(epos);
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

void Controller::playerMoveUp(bool move) {
	_player->setMoveUp(move);
}

void Controller::playerMoveDown(bool move) {
	_player->setMoveDown(move);
}

void Controller::playerMoveLeft(bool move) {
	_player->setMoveLeft(move);
}

void Controller::playerMoveRight(bool move) {
	_player->setMoveRight(move);
}
