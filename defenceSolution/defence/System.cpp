#include "System.h"
#include <iostream>
using namespace std;

System::System(void) {
	 running = true;
	 wnd = NULL;
}

System::~System(void) {
}

bool System::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL init failed." << endl;
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG)==0){
		std::cout << "IMG_Init: " << IMG_GetError();
	}
	wnd = SDL_CreateWindow("Testi", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (wnd == NULL) {
		cout << "Window creation failed." << endl;
		return false;
	}

    rndr = SDL_CreateRenderer(wnd, -1, 0);
    if (rndr == NULL) {
            cout << "render creation failed." << endl;
    }
	SDL_Rect wndw = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	controller = new Controller(this,rndr,wndw);
	controller->initGame();
	mousedown = false;
	return true;
}

void System::exit() {
	running = false;
}

void System::enterMainLoop() {
	
	while (running)
	{
		while(SDL_PollEvent(&event)){
			switch (event.type)
			{
			case SDL_KEYDOWN:
				eventKeyDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				eventKeyUp(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtonDown(event.button.button, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtonUp(event.button.button, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEMOTION:
				mouseMove(event.motion.x, event.motion.y);
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		long frame_start = SDL_GetTicks();
		update();
		
		SDL_RenderClear(rndr);

		draw();
        
		SDL_RenderPresent(rndr);
		long frame_end = SDL_GetTicks();
		if(frame_end-frame_start<1000.f/FRAMERATE){
			SDL_Delay(1000.f/FRAMERATE-(frame_end-frame_start));
		}
	}
	delete controller;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(rndr);
	SDL_DestroyWindow(wnd);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void System::eventKeyDown(SDL_Keycode sym) {
	SDL_Keymod modstate;
	switch (sym){
	case SDLK_F4:
			if (SDL_GetModState() == KMOD_LALT){
				running = false;
			}
		break;
	case SDLK_F1:
		controller->setGameState(controller->getGameState()^Controller::PAUSED);
		controller->initGame();
		break;
	case SDLK_w:
		controller->playerMoveUp(true);
		break;
	case SDLK_s:
		controller->playerMoveDown(true);
		break;
	case SDLK_a:
		controller->playerMoveLeft(true);
		break;
	case SDLK_d:
		controller->playerMoveRight(true);
		break;
	}
}

void System::eventKeyUp(SDL_Keycode sym) {
	switch (sym) {
	case SDLK_w:
		controller->playerMoveUp(false);
		break;
	case SDLK_s:
		controller->playerMoveDown(false);
		break;
	case SDLK_a:
		controller->playerMoveLeft(false);
		break;
	case SDLK_d:
		controller->playerMoveRight(false);
		break;
	}
}

void System::mouseButtonDown(Uint8 button, Sint32 x, Sint32 y) {
	mousedown = true;

}

void System::mouseButtonUp(Uint8 button, Sint32 x, Sint32 y) {
	controller->onClick(x,y);
	mousedown = false;
}

void System::mouseMove(Sint32 x, Sint32 y) {
		
}

void System::draw() {
	controller->draw();
}
void System::update(){
	controller->update();
}