#include "EnemyManager.h"
#include "SceneGame.h"
EnemyManager* EnemyManager::instance = NULL;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

bool EnemyManager::Hit(LAZY::TRANSFORM _projectile, int _dmg)
{
	SDL_Rect projectile = _projectile.ToSDL();
	bool whatReturn = false;
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		//Check if overlap
		SDL_Rect tempEnemyRect = enemyList.at(i)->GetWorldRect()->ToSDL();
		if (SDL_HasIntersection(&tempEnemyRect,&projectile))
		{
			enemyList.at(i)->Hit(_dmg);
 			whatReturn = true;
		}
	}
	return whatReturn;
}

void EnemyManager::Init()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		delete enemyList[i];
	}
	enemyList.resize(0);
	AEnemy* Enemy_1 = new AEnemy(9 * 8, 56 * 8, SceneGame::GetPlayer());
	Enemy_1->AddNewPatrolPoint({ 9 * 8, 56 * 8 });
	Enemy_1->AddNewPatrolPoint({ 6 * 8, 56 * 8 });
	Enemy_1->AddNewPatrolPoint({ 6 * 8, 60 * 8 });
	Enemy_1->AddNewPatrolPoint({ 24 * 8, 60 * 8 });
	Enemy_1->AddNewPatrolPoint({ 24 * 8, 56 * 8 });
	Enemy_1->AddNewPatrolPoint({ 20 * 8, 56 * 8 });
	Enemy_1->AddNewPatrolPoint({ 20 * 8, 60 * 8 });
	Enemy_1->AddNewPatrolPoint({ 9 * 8, 60 * 8 });
	Enemy_1->AddNewPatrolPoint({ 15 * 8, 110 * 8 });
	AddEnemy(Enemy_1);

	AEnemy* Enemy_2 = new AEnemy(7 * 8, 48 * 8, SceneGame::GetPlayer());
	Enemy_2->AddNewPatrolPoint({ 7 * 8, 48 * 8 });
	Enemy_2->AddNewPatrolPoint({ 23 * 8, 48 * 8 });
	Enemy_2->AddNewPatrolPoint({ 7 * 8, 48 * 8 });
	Enemy_2->AddNewPatrolPoint({ 23 * 8, 48 * 8 });
	AddEnemy(Enemy_2);

	AEnemy* Enemy_3 = new AEnemy(48 * 8, 88 * 8, SceneGame::GetPlayer());
	Enemy_3->AddNewPatrolPoint({ 48 * 8, 88 * 8 });
	Enemy_3->AddNewPatrolPoint({ 48 * 8, 76 * 8 });
	Enemy_3->AddNewPatrolPoint({ 38 * 8, 76 * 8 });
	Enemy_3->AddNewPatrolPoint({ 38 * 8, 88 * 8 });
	Enemy_3->AddNewPatrolPoint({ 38 * 8, 88 * 8 });
	AddEnemy(Enemy_3);

	AEnemy* Enemy_4 = new AEnemy(50 * 8, 88 * 8, SceneGame::GetPlayer());
	Enemy_4->AddNewPatrolPoint({ 50 * 8, 88 * 8 });
	Enemy_4->AddNewPatrolPoint({ 50 * 8, 76 * 8 });
	Enemy_4->AddNewPatrolPoint({ 60 * 8, 76 * 8 });
	Enemy_4->AddNewPatrolPoint({ 60 * 8, 88 * 8 });
	Enemy_4->AddNewPatrolPoint({ 60 * 8, 88 * 8 });
	AddEnemy(Enemy_4);


	AEnemy* Enemy_5 = new AEnemy(9 * 8, 36 * 8, SceneGame::GetPlayer());
	Enemy_5->AddNewPatrolPoint({ 9 * 8, 36 * 8 });
	Enemy_5->AddNewPatrolPoint({ 19 * 8, 36 * 8 });
	Enemy_5->AddNewPatrolPoint({ 20 * 8, 36 * 8 });
	AddEnemy(Enemy_5);

	AEnemy* Enemy_6 = new AEnemy(9 * 8, 28 * 8, SceneGame::GetPlayer());
	Enemy_6->AddNewPatrolPoint({ 9 * 8, 28 * 8 });
	Enemy_6->AddNewPatrolPoint({ 19 * 8, 28 * 8 });
	Enemy_6->AddNewPatrolPoint({ 20 * 8, 28 * 8 });
	AddEnemy(Enemy_6);

	AEnemy* Enemy_7 = new AEnemy(37 * 8, 9 * 8, SceneGame::GetPlayer());
	Enemy_7->AddNewPatrolPoint({ 37 * 8, 9 * 8 });
	Enemy_7->AddNewPatrolPoint({ 37 * 8, 4 * 8 });
	Enemy_7->AddNewPatrolPoint({ 49 * 8, 4 * 8 });
	Enemy_7->AddNewPatrolPoint({ 49 * 8, 19 * 8 });
	Enemy_7->AddNewPatrolPoint({ 37 * 8, 19 * 8 });
	Enemy_7->AddNewPatrolPoint({ 49 * 8, 19 * 8 });
	Enemy_7->AddNewPatrolPoint({ 49 * 8, 4 * 8 });
	Enemy_7->AddNewPatrolPoint({ 37 * 8, 4 * 8 });
	AddEnemy(Enemy_7);
}

void EnemyManager::Update()
{
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Update();
	}
}

void EnemyManager::Render()
{
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Render();
	}
}
