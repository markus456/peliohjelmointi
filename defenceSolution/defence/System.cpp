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
	map = new TileMap();
	map->setMap("Level1temp.txt");
	map->setRenderer(rndr);
	map->addTiles();
	map->setTexture("terrain.png",rndr);
	enemyX = 0;
	enemyY = 0;
	sprites.push_back(std::shared_ptr<Sprite>(new TestTile()));
	SDL_Point tmp = {300, 500};
	SDL_Point tmpTower = {400,10};
	sprites.back()->setLocation(tmp);
	sprites.back()->setTexture("test.png",rndr);
	t = sprites.back().get();
	
	sprites.push_back(std::shared_ptr<Sprite>(new Tower()));
	sprites.back()->setLocation(tmpTower);
	sprites.back()->setTexture("tower.png",rndr);
	SDL_Rect loc = {0,0,64,64};
	sprites.back()->setSize(loc);

	sprites.push_back(std::shared_ptr<Sprite>(new Bullet()));
	sprites.back()->setTexture("button_background.png",rndr);
	tower = (Tower *)sprites.back().get();
	tower->setLocation(tmpTower);
	b = (Bullet *)sprites.back().get();
	tower->loadProjectile(tmp,0,b);
	loc.w = 32;
	loc.h = 32;
	sprites.back()->setSize(loc);
	sprites.push_back(std::shared_ptr<Sprite>(new TestTile()));
	sprites.back()->setLocation(tmp);
	sprites.back()->setTexture("test.bmp",rndr);
	Menu* menu = new Menu();
	TextButton<TestTile>* b = new TextButton<TestTile>("Testinappula", "button_background.png", rndr, (TestTile*)sprites.back().get(), &TestTile::update);
	menu->setLocation(tmp);
	menu->addButton(b);
	uiElements.push_back(std::shared_ptr<Button>(menu));
	sprites.push_back(uiElements.back());
	mousedown = false;
	return true;
}

void System::exit() {
	sprites.clear();
	uiElements.clear();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(rndr);
	SDL_DestroyWindow(wnd);
	TTF_Quit();
	IMG_Quit();
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
}

void System::eventKeyDown(SDL_Keycode sym) {
	SDL_Keymod modstate;
	switch (sym){
	case SDLK_F4:
			if (SDL_GetModState() == KMOD_LALT){
				running = false;
			}
		break;
	}
}

void System::eventKeyUp(SDL_Keycode sym) {
}

void System::mouseButtonDown(Uint8 button, Sint32 x, Sint32 y) {
	mousedown = true;
}

void System::mouseButtonUp(Uint8 button, Sint32 x, Sint32 y) {
	for (auto& a : uiElements){
		a->onClick(x, y);
	}
	mousedown = false;
}

void System::mouseMove(Sint32 x, Sint32 y) {
		/*for(auto& a: uiElements){
			
		}*/
}

void System::draw() {
	map->drawMap();
	for(auto& a: sprites){
		a->draw(rndr);
	}
}
void System::update(){
	if(mousedown){
		SDL_Rect loc = {0,0,32,32};
	SDL_Point tmpTower = {400,10};
	SDL_Point tmp = {300, 500};
	//tower->setLocation(tmpTower);
				tmp.x = event.button.x;
				tmp.y = event.button.y;
				sprites.push_back(std::shared_ptr<Sprite>(new Bullet()));
				
				b = (Bullet *)sprites.back().get();
				b->setTexture("button_background.png",rndr);
				tower->loadProjectile(tmp,5,b);
				tower->shoot();
				mouseButtonUp(event.button.button, event.motion.x, event.motion.y);
	}
	if (b->collideTest(*t)) {
		cout << "osuu " << b->getLocation().x << " " << b->getLocation().y << endl;
		SDL_Point tmppoint;
		b->setSpeed(0);
	}
	for(auto& a: sprites){
		a->update();
	}
}