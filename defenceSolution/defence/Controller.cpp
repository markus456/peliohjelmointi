#include "Controller.h"
Controller::~Controller(){
	_enemies.clear();
	_towers.clear();
	_bullets.clear();
	_buttons.clear();
}
void Controller::update(){

	/// UI:n ja visuaalien päivitys

	_timer = SDL_GetTicks();
	_menu->update();
	auto eff_it = _effects.begin();
	while(eff_it<_effects.end()){
		(*eff_it)->update();
		if((*eff_it)->done()){
			eff_it = _effects.erase(eff_it);
			continue;
		}
		eff_it++;
	}
	for(auto& a:_texts){
		a->update();
	}


	if(!(_game_state&Controller::PAUSED)){
		if(_game_state&Controller::GAME_WAIT){ /// Aaltojen välinen tauko
			if(_params->waveDelay()<(_timer-_wave_timer)){
				setGameState(Controller::GAME_ACTIVE);
				_generated_enemies = 0;
				initGame();
			}
		}else if(_game_state&Controller::GAME_ACTIVE){ /// Aalto meneillään

			/// Pelin tila

			if(_enemies_got_through>=_params->enemiesAllowedThrough()){
				_enemies_got_through = 0;
				_effects.clear();
				setGameState(Controller::GAME_OVER);
				buildMenu();
			}else if(_enemies.size()<_params->enemiesPerWave()&&_timer-_spawn_delay>_params->spawnDelay()&&_generated_enemies<_params->totalEnemies()){
				buildEnemy();
				_spawn_delay = _timer;
				_generated_enemies++;
			}else if(_enemies.size()==0&&_generated_enemies>=_params->totalEnemies()){
				_generated_enemies = 0;
				_params->advance();
				setGameState(Controller::GAME_WAIT);
				initGame();
			}

			/// Vihollisten päivitys

			auto e_iterator =_enemies.begin();
			while(e_iterator<_enemies.end()){
				(*e_iterator)->update();
				auto p_it = _bullets.begin();
				while(p_it<_bullets.end()){
					if((*e_iterator)->isInside((*p_it)->getLocation())){
						(*e_iterator)->setHP((*e_iterator)->getHP()-(*p_it)->getDamage());
						createBlood((*e_iterator)->getLocation());

						p_it = _bullets.erase(p_it);
					}else{
						p_it++;
					}
				}
				if((*e_iterator)->isEmpty()){
					e_iterator = _enemies.erase(e_iterator);
					_enemies_got_through++;
					for(auto h_it = _healthbars.begin();h_it!=_healthbars.end();h_it++){
						if((*h_it)->getTarget()==(*e_iterator).get()){
							_healthbars.erase(h_it);
							break;
						}
					}
				}else if((*e_iterator)->getHP()<1){
					e_iterator = _enemies.erase(e_iterator);
					_current_gold++;
					for(auto h_it = _healthbars.begin();h_it!=_healthbars.end();h_it++){
						if((*h_it)->getTarget()==(*e_iterator).get()){
							_healthbars.erase(h_it);
							break;
						}
					}
				}else{
					e_iterator++;
				}
			}

			/// Tornien päivitys
			
			for(auto& a:_towers){
				a->update();
				a->addEnemies(_enemies);
			}
	
			
			/// Ammusten päivitys
			
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
			
			/// Tornien ammusten tarve
			
			for(auto& a:_towers){
				if(a->needsBullet()){
					std::shared_ptr<Bullet> bullet(new Bullet);
					bullet->setTexture("bullet.png",_renderer);
					bullet->setSize(_tile_size);
					a->loadProjectile(bullet);
					Mix_PlayChannel(-1,pew,0);
					_bullets.push_back(bullet);
				}		
			}

			/// Pelaajan päivitys
			for(auto& a:_healthbars){
				a->update();
			}
			_player->update();
		}
	}
}
void Controller::draw(){
	if(_game_state&(Controller::MAIN_MENU|Controller::GAME_OVER)){/// Päävalikko tai loppuruutu
		for(const auto& a:_effects){
			a->draw(_renderer);
		}
		if(_menu){
			_menu->draw(_renderer);
		}
	}else if(_game_state&(Controller::GAME_ACTIVE|Controller::GAME_WAIT)){/// Pelin pelaaminen
		if(_map){
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
		for(const auto& a:_texts){
			a->draw(_renderer);
		}
		for(const auto& a:_healthbars){
			a->draw(_renderer);
		}
		if(_game_state&Controller::PAUSED){
			if(_menu){
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
		Mix_PlayChannel(-1,menuClick,0);
		_menu->onClick(x,y);
	}else if(_game_state&Controller::GAME_ACTIVE){

		buildTower(x,y);

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
	Location first(0,0,200,200);///Nämä on väliaikaisia
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

		TextButton* b = new TextButton("New Game","button_background.png",_renderer,[this]{
			this->setGameState(Controller::GAME_NEW);
			this->initGame();
		});

		_menu->addButton(b);
		unsigned int bpos = _menu->size();
		b = new TextButton("Difficulty: EASY","button_background.png",_renderer,[=]{
			this->cycleDifficulty();
			switch(_params->difficulty()){
			case GameParams::EASY:
				((TextButton*)_menu->getButton(bpos))->setText("Difficulty: EASY");
				break;
			case GameParams::NORMAL:
				((TextButton*)_menu->getButton(bpos))->setText("Difficulty: NORMAL");
				break;
			case GameParams::HARD:
				((TextButton*)_menu->getButton(bpos))->setText("Difficulty: HARD");
				break;
			}
		});
		_menu->addButton(b);
		b = new TextButton("Exit","button_background.png",_renderer,[=]{
			_parent->exit();
		});
		_menu->addButton(b);
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
			resetGame();
			buildMenu();
		}));
	}
}
void Controller::resetGame(){
	_timer =  _enemies_got_through = _spawn_delay = _generated_enemies = 0;
	_current_gold = towerCost;
	setGameState(Controller::MAIN_MENU);
	_enemies.clear();
	_towers.clear();
	_bullets.clear();
	_effects.clear();
	_texts.clear();
	_buttons.clear();
	_enemy_path.clear();
}
void Controller::initGame(){
	if(_game_state&(Controller::MAIN_MENU|Controller::PAUSED|Controller::GAME_OVER)){
		loadSounds();
		buildMenu();
	}else if(_game_state&Controller::GAME_NEW){
		resetGame();
		setGameState(Controller::GAME_ACTIVE);
		_texts.push_back(std::shared_ptr<Sprite>(new TextCounter([this]{return currentGold();},0,"Gold: ")));
		_texts.back()->setLocation(Location(0,0));
		_texts.push_back(std::shared_ptr<Sprite>(new TextCounter([&]{return _params->enemiesAllowedThrough()-_enemies_got_through;},0,"The walls will hold "," more enemies!")));
		_texts.back()->setLocation(Location(0,50));
		_map.reset(new TileMap());
		_map->setRenderer(_renderer);
		_map->setTexture("terrain.png",_renderer);
		auto tmp_path = _map->getRoad(0);
		for(auto& a: tmp_path){
			_enemy_path.push_back(a.getLocation());
		}
		_player.reset(new Player());
		_player->setTexture("player.png",_renderer);
		SDL_Point ppos = {8*System::SCREEN_WIDTH/10,System::SCREEN_HEIGHT/4};
		_player->setLocation(ppos);
		_player->setMap(_map);

		_effects.push_back(std::shared_ptr<ImageSprite>(new ImageSprite()));
		_effects.back()->setTexture("castle.png",_renderer);
		_effects.back()->setSize(Location(0,0,200,150));
		_effects.back()->setLocation(Location(6*System::SCREEN_WIDTH/8,8*System::SCREEN_HEIGHT/10));
		buildEnemy();
	}else if(_game_state&Controller::GAME_WAIT){
		_wave_timer = _timer;
		_effects.clear();
		_enemies.clear();
		_bullets.clear();
		_texts.clear();
		_texts.push_back(std::shared_ptr<Sprite>(new TextCounter([&]{return (_params->waveDelay() - (_timer-_wave_timer))/1000;},0,"Next wave in ", " seconds!")));
		_texts.back()->setLocation(Location(0,50));
	}else if(_game_state&Controller::GAME_ACTIVE){
		_texts.clear();
		_texts.push_back(std::shared_ptr<Sprite>(new TextCounter([this]{return currentGold();},0,"Score: ")));
		_texts.back()->setLocation(Location(0,0));
		_texts.push_back(std::shared_ptr<Sprite>(new TextCounter([&]{return _params->enemiesAllowedThrough()-_enemies_got_through;},0,"The walls will hold "," more enemies!")));
		_texts.back()->setLocation(Location(0,50));
	}
}
void Controller::buildEnemy(){
	_generated_enemies ++;
	int enem = _enemies.size();
	_enemies.push_back(std::shared_ptr<Enemy>(new Enemy));
	_enemies.back()->setSpeed(_params->enemySpeed());
	_enemies.back()->setHP(_params->enemyHP());
	_enemies.back()->setAttack(_params->enemyAttack());
	Enemy* en = _enemies.back().get();
	ShapeCounter* s = new ShapeCounter([=]{
		if(en!=nullptr){
			return (float) en->getHP();
		}else{
			return 0.f;
		}		
	},_enemies.back().get());
	s->genTexture(_renderer);
	s->setSize(Location(0,0,32,10));
	_healthbars.push_back(std::shared_ptr<ShapeCounter>(s));
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
	_enemies.back()->setSize(_tile_size);

	auto tmp_path = _map->getRoad(rand() % 2);
	_enemy_path.clear();
		for(auto& a: tmp_path){
			_enemy_path.push_back(a.getLocation());
		}
	_enemies.back()->setPath(_enemy_path);
	Location epos = _enemy_path.front();
	_enemies.back()->setLocation(epos.toSDL_Rect());
	for(auto& a:_towers){
		a->addEnemies(_enemies);
	}
}
void Controller::buildTower(int x, int y){

	Tiili newTowerTile;
	bool tileTaken = false;

	if(_towers.size()<_params->towerLimit()){

		//tutkitaan tile johon ollaan rakentamassa tornia
		for(auto tile:_map->getMap()){
			if(tile.isInside(x,y)){
				newTowerTile = tile;
			}
		}

		//katsotaan onko tile tyhjä
		for(auto t:_towers){
			if(t->isInside(x,y)){
				tileTaken = true;
			}
		}
		if(newTowerTile.buildable() && !tileTaken && towerCost<=_current_gold){

			_towers.push_back(std::shared_ptr<Tower>(new Tower(newTowerTile.getLocation().x,newTowerTile.getLocation().y,400,10,towerCost)));
			_towers.back()->setTexture("tower1.png",_renderer);
			_towers.back()->setSize(Location(x,y,_tile_size.w,_tile_size.h));
			_towers.back()->addEnemies(_enemies);

			_current_gold-=towerCost;
		}
	}
}

