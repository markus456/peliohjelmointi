#include <fstream>
#ifdef SYSTEM_LIBS
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

const int TILE_GRASS = 0;
const int TILE_WATER = 1;

const int TOTAL_TILES = 2;	//monta eri tiilt‰ sheetiss‰
const int TILE_SIZE = 32;	//tiilen koko pikselein‰(neliˆ), k‰ytet‰‰n position m‰‰ritt‰miseen

class Map	//alustaa ja piirt‰‰ kartan
{
private:
	SDL_Surface* terrainTiles;			//tiilien kuvat
	SDL_Rect gTileClips[TOTAL_TILES];	//tiilien kuvat pilkottuna

public:
	Map();
	~Map();

	void LoadImage(std::string imagename, SDL_Surface* screenSurface);	//lataa spritesheetin, eli tiilien kuvat
	void setTiles(Tile* tiles[]);										//asettaa kartan
};
