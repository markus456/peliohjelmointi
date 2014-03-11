#ifndef SYSTEM_H
#define SYSTEM_H
#include "SDL.h"
#include "include\SDL_image.h"
#include "Sprite.h"
#include "ui.h"
#include "Bullet.h"
#include "Tower.h"
#include "Tiili.h"
#include "TileMap.h"
#include "Enemy.h"
#include <memory>
#include <vector>
class System {
private:
	SDL_Event event;
	SDL_Window* wnd;
	SDL_Renderer *rndr;
	SDL_Texture *texture;
	bool running,mousedown;
	Sprite *t;
	Bullet *b;
	int enemyX, enemyY;

	TileMap* map;

	Tower *tower;
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::vector<std::shared_ptr<Button>> uiElements;
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int FRAMERATE =60;
	System(void);
	~System(void);
	bool init();
	void exit();
	void enterMainLoop();
	void eventKeyDown(SDL_Keycode sym);
	void eventKeyUp(SDL_Keycode sym);
	void mouseButtonDown(Uint8 button, Sint32 x, Sint32 y);
	void mouseButtonUp(Uint8 button, Sint32 x, Sint32 y);
	void mouseMove(Sint32 x, Sint32 y);
	void draw();
	void update();
};
#endif