#include "Tiili.h"


Tiili::Tiili(void)
{
}


Tiili::~Tiili(void)
{
}

void Tiili::draw(SDL_Renderer* rndr)
{
	SDL_RenderCopy(rndr,_texture,nullptr,&_location.toSDL_Rect());
}

void Tiili::draw(SDL_Renderer* rndr, SDL_Texture* texture)
{
	SDL_RenderCopyEx(rndr, texture, &source, &_location.toSDL_Rect(), 0, NULL, SDL_FLIP_NONE);
}

void Tiili::update()
{

}

void Tiili::setType(int type)
{
	tileType = type;	//tiilen tyyppi, esim. 0-2 on maata vesi rajalla
	isBuildable=true;
	isPassable=true;

	//Tielle ja esim. veteen ei voi rakentaa, mutta tiellä voi kulkea
	if(tileType>=4 && tileType<=9){
		isBuildable = false;
		if(tileType==8 || tileType==9){ //nämä ovat tie tiiliä
			isPassable=true;
		}else{
			isPassable=false;
		}
	}else if(tileType==13){				//vettä
		isBuildable=false;
		isPassable=false;
	}
	else if(tileType>=15 && tileType<=19){ //nämä ovat tie tiiliä
		isBuildable = false;
		if(tileType==18 || tileType==19){
			isPassable=true;
		}else{
			isPassable=false;
		}
	}
	else if(tileType>=24 && tileType<=29){ //nämä ovat tie tiiliä
		isBuildable=false;
		if(tileType==28 || tileType==29 || tileType==24){
			isPassable=true;
		}else{
			isPassable=false;
		}
	}
	else{
		//isBuildable=true;
	}
}

void Tiili::setSourceRect(int w, int h, int x, int y)
{
	source.w = w;
	source.h = h;
	source.x = x;
	source.y = y;
}

int Tiili::getType()
{
	return tileType;
}
bool Tiili::buildable(){///Tilapäinen korjaus
	return isBuildable;
}
bool Tiili::passable(){//Tilapäinen korjaus
	return isPassable;
}
void Tiili::setBuildable(bool Buildable){
	isBuildable = Buildable;
}
void Tiili::setPassable(bool Passable){
	isPassable = Passable;
}


