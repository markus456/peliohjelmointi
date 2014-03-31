#ifndef GPARAM_G
#define GPARAM_G
/*
*Yleinen parametrilista pelin eri vaikeusasteille.
*Controller alustaa pelin näillä parametreilla.
*/
class GameParams{
private:
	unsigned int _enemies_per_wave, _enemies_allowed_through,_enemy_speed,_enemy_hp,_enemy_attack,_tower_limit;
public:
	static const unsigned int EASY = 1;
	static const unsigned int NORMAL = 2;
	static const unsigned int HARD = 3;
	GameParams(unsigned int difficulty = GameParams::NORMAL){
		switch(difficulty){
		case GameParams::EASY:
			_enemies_per_wave = 2;
			_enemies_allowed_through = 8;
			_enemy_speed = 2;
			_enemy_attack = 1;
			_enemy_hp = 2;
			_tower_limit = 15;
			break;
		case GameParams::NORMAL:
			_enemies_per_wave = 4;
			_enemies_allowed_through = 4;
			_enemy_speed = 4;
			_enemy_hp = 4;
			_enemy_attack = 2;
			_tower_limit = 8;
			break;
		case GameParams::HARD:
			_enemies_per_wave = 8;
			_enemies_allowed_through = 2;
			_enemy_speed = 6;
			_enemy_hp = 8;
			_enemy_attack = 4;
			_tower_limit = 4;
			break;
		}
	}
	unsigned int enemiesPerWave(){return _enemies_per_wave;}
	unsigned int enemiesAllowedThrough(){return _enemies_allowed_through;}
	unsigned int enemySpeed(){return _enemy_speed;}
	unsigned int towerLimit(){return _tower_limit;}
	unsigned int enemyHP(){return _enemy_hp;}
	unsigned int enemyAttack(){return _enemy_attack;}
};
#endif
