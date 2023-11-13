#include "AEnemy.h"
#include "Engine/Input.h"
#include "Engine/Video.h"
#include "Engine/MapManager.h"
#include <math.h>
AEnemy::AEnemy()
{
	state = IDLE;
	preState = DOWN;
	m_frame = 0;
	m_animtionRow = 0;
	m_a_animationTimer = 0;
	m_maxFrame = 3;
	m_hp = 100;
	flipFlop = false;
	isAlerted = false;
	patrol = std::vector<LAZY::POINT>();
	enemyWeapon = nullptr;
}

AEnemy::AEnemy(int _x, int _y, ACharacter* _player)
{
	patrol = std::vector<LAZY::POINT>();
	state = IDLE;
	preState = DOWN;
	m_frame = 0;
	m_animtionRow = 0;
	m_a_animationTimer = 0;
	m_maxFrame = 3;
	m_hp = 100;
	currentPatrolIndex = 0;
	currentPatrolIndexPrevious = 0;
	isAlerted = false;
	flipFlop = false;
	playerREF = _player;
	m_range = 40;
	LAZY::TRANSFORM rect = { _x, _y, 16, 32, 0 };
	CreateActor(rect, "./assets/img/enemies/EnemyBase128x128.png");
	m_rect.w = rect.w;
	m_rect.h = rect.h;
	m_worldRect.w = rect.w;
	m_worldRect.h = rect.h;
	m_directions = -1;
	enemyWeapon = new AItem_Weapon(this, { -200,-200,0,0,0 }, "EnemyWeapon", 0, 0, Handgun,5);
	enemyWeapon->SetObtained(true);
	for (int i = 0; i < LAZY::DIRECTIONS::_LAST; i++)
	{
		directions[i] = 0;
	}
}

AEnemy::~AEnemy()
{
}

void AEnemy::Update()
{
	if (m_hp <= 0)
	{
		return;
	}
	for (int i = 0; i < LAZY::DIRECTIONS::_LAST; i++)
	{
		directions[i] = 0;
	}

	/* 
		TODO CHECK IF OUT OF SHIGHT
	*/
	enemyWeapon->Update();
	UpdateTimer();
	UpdateRelToCam();
	if (IsOnScreen()) {
		//printf("ON SCREEN\n");
		if (flipFlop && state != DEAD)
		{
			flipFlop = false;
			UpdateState();
			if (CheckPlayerFromDirection())
			{
				isAlerted = true;
			}
			if (isAlerted)
			{
				FollowPlayer();
			}
			else
			{
				Patrol();
			}
		}
		else
		{
			flipFlop = true;
		}
	}
}

void AEnemy::UpdateState()
{
	switch (state)
	{
	case AEnemy::IDLE:
		state = GOTO_PLAYER;
		m_frame = 1;
		m_a_animationTimer = 0;
		break;
	case AEnemy::UP:
		m_animtionRow = 2;
		break;
	case AEnemy::DOWN:
		m_animtionRow = 0;
		break;
	case AEnemy::RIGHT:
		m_animtionRow = 3;
		break;
	case AEnemy::LEFT:
		m_animtionRow = 1;
		break;
	default:
		break;
	}
}

void AEnemy::UpdateTimer()
{
	m_a_animationTimer += Video::getInstance()->GetDeltaTime();
	m_w_shootingTimer += Video::getInstance()->GetDeltaTime();
	
	if (m_a_animationTimer > 200)
	{
		m_frame++;
		if (m_frame >= m_maxFrame)//Frames per animation
		{
				m_frame = 0;
		}
		m_a_animationTimer = 0;
	}
}

void AEnemy::UpdateAnimationFrame()
{
}

void AEnemy::FollowPlayer()
{
	LAZY::POINT currentLocation = { m_worldRect.x, m_worldRect.y };
	LAZY::POINT playerLocation = { playerREF->GetX(), playerREF->GetY() };

	if ((int)LAZY::POINT::Distance(currentLocation,playerLocation) <=20 && (int)LAZY::POINT::Distance(currentLocation, playerLocation) >= -20)
	{
		state = ATTACK;
		return;
	}
	LAZY::POINT diff = LAZY::POINT::Difference(currentLocation, playerLocation);
	bool insideRange = abs(diff.y) <= 30 && abs(diff.x) <= 30;
	state = IDLE;
	if (currentLocation.y < playerLocation.y)
	{
		if (!insideRange)
		{
			state = DOWN;
			m_worldRect.y++;
			directions[LAZY::DIRECTIONS::DOWN] = 1;
			m_directions = 0;
		}
	}
	else if (currentLocation.y > playerLocation.y)
	{
		if (!insideRange)
		{
			state = UP;
			m_worldRect.y--;
			directions[LAZY::DIRECTIONS::UP] = 1;
			m_directions = 2;
		}
	}
	if (currentLocation.x < playerLocation.x)
	{
		if (!insideRange)
		{
			state = RIGHT;
			m_worldRect.x++;
			directions[LAZY::DIRECTIONS::RIGHT] = 1;
			m_directions = 3;
		}
	}
	else if (currentLocation.x > playerLocation.x)
	{
		if (!insideRange)
		{
			state = LEFT;
			m_worldRect.x--;
			directions[LAZY::DIRECTIONS::LEFT] = 1;
			m_directions = 1;
		}
	}
	if (insideRange)
	{
		directions[LAZY::DIRECTIONS::CENTER] = 1;
		Shoot();
	}
	CheckWorldColision(directions);

}

