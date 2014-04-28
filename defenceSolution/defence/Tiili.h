<<<<<<< HEAD
#pragma once
#include "sprite.h"
#include "SDL.h"

class Tiili :
	public Sprite
{
private:
	bool isPassable;	//voiko tästä mennä vihulaiset ja/tai hero
	bool isBuildable;	//voiko tornin rakentaa tähän
	int tileType;
	SDL_Rect source;	//mikä osa sprite sheetistä piirretään
	
public:
	Tiili(void);
	virtual ~Tiili(void);
	void draw(SDL_Renderer* rndr);
	void draw(SDL_Renderer* rndr, SDL_Texture* texture);
	void update();
	void setType(int type);
	void setSourceRect(int w, int h, int x, int y);
	int getType();
	bool buildable();
	bool passable();
	void setBuildable(bool Buildable);
	void setPassable(bool Passable);
};

=======
#pragma once
#include "sprite.h"
#include "SDL.h"

class Tiili :
	public Sprite
{
private:
	bool isPassable;	//voiko tästä mennä vihulaiset ja/tai hero
	bool isBuildable;	//voiko tornin rakentaa tähän
	int tileType;
	SDL_Rect source;	//mikä osa sprite sheetistä piirretään
	
public:
	Tiili(void);
	virtual ~Tiili(void);
	void draw(SDL_Renderer* rndr);
	void draw(SDL_Renderer* rndr, SDL_Texture* texture);
	void update();
	void setType(int type);
	void setSourceRect(int w, int h, int x, int y);
	int getType();
	bool buildable();
	bool passable();
	void setBuildable(bool Buildable);
	void setPassable(bool Passable);
};

>>>>>>> origin/Mappi2
