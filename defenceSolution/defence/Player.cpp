#include "Player.h"


Player::Player(void)
{
	_location.x=0;
	_location.y=0;
	_move_up = false;
	_move_down = false;
	_move_left = false;
	_move_right = false;
	_speedx = 0;
	_speedy = 0;
}


Player::~Player(void)
{
}

void Player::draw(SDL_Renderer* rndr)
{
	Location p(_location.w / 2, _location.h / 2);
	SDL_RenderCopyEx(rndr, _texture, nullptr, &_location.toSDL_Rect(), 0, &p.toSDL_Point(), SDL_FLIP_NONE);
}

void Player::update()
{
	_location.x += _speedx;
	_location.y += _speedy;
}

void Player::updateSpeed() {
	_speedx = 0;
	_speedy = 0;
	if (_move_up) {
		_speedy -= 1;
	}
	if (_move_down) {
		_speedy += 1;
	}
	if (_move_left) {
		_speedx -= 1;
	}
	if (_move_right) {
		_speedx += 1;
	}
}

void Player::setMoveUp(bool move) {
	_move_up = move;
	updateSpeed();
}

void Player::setMoveDown(bool move) {
	_move_down = move;
	updateSpeed();
}

void Player::setMoveLeft(bool move) {
	_move_left = move;
	updateSpeed();
}

void Player::setMoveRight(bool move) {
	_move_right = move;
	updateSpeed();
}