#include "Controller.h"
Controller::~Controller(){
	_enemies.clear();
	_towers.clear();
	_bullets.clear();
	_buttons.clear();
}
void Controller::update(){
	_menu->update();
	for(auto& a:_effects){
		a->update();
	}
	
	if(_game_state&(Controller::GAME_ACTIVE|Controller::GAME_WAIT)&&!(_game_state&Controller::PAUSED)){
		if(_enemies_got_through>=_params->enemiesAllowedThrough()){
		_enemies_got_through = 0;
		setGameState(Controller::GAME_OVER);
		buildMenu();
		}else if(_enemies.size()==0){
			buildEnemies();
		}
		auto e_iterator =_enemies.begin();
		while(e_iterator<_enemies.end()){
			(*e_iterator)->update();
			if((*e_iterator)->isEmpty()){
				e_iterator = _enemies.erase(e_iterator);
				_enemies_got_through++;
				_floating_text.clear();
				std::stringstream ss;
				ss << "Castle walls will hold " << _params->enemiesAllowedThrough()-_enemies_got_through << " more enemies!";
				_floating_text.push_back(std::shared_ptr<ImageSprite>(new TextSprite(ss.str(),true)));
				_floating_text.back()->setLocation(Location(System::SCREEN_WIDTH/2-_floating_text.back()->getLocation().w/4,System::SCREEN_HEIGHT/10));
			}else{
				e_iterator++;
			}
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
}
void Controller::draw(){
	if(_game_state&(Controller::MAIN_MENU|Controller::GAME_OVER)){
		for(const auto& a:_effects){
			a->draw(_renderer);
		}
		if(_menu.get() != nullptr){
			_menu->draw(_renderer);
		}
	}else if(_game_state&(Controller::GAME_ACTIVE|Controller::GAME_WAIT)){
		if(_map.get() != nullptr){
			_map->drawMap();
		}
		for(const auto& a:_effects){
			a->draw(_renderer);
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
		for(const auto& a:_floating_text){
			a->draw(_renderer);
		}
		if(_game_state&Controller::PAUSED){
			if(_menu.get() != nullptr){
				_menu->draw(_renderer);
			}
		}
	}

}
void Controller::onClick(int x,int y){
	if(_game_state&(Controller::MAIN_MENU|Controller::PAUSED|Controller::GAME_WAIT|Controller::GAME_OVER)){
		for(const auto& a:_buttons){
			if(a->isInside(x,y)){
				a->onClick(x,y);
				return;
			}
		}
		_menu->onClick(x,y);
	}else if(_game_state&Controller::GAME_ACTIVE){
		if(_towers.size()<_params->towerLimit()){
			_towers.push_back(std::shared_ptr<Tower>(new Tower(x,y,200,10)));		
			_towers.back()->setTexture("tower1.png",_renderer);
			_towers.back()->addEnemies(_enemies);
		}
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
	if(_game_state&Controller::PAUSED){
		size.w = System::SCREEN_WIDTH;
		size.h = System::SCREEN_HEIGHT;
		position.x = 0;
		position.y = 0;

		_menu.reset(new Menu());
		size.w = System::SCREEN_WIDTH/4;
		size.h = System::SCREEN_HEIGHT/4;
		position.x = System::SCREEN_WIDTH/4+System::SCREEN_WIDTH/8;
		position.y = System::SCREEN_HEIGHT/4+System::SCREEN_HEIGHT/8;
		_menu->setTexture("menu_background.png",_renderer);
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->standardize(true);
		_menu->addButton(new TextButton("Resume Game","button_background.png",_renderer,[this]{
			this->setGameState(getGameState()^Controller::PAUSED);
			this->initGame();
		}));
		_menu->addButton(new TextButton("Quit","button_background.png",_renderer,[=]{
			this->setGameState(Controller::MAIN_MENU);
			this->initGame();
		}));
	}else if(_game_state&Controller::MAIN_MENU){
		_effects.clear();
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
		s->setAnimationDelay(60*2);
		add(s);
		_menu.reset(new Menu());
		size.w = System::SCREEN_WIDTH/2;
		size.h = System::SCREEN_HEIGHT/2;
		position.x = System::SCREEN_WIDTH/4;
		position.y = System::SCREEN_HEIGHT/4;
		_menu->setTexture("menu_background.png",_renderer);
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->standardize(true);
		_menu->addButton(new TextButton("New Game","button_background.png",_renderer,[this]{
			this->setGameState(Controller::GAME_NEW);
			this->initGame();
		}));
		_menu->addButton(new TextButton("Exit","button_background.png",_renderer,[=]{
			_parent->exit();
		}));
	}else if(_game_state&Controller::GAME_OVER){
		_effects.clear();
		size.w = System::SCREEN_WIDTH;
		size.h = System::SCREEN_HEIGHT;
		position.x = 0;
		position.y = 0;
		s = new ImageSprite();
		s->setTexture("game_over_bg.png",_renderer);
		s->setSize(size);
		s->setLocation(position);
		s->setSpriteSheetSize(1,1);
		s->setLoop(true);		
		frames.push_back(first);
		frames.push_back(second);
		frames.push_back(third);
		frames.push_back(fourth);
		frames.push_back(third);
		frames.push_back(second);
		s->addFrames(frames);
		s->setAnimationDelay(8);
		add(s);
		_menu.reset(new Menu());
		size.w = System::SCREEN_WIDTH/2;
		size.h = System::SCREEN_HEIGHT/2;
		position.x = System::SCREEN_WIDTH/4;
		position.y = System::SCREEN_HEIGHT/4;
		_menu->setTexture("game_over.png",_renderer);
		_menu->setSize(size);
		_menu->setLocation(position);
		_menu->standardize(true);
		_menu->addButton(new TextButton("OK","button_background.png",_renderer,[this]{
			this->setGameState(Controller::MAIN_MENU);
			this->buildMenu();
		}));
	}
}
void Controller::initGame(){
	if(_game_state&(Controller::MAIN_MENU|Controller::PAUSED|Controller::GAME_OVER)){
		buildMenu();
	}else if(_game_state&Controller::GAME_NEW){
		setGameState(Controller::GAME_ACTIVE);
		_effects.clear();
		_enemies.clear();
		_bullets.clear();
		_towers.clear();
		_map.reset(new TileMap());
		_map->setMap("Level1temp.txt");
		_map->addTiles();
		_map->setRenderer(_renderer);
		_map->setTexture("terrain.png",_renderer);
		_player.reset(new Player());
		_player->setTexture("player.png",_renderer);
		SDL_Point ppos = {9*System::SCREEN_WIDTH/10,System::SCREEN_HEIGHT/4};
		_player->setLocation(ppos);
		
		_effects.push_back(std::shared_ptr<ImageSprite>(new ImageSprite()));
		_effects.back()->setTexture("castle.png",_renderer);
		_effects.back()->setSize(Location(0,0,200,150));
		_effects.back()->setLocation(Location(6*System::SCREEN_WIDTH/8,8*System::SCREEN_HEIGHT/10));

		buildEnemies();
	}
}
void Controller::buildEnemies(){
	for(int i = 0;i<_params->enemiesPerWave();i++){
			SDL_Point epos = {System::SCREEN_WIDTH/10 + (rand() % 100),System::SCREEN_HEIGHT/6};
			_enemies.push_back(std::shared_ptr<Enemy>(new Enemy));
			_enemies.back()->setSpeed(_params->enemySpeed());
			_enemies.back()->setHP(_params->enemyHP());
			_enemies.back()->setAttack(_params->enemyAttack());
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
	for(auto& a:_towers){
		a->addEnemies(_enemies);
	}
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
