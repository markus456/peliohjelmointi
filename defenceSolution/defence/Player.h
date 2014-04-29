#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "SDL_mixer.h"
#include <memory>

class Player : public Sprite {
public:
	Player(void);
	~Player(void);
	virtual void draw(SDL_Renderer* rndr);
	virtual void update();
	bool move(double speedx, double speedy);
	void updateSpeed();
	void setMoveUp(bool move);
	void setMoveDown(bool move);
	void setMoveLeft(bool move);
	void setMoveRight(bool move);
	void setMap(std::unique_ptr<TileMap>& map);
	bool collideTestWorldBounds();
	unsigned int getDamage();
	void setSpriteSize(Location l = Location(0,0,64,64));

private:
	double _speedx, _speedy;
	unsigned int _damage;
	Location render_size;
	bool _move_up, _move_down, _move_left, _move_right;
	std::unique_ptr<TileMap>* _map;
	Mix_Chunk* footstep;
};

