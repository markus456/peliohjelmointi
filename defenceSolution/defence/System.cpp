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


<<<<<<< HEAD
	sprites.push_back(std::unique_ptr<Sprite>(new Tile()));
	SDL_Point tmp = {300, 500};
	SDL_Point tmpTower = {400,10};
	sprites.back()->setLocation(tmp);
	sprites.back()->setTexture("test.png",rndr);
	t = sprites.back().get();
	
	sprites.push_back(std::unique_ptr<Sprite>(new Tower()));
	sprites.back()->setLocation(tmpTower);
	sprites.back()->setTexture("test.bmp",rndr);

	sprites.push_back(std::unique_ptr<Sprite>(new Bullet()));
	sprites.back()->setTexture("test.bmp",rndr);
	tower = (Tower *)sprites.back().get();
	tower->setLocation(tmpTower);
	b = (Bullet *)sprites.back().get();
	tower->loadProjectile(tmp,0,b);
	
	//b->dirTo(tmp, 5);

=======
	sprites.push_back(std::shared_ptr<Sprite>(new Tile()));
	SDL_Point tmp = {50,50};
	sprites.back()->setLocation(tmp);
	sprites.back()->setTexture("test.bmp",rndr);
	uiElements.push_back(std::shared_ptr<Button>(new TextButton<Tile>("Testinappula", rndr, (Tile*)sprites.back().get(), &Tile::update)));
	tmp.y += 100;
	uiElements.back()->setLocation(tmp);
	uiElements.back()->setTexture("button_background.png", rndr);
	sprites.push_back(uiElements.back());
>>>>>>> uiproto2
	mousedown = false;
	return true;
}

void System::exit() {
	sprites.clear();
	IMG_Quit();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(rndr);
	SDL_DestroyWindow(wnd);
	SDL_Quit();
}

void System::enterMainLoop() {
	SDL_Point tmpTower = {400,10};
	SDL_Point tmp = {300, 500};
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
				
				tower->setLocation(tmpTower);
				tmp.x = event.button.x;
				tmp.y = event.button.y;
				tower->loadProjectile(tmp,0,b);
				tower->shoot();
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
		for(auto& a: sprites){
			SDL_Point tmp = {enemyX,enemyY};
			sprites.back()->setLocation(tmp);
			enemyX=enemyX+10;
			if(enemyX>=800){
				enemyX=-60;
			}
			SDL_Delay(300);
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
}

void System::eventKeyDown(SDL_Keycode sym) {
}

void System::eventKeyUp(SDL_Keycode sym) {
}

void System::mouseButtonDown(Uint8 button, Sint32 x, Sint32 y) {
	mousedown = true;
}

void System::mouseButtonUp(Uint8 button, Sint32 x, Sint32 y) {
	for (auto& a : uiElements){
		if (a->isInside(x, y)){
			a->onClick();
			break;
		}
	}
	mousedown = false;
}

void System::mouseMove(Sint32 x, Sint32 y) {
		for(auto& a: sprites){
			if(a->isInside(x,y)&&mousedown){
				//Toiminnallisuus puuttuu
			}
		}
}

void System::draw() {
	for(auto& a: sprites){
		a->draw(rndr);
	}
}
void System::update(){
	if (b->collideTest(*t)) {
		cout << "osuu " << b->getLocation().x << " " << b->getLocation().y << endl;
	}
	for(auto& a: sprites){
		//a->update();
	}
}