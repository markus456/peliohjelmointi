<<<<<<< HEAD
#pragma once
#include "Sprite.h"
#include "TileMap.h"

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

private:
	double _speedx, _speedy;
	unsigned int _damage;
	bool _move_up, _move_down, _move_left, _move_right;
	std::unique_ptr<TileMap>* _map;
};

=======
#pragma once
#include "Sprite.h"
#include "TileMap.h"

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

private:
	double _speedx, _speedy;
	unsigned int _damage;
	bool _move_up, _move_down, _move_left, _move_right;
	std::unique_ptr<TileMap>* _map;
};

>>>>>>> origin/Mappi2
