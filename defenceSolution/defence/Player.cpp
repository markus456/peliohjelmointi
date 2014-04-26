#include "Player.h"
#include "System.h"


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
	_damage = 10;
	footstep = Mix_LoadWAV("sfx/footstep.wav");
}


Player::~Player(void)
{
}

void Player::draw(SDL_Renderer* rndr)
{
	Location p(_location.w / 2, _location.h / 2);
	SDL_Rect r = _location.toSDL_Rect();
	SDL_Point po = p.toSDL_Point();
	SDL_RenderCopyEx(rndr, _texture, nullptr, &r, 0, &po, SDL_FLIP_NONE);
}

void Player::update() {
	if (!move(_speedx, _speedy)) {
		if (!move(_speedx, 0)) {
			move(0, _speedy);
		}
	}
}

bool Player::move(double speedx, double speedy) {
	if(speedx!=0||speedy!=0)
		Mix_PlayChannel(-1,footstep,0);
	_location.x += speedx;
	_location.y += speedy;

	if (collideTestWorldBounds()) {
		//return back to original place
		_location.x -= speedx;
		_location.y -= speedy;
		return false;
	}
	
	for (Tiili &tiili : _map->get()->getMap()) {
		if (!tiili.passable()) {
			if (collideTest(tiili)) {
				//return back to original place
				_location.x -= speedx;
				_location.y -= speedy;
				return false;
			}
		}
	}
	
	return true;
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

void Player::setMap(std::unique_ptr<TileMap>& map) {
	_map = &map;
}

bool Player::collideTestWorldBounds() {
	return !(_location.w + _location.x < System::SCREEN_WIDTH && _location.h + _location.y < System::SCREEN_HEIGHT &&
		_location.x > 0 && _location.y > 0);
}

unsigned int Player::getDamage() {
	return _damage;
}