bool AEnemy::CheckPlayerFromDirection()
{
	//From State check if player is in front
	LAZY::POINT currentLocation = { m_worldRect.x, m_worldRect.y };
	LAZY::POINT playerLocation = { playerREF->GetX(), playerREF->GetY() };
	if ((LAZY::POINT::Distance(playerLocation, currentLocation)) <= m_range)
	{
		//printf("%f \n", LAZY::POINT::Distance(playerLocation, currentLocation));
		LAZY::POINT difference = LAZY::POINT::Difference(playerLocation, currentLocation);
		if (abs(difference.x) <= m_range && abs(difference.y) <= m_range)
		{
			return true;
		}
		 /*switch (state)
		{
		case AEnemy::IDLE:
			break;
		case AEnemy::UP:
			if (difference.y <= m_range)
			{
				return true;
			}
			break;
		case AEnemy::DOWN:
			if (difference.y*-1 <= m_range)
			{
				return true;
			}
			break;
		case AEnemy::RIGHT:
			if (difference.x <= m_range)
			{
				return true;
			}
			break;
		case AEnemy::LEFT:
			if (difference.x * -1 <= m_range)
			{
				return true;
			}
			break;
		default:
			break;
		}
		 */
	}
	return false;
}

void AEnemy::CheckWorldColision(int* directions)
{	
	bool validPos = false;
	AMap* CurrentMap = MapManager::getInstance()->GetCurrentMapPointer();
	while (!validPos)
	{

		if (directions[LAZY::DIRECTIONS::LEFT])
		{
			if (CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + 6) > 0
				||
				CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + m_rect.h - 4) > 0
				)
			{
				m_worldRect.x += 1;
			}
			else
			{
				validPos = true;
			}
		}
		if (directions[LAZY::DIRECTIONS::RIGHT])
		{
			if (CurrentMap->GetTileFromMap(1, m_worldRect.x + m_rect.w - 4, m_worldRect.y + 6) > 0
				||
				CurrentMap->GetTileFromMap(1, m_worldRect.x + m_rect.w - 4, m_worldRect.y + m_rect.h - 4) > 0
				)
			{
				m_worldRect.x -= 1;
			}
			else
			{
				validPos = true;
			}
		}
		if (directions[LAZY::DIRECTIONS::UP])
		{
			if (CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + 4) > 0
				||
				CurrentMap->GetTileFromMap(1, m_worldRect.x + m_rect.w - 4, m_worldRect.y + 4) > 0
				)
			{
				m_worldRect.y += 1;
			}
			else
			{
				validPos = true;
			}
		}
		if (directions[LAZY::DIRECTIONS::DOWN])
		{
			if (CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + m_rect.h - 2) > 0
				||
				CurrentMap->GetTileFromMap(1, m_worldRect.x + m_rect.w - 4, m_worldRect.y + m_rect.h - 2) > 0
				)
			{
				m_worldRect.y -= 1;
			}
			else
			{
				validPos = true;
			}
		}
		if (directions[LAZY::DIRECTIONS::CENTER])
		{
			validPos = true;
		}
	}
}

void AEnemy::Patrol()
{
	LAZY::POINT currentLocation = { m_worldRect.x, m_worldRect.y };
	if (patrol.size() - 1 == currentPatrolIndex)
	{
		currentPatrolIndex = 0;
	}
	if (LAZY::POINT::Equals(currentLocation, patrol[currentPatrolIndex]) )
	{
		currentPatrolIndex++;
	}
	else
	{
		if (currentLocation.y < patrol[currentPatrolIndex].y)
		{
			m_worldRect.y++;
			state = DOWN;
			directions[LAZY::DIRECTIONS::DOWN] = 1;
			m_directions = 0;

		}
		else if (currentLocation.y > patrol[currentPatrolIndex].y)
		{
			m_worldRect.y--;
			state = UP;
			directions[LAZY::DIRECTIONS::UP] = 1;
			m_directions = 2;

		}
		if (currentLocation.x < patrol[currentPatrolIndex].x)
		{
			m_worldRect.x++;
			state = RIGHT;
			directions[LAZY::DIRECTIONS::RIGHT] = 1;
			m_directions = 3;

		}
		else if (currentLocation.x > patrol[currentPatrolIndex].x)
		{
			m_worldRect.x--;
			state = LEFT;
			directions[LAZY::DIRECTIONS::LEFT] = 1;
			m_directions = 1;

		}
	}
	LAZY::POINT UpdatedLocation = { m_worldRect.x, m_worldRect.y };
	if (LAZY::POINT::Equals(currentLocation, UpdatedLocation))
	{
		directions[LAZY::DIRECTIONS::CENTER] = 1;
	}
	CheckWorldColision(directions);

}

void AEnemy::Render()
{
	if (IsOnScreen() && m_hp > 0)
	{
		Video::getInstance()->renderGraphic(m_image, m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.w * m_frame, m_rect.h * m_animtionRow);
		enemyWeapon->Render();
	}
}

//TODO: NOT WORKY
bool AEnemy::IsOnScreen()
{
	SDL_Rect _rect = MapManager::getInstance()->GetCurrentMapPointer()->GetCamera()->GetTransform()->ToSDL();
	bool returned = SDL_HasIntersection(&m_rect, &_rect);
	return true; // Not working :<
	return returned;
}

void AEnemy::Hit(int _dmg)
{
 	m_hp -= _dmg;
	isAlerted = true;
}

void AEnemy::Shoot()
{
	//spawn bullet from direction and check timers
	//0 = DOWN 1=LEFT 2=UP 3=RIGHT
	if (m_w_shootingTimer > 300)
	{
		enemyWeapon->AddBullet(m_directions);
		m_w_shootingTimer = 0;
	}
	
}
