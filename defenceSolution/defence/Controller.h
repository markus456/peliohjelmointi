#ifndef CONTROLLER_HEADER_GUARD
#define CONTROLLER_HEADER_GUARD
#include <vector>
#include <memory>
class System;
#include "System.h"
#include "ui.h"
class Controller{
protected:
	std::vector<std::shared_ptr<Sprite>> _render_targets;
	std::vector<std::shared_ptr<Sprite>> _update_targets;
	std::vector<std::shared_ptr<Button>> _ui_targets;
	System* _parent;
	unsigned int _game_state;
	std::unique_ptr<TileMap> _map;
	std::unique_ptr<Menu> _menu;
	SDL_Renderer* _renderer;
	SDL_Rect _window_size;
	void addRenderTarget(Sprite* s);
	void addUpdateTarget(Sprite* s);
	void addUiTarget(Button* b);
	void buildMenu();
public:
	const static unsigned int MAIN_MENU = 1;
	const static unsigned int GAME = 2;
	const static unsigned int PAUSED = 3;
	Controller(System* parent, SDL_Renderer* rndr, SDL_Rect wndw):_parent(parent),_game_state(MAIN_MENU),_map(nullptr),_renderer(rndr), _window_size(wndw){}
	~Controller();
	void update();
	void draw();
	void onClick(int,int);
	void loadMap(std::string);
	void add(Button* b);
	void add(Bullet* b);
	void add(Enemy* b);
	void add(Tower* b);
	void add(TileMap* b);
	unsigned int getGameState();
	void setGameState(unsigned int);
	void initGame();
	
};
#endif