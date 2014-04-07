#include <SDL.h>

const int TILE_GRASS = 0;
const int TILE_WATER = 1;

class Tile				//yksitt‰inen "tiili", joista koostetaan koko kartta
{
private:
	float posx;			//spriten x ja y koordinaatit
	float posy;
	int tileType;		//selvitt‰‰ kuvan sheetist‰..

public:
	Tile(int x, int y, int tileType);
	~Tile();

	void Draw(int x, int y, SDL_Surface* dest);	// spriten piirtoon koordinaatit ja mihin piirret‰‰n
};