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
	if (TTF_Init() < 0){
		cout << "SDL_ttf init failed." << endl;
		return false;
	}

	wnd = SDL_CreateWindow("Testi", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
	if (wnd == NULL) {
		cout << "Window creation failed." << endl;
		return false;
	}

    rndr = SDL_CreateRenderer(wnd, -1, 0);
    if (rndr == NULL) {
            cout << "render creation failed." << endl;
    }

	texture = SDL_CreateTexture(rndr, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
	
	testbutton = new Button(100,100,50,100,"Testinappula",0,"test.bmp");
	testbutton->setRenderer(rndr);
	return true;
}

void System::exit() {
	delete testbutton;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(rndr);
	SDL_DestroyWindow(wnd);
	SDL_Quit();
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

		SDL_RenderClear(rndr);

		draw();

        SDL_RenderCopy(rndr, texture, NULL, NULL);
        SDL_RenderPresent(rndr);
	}
}

void System::eventKeyDown(SDL_Keycode sym) {

}

void System::eventKeyUp(SDL_Keycode sym) {

}

void System::mouseButtonDown(Uint8 button, Sint32 x, Sint32 y) {

}

void System::mouseButtonUp(Uint8 button, Sint32 x, Sint32 y) {

}

void System::mouseMove(Sint32 x, Sint32 y) {
	SDL_Rect tmp = testbutton->getRectangle();
	tmp.x = x;
	tmp.y = y;
	testbutton->setRectangle(tmp);
}

void System::draw() {
	testbutton->render();
}