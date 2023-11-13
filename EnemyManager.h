#pragma once
#include <vector>
#include "AEnemy.h"

///
/// EnemyManager
/// 
/// Container class for Enemy actors
/// 
class EnemyManager
{
	std::vector<AEnemy*> enemyList;
	static EnemyManager* instance;
	EnemyManager();
public:
	static EnemyManager* getInstance() {
		if (instance == NULL)
		{
			instance = new EnemyManager();
		}
		return instance;
	}
	~EnemyManager();

	//Adds Enemy to Enemy list
	//Automatically will call update and render of that object
	void AddEnemy(AEnemy * _enemy) {
		enemyList.push_back(_enemy);
	};

	//Checks sent transform with every enemy and applies damage
	// if transform overlaps enemy
	bool Hit(LAZY::TRANSFORM _projectile, int _dmg);

	//Spawn of Enemies and set of their patrols
	void Init();

	//Update of all enemies
	void Update();

	//Render of all Enemies
	void Render();
};

