#pragma once
#include "Engine/Actor.h"
#include "Engine/ACharacter.h"
#include "AItem_Weapon.h"
#include <vector>
enum  EnemyType
{
	BASIC, SHOTMAKER, MACHINE_KID, HIND_D, _LAST_ENEMY_TYPE
};


class AEnemy : public Actor
{
public:
	enum EnemyStates
	{
		IDLE, ATTACK, UP, DOWN, RIGHT, LEFT, DEAD, GOTO_PLAYER, NO_STATE
	};

private:
	std::vector<LAZY::POINT> patrol;
	unsigned int currentPatrolIndex;
	unsigned int currentPatrolIndexPrevious;
	EnemyStates state;
	EnemyStates preState;
	bool flipFlop;
	bool isAlerted;
	//Var
	//-AMap <-- Per verure si estan alertats o no i a
	//on anar per perseguir el jugador

	int m_frame;
	int m_animtionRow;
	int m_a_animationTimer;
	int m_w_shootingTimer;
	int m_maxFrame;
	int m_hp;
	int m_range;

	int m_directions;
	ACharacter* playerREF;
	int directions[LAZY::DIRECTIONS::_LAST];

	AItem_Weapon* enemyWeapon;

public:
	AEnemy();
	AEnemy(int _x, int _y, ACharacter* _player = nullptr);
	~AEnemy();

	void Update();
	void UpdateState();
	void UpdateTimer();
	void UpdateAnimationFrame();

	//Checks location of player and moves Actor to 1 step to it in any direction
	void FollowPlayer();

	//Checks if player is in front of actor or close and return true
	bool CheckPlayerFromDirection();

	//Moves Actor to nearest available space
	void CheckWorldColision(int* directions);
	void Patrol();
	void Render() override;

	void AddNewPatrolPoint(LAZY::POINT _point) { patrol.push_back(_point); };

	bool IsOnScreen();
	void Hit(int _dmg);

	void Shoot();
};