std::shared_ptr<Bullet> Controller::buildBullet(){

	return std::shared_ptr<Bullet>();
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
unsigned int Controller::currentGold(){
	return _current_gold;
}
void Controller::cycleDifficulty(){
	if(++_difficulty>GameParams::HARD){
		_difficulty = GameParams::EASY;
	}
	_params.reset(new GameParams(_difficulty));
}

void Controller::playerDoDamage() {
	if(getGameState()==Controller::GAME_OVER)return;
	std::vector<Location> effect_frames;
	effect_frames.push_back(Location(0,0,64,64));
	effect_frames.push_back(Location(64,0,64,64));
	effect_frames.push_back(Location(0,64,64,64));
	effect_frames.push_back(Location(64,64,64,64));
	for (const auto &a : _enemies) {
		if (a->distance(*_player.get()) < 50) {
			a->setHP(a->getHP() - _player->getDamage());
			createBlood(a->getLocation());

		}
	}
	createEffect(_player->getLocation(),"explosion.png",5,Location(0,0,128,128),effect_frames);
}

void Controller::createEffect(Location &location, std::string filename, unsigned int delay,Location effect_size, std::vector<Location> framelist) {
	_effects.push_back(std::shared_ptr<ImageSprite>(new ImageSprite()));
	_effects.back()->setTexture(filename, _renderer);
	_effects.back()->setLocation(location);
	_effects.back()->setSize(effect_size);
	_effects.back()->setAnimationDelay(delay);
	if(framelist.size()>0){
		_effects.back()->addFrames(framelist);
	}
}
void Controller::createBlood(Location &location) {
	_effects.push_back(std::shared_ptr<ImageSprite>(new ImageSprite()));
	Mix_PlayChannel(-1,enemydeath,0);
	_effects.back()->setTexture("blood.png", _renderer);
	_effects.back()->setLocation(location);
	_effects.back()->setSize(_tile_size);
	_effects.back()->setAnimationDelay(90);
}
void Controller::loadSounds(){
	enemydeath = Mix_LoadWAV("sfx/enemydeath.wav");
	pew = Mix_LoadWAV("sfx/pew.wav");
	menuClick = Mix_LoadWAV("sfx/menu.wav");
}