#include "TileMap.h"


TileMap::TileMap(void)
{
	srand (time(NULL));
	setMap("level1temp.txt");
	addTiles();
	typeMap.clear();
	setMap("roadmap.txt");
	addRoads();
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
				if(tile.getType() <= 10){			//ylimm‰t tiilet kuvassa
					tile.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, tile.getType() * TILE_WIDTH, 0);
				}else if(tile.getType() <= 20){		//seuraavan rivin tiilet
					tile.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, (tile.getType()-11) * TILE_WIDTH, 32);
				}else if(tile.getType() <= 30){		//seuraavan rivin tiilet
					tile.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, (tile.getType()-21) * TILE_WIDTH, 64);
				}
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

//tiekartan teko
void TileMap::addRoads(){
	Road road;
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
				road.setSize(size);			//tiilen koko
				road.setLocation(location);	//tiilen sijainti
				road.setType(typeMap[x+y*MAP_WIDTH]);

				for(auto& a:map){			//laittaa maastokarttaan oikeat flagit, eli tielle ei voi rakentaa, mutta voi kulkea
					if(&a.getLocation()==&road.getLocation()){
						a.setBuildable(false);
						a.setPassable(true);
					}
				}
				
				if(road.getType() >=  8 && road.getType() <= 10){			//ylimm‰t tiilet kuvassa
					road.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, road.getType() * TILE_WIDTH, 0);
					roadmap.push_back(road);		//lis‰ys vektoriin
				}else if(road.getType() >= 18 && road.getType() <= 20){		//seuraavan rivin tiilet
					road.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, (road.getType()-11) * TILE_WIDTH, 32);
					roadmap.push_back(road);		//lis‰ys vektoriin
				}else if(road.getType() >= 28 && road.getType() <= 30){		//seuraavan rivin tiilet
					road.setSourceRect(TILE_WIDTH -1, TILE_HEIGHT -1, (road.getType()-21) * TILE_WIDTH, 64);
					roadmap.push_back(road);		//lis‰ys vektoriin
				}
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
	for(auto& a: map) {
		a.draw(rndr, tileTexture);
	}
	for(auto& a:roadmap) {
		a.draw(rndr, tileTexture);
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
		std:: cout << temp;
		typeMap.push_back(temp);		//lis‰ys vektoriin
    }
	mappi.close();
	std::cout << "Tiedosto suljettu";
}
std::vector<Tiili>& TileMap::getMap(){
	return map;
}
std::vector<Road>& TileMap::getRoad(){
	return roadmap;
}