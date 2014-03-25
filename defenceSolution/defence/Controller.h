#ifndef CONTROLLER_HEADER_GUARD
#define CONTROLLER_HEADER_GUARD
#include <vector>
#include <memory>
class System;
#include "System.h"
#include "ui.h"
#include "Player.h"
#include "Sprite.h"
class Controller{
protected:
	std::vector<std::shared_ptr<Enemy>> _enemies;
	std::vector<std::shared_ptr<Tower>> _towers;
	std::vector<std::shared_ptr<Bullet>> _bullets;
	std::vector<std::shared_ptr<ImageSprite>> _effects;
	std::vector<std::shared_ptr<Button>> _buttons;
	System* _parent;
	unsigned int _game_state, _enemy_cap,_tower_cap;
	std::unique_ptr<TileMap> _map;
	std::unique_ptr<Player> _player;
	std::unique_ptr<Menu> _menu;
	SDL_Renderer* _renderer;
	Location _window_size,_tile_size;
	void buildMenu();
public:
	const static unsigned int MAIN_MENU = 1;
	const static unsigned int GAME = 2;
	const static unsigned int PAUSED = 3;
	Controller(System* parent, SDL_Renderer* rndr, SDL_Rect wndw):_parent(parent),_game_state(MAIN_MENU),_map(nullptr),_renderer(rndr), _window_size(wndw),_enemy_cap(5),_tower_cap(5){
		_tile_size = Location(0,0,32,32);
	}
	~Controller();
	void update();
	void draw();
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
};
#endif
