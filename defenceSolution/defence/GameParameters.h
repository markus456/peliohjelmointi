#ifndef GPARAM_G
#define GPARAM_G
/*
*Yleinen parametrilista pelin eri vaikeusasteille.
*Controller alustaa pelin näillä parametreilla.
*/
class GameParams{
private:
	unsigned int _enemies_per_wave, _enemies_allowed_through,_enemy_speed,_enemy_hp,_enemy_attack,_tower_limit,_total_enemies,_spawn_delay,_wave_delay,_difficulty;
public:
	static const unsigned int EASY = 1;
	static const unsigned int NORMAL = 2;
	static const unsigned int HARD = 3;
	GameParams(unsigned int difficulty = GameParams::NORMAL){
		_difficulty = difficulty;
		switch(difficulty){
		case GameParams::EASY:
			_spawn_delay = 650;
			_total_enemies = 80;
			_enemies_per_wave = 30;
			_enemies_allowed_through = 8;
			_enemy_speed = 1;
			_enemy_attack = 1;
			_enemy_hp = 100;
			_tower_limit = 15;
			_wave_delay = 5*1000;
			break;
		case GameParams::NORMAL:
			_spawn_delay = 300;
			_total_enemies = 160;
			_enemies_per_wave = 45;
			_enemies_allowed_through = 4;
			_enemy_speed = 3;
			_enemy_hp = 140;
			_enemy_attack = 2;
			_tower_limit = 12;
			_wave_delay = 5*1000;
			break;
		case GameParams::HARD:
			_spawn_delay = 150;
			_total_enemies = 320;
			_enemies_per_wave = 60;
			_enemies_allowed_through = 2;
			_enemy_speed = 4;
			_enemy_hp = 180;
			_enemy_attack = 4;
			_tower_limit = 8;
			_wave_delay = 5*1000;
			break;
		}
	}
	unsigned int enemiesPerWave(){return _enemies_per_wave;}
	unsigned int enemiesAllowedThrough(){return _enemies_allowed_through;}
	unsigned int enemySpeed(){return _enemy_speed;}
	unsigned int towerLimit(){return _tower_limit;}
	unsigned int enemyHP(){return _enemy_hp;}
	unsigned int enemyAttack(){return _enemy_attack;}
	unsigned int totalEnemies(){return _total_enemies;}
	unsigned int spawnDelay(){return _spawn_delay;}
	unsigned int waveDelay(){return _wave_delay;}
	unsigned int difficulty(){return _difficulty;}
	void advance(){
		_enemy_hp++;
		_tower_limit += 5;
		if(_wave_delay - 1000>0){
			_wave_delay -= 1000;
		}
		_enemy_speed++;
		_enemies_per_wave += 5;
	}
};
#endif
