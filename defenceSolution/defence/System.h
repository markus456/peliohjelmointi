#ifndef SYSTEM_H
#define SYSTEM_H

#include "SDL.h"

class System {
private:
	SDL_Event event;
	SDL_Window* wnd;
	SDL_Renderer *rndr;
	SDL_Texture *texture;
	bool running;
public:
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
};

#endif