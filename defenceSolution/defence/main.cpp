#include "SDL.h"
int main(int argc, char** argv){
	SDL_Event event;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* wnd = SDL_CreateWindow("Testi", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
	bool running = true;
	while (running)
	{
		while(SDL_PollEvent(&event)){
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	
	}
	return 0;
}