#ifndef CONTROLLER_HEADER_GUARD
#define CONTROLLER_HEADER_GUARD
#include <vector>
#include <memory>
#include <sstream>
class System;
#include "System.h"
#include "GameParameters.h"
#include "ui.h"
#include "Player.h"
#include "Sprite.h"
class Controller{
protected:
	std::vector<std::shared_ptr<Enemy>> _enemies;
	std::vector<std::shared_ptr<Tower>> _towers;
	std::vector<std::shared_ptr<Bullet>> _bullets;
	std::vector<std::shared_ptr<ImageSprite>> _effects;
	std::vector<std::shared_ptr<Sprite>> _texts;
	std::vector<std::shared_ptr<Button>> _buttons;
	std::deque<Location> _enemy_path;
	System* _parent;
	std::unique_ptr<GameParams> _params;
	unsigned int _timer,_game_state,_enemies_got_through,_generated_enemies,_current_gold,_spawn_delay,_wave_timer,_difficulty;
	std::unique_ptr<TileMap> _map;
	std::unique_ptr<Player> _player;
	std::unique_ptr<Menu> _menu;
	SDL_Renderer* _renderer;
	Location _window_size,_tile_size;
	void buildMenu();
	void buildEnemy();
	void buildTower(int x, int y);
	std::shared_ptr<Bullet> buildBullet();

public:

	const static int towerCost=5; //TEMP, k‰ytet‰‰n atm controllerin constructorissa.
	
	const static unsigned int MAIN_MENU = 1;
	const static unsigned int GAME_ACTIVE = 2;
	const static unsigned int GAME_WAIT = 4;
	const static unsigned int GAME_NEW = 32;
	const static unsigned int GAME_OVER = 64;
	const static unsigned int PAUSED = 128;
	Controller(System* parent, SDL_Renderer* rndr, SDL_Rect wndw):_parent(parent),_game_state(MAIN_MENU),_map(nullptr),_timer(0),
		_renderer(rndr), _window_size(wndw),_enemies_got_through(0),_generated_enemies(0),_current_gold(towerCost),_spawn_delay(0)
	{
		_tile_size = Location(0,0,32,32);
		_difficulty = GameParams::EASY;
		_params = std::unique_ptr<GameParams>(new GameParams(GameParams::EASY));
	}
	~Controller();
	void update();
	void draw();
	void resetGame();
	void onClick(int,int);
	void loadMap(std::string);
	void add(Button* b);
	void add(ImageSprite* b);
	void add(Bullet* b);
	void add(Enemy* b);
	void add(Tower* b);
	void add(TileMap* b);
	unsigned int getGameState();
	void setGameState(unsigned int);
	void setEnemyCap(int);
	void setTowerCap(int);
	void initGame();
	void playerMoveUp(bool move);
	void playerMoveDown(bool move);
	void playerMoveLeft(bool move);
	void playerMoveRight(bool move);
	unsigned int currentGold();
	void cycleDifficulty();
	void playerDoDamage();
	void createBlood(Location &location);
	void createEffect(Location &location, std::string filename, unsigned int delay = 1,Location effect_size = Location(0,0,32,32), std::vector<Location> framelist = std::vector<Location>());
};
#endif
