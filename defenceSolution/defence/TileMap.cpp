#include "TileMap.h"


TileMap::TileMap(void)
{
	srand (time(NULL));
}


TileMap::~TileMap(void)
{
}

// lis‰‰ vektoriin tiilet ja asettaa tiilien kuvat ja sijainnnin
void TileMap::addTiles()
{
	Tiili tile;
	SDL_Point location;
	SDL_Rect size;
	size.h = TILE_HEIGHT;
	size.w = TILE_WIDTH;

	int w = 0;
	int h = 0;
	int x = 0;
	int y = 0;

	for(y; y<MAP_HEIGHT; y++){
		x=0;
		for(x; x<MAP_WIDTH; x++){
			if(y <= MAP_HEIGHT){
				location.x = w;
				location.y = h;
				tile.setSize(size);			//tiilen koko
				tile.setLocation(location);	//tiilen sijainti
				tile.setType(typeMap[x+y*MAP_WIDTH]);
				tile.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, tile.getType() * TILE_WIDTH, 0);
				map.push_back(tile);		//lis‰ys vektoriin
				w += TILE_WIDTH;			//seuraava tiili leveyden verran oikealle
				//std::cout  << " x: " << x << " y: "<< y << "   taulussa on " << mapTemp[x][y] <<"\n";

				if(x == MAP_WIDTH-1){
					h += TILE_HEIGHT;		//tiilen sijainnit alemmalle riville
					w = 0;					//taas vasemmasta laidasta aloitus
				}//if
			}//if
		}//for x
	}//for y
}

void TileMap::drawMap()
{
	int x = 0;
	for(vector<Tiili>::iterator it = map.begin(); it != map.end(); ++it) {
		it->draw(rndr, tileTexture);
	}
}

void TileMap::setTexture(std::string filename, SDL_Renderer* rndr)
{
	SDL_Surface* tmp = IMG_Load(filename.c_str());
	if(tmp==0){
			//std::cout << "Error loading file: " << filename << std::endl;
			return;
	}
	tileTexture = SDL_CreateTextureFromSurface(rndr, tmp);
	SDL_FreeSurface(tmp);
}

void TileMap::setRenderer(SDL_Renderer* rendr)
{
	rndr = rendr;
}

void TileMap::setMap(std::string filename)
{
	std::ifstream mappi( filename.c_str() );

	int temp = 0;

    if(!mappi)
    {
		std::cout<<"Tiedosto ei avautunut \n";
    }
    while(!mappi.eof())
    {
		mappi >> temp;
		typeMap.push_back(temp);		//lis‰ys vektoriin
    }
	mappi.close();
	std::cout << "Tiedosto suljettu";
}
