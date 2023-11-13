#include "ABullet.h"
#include "EnemyManager.h"
#include "Engine/Video.h"
#include "SceneGame.h"

ABullet::ABullet(bool _isfriendly,LAZY::TRANSFORM _transform, int _proj_direction, int _speed, int _dmg)
{
	isFriendly = _isfriendly;
	requestDelete = false;
	dmg = _dmg;
	velocity = _speed;
	direction = _proj_direction;
	CreateActor(_transform, BULLET_GX_PATH);
	m_a_animationTimer = 0;

}

ABullet::~ABullet()
{
}

void ABullet::Update()
{
	if (requestDelete)
	{
		return;
	}
	Actor::Update();
	//0 = DOWN 1=LEFT 2=UP 3=RIGHT
	switch (direction)
	{
	case 0:
		m_worldRect.y += velocity;
		break;
	case 1:
		m_worldRect.x -= velocity;
		break;
	case 2:
		m_worldRect.y -= velocity;
		break;
	case 3:
		m_worldRect.x += velocity;
		break;
	default:
		break;
	}


	AMap* CurrentMap = MapManager::getInstance()->GetCurrentMapPointer();
	if (CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + 6) > 0
		||
		CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + m_rect.h - 4) > 0
		)
	{
		requestDelete = true;
		return;
	}


	if (isFriendly)
	{
		if (EnemyManager::getInstance()->Hit(m_worldRect, dmg))
		{
			requestDelete = true;
		}
	}
	else
	{
		SDL_Rect playerRect = SceneGame::GetPlayer()->GetWorldRect()->ToSDL();
		SDL_Rect bulletRect = GetWorldRect()->ToSDL();
		if (SDL_HasIntersection(&playerRect, &bulletRect))
		{
			SceneGame::GetPlayer()->ReduceHP(dmg);
			requestDelete = true;
		}
	}
	
	
	m_a_animationTimer += Video::getInstance()->GetDeltaTime();
	if (m_a_animationTimer > 2000)
	{
		requestDelete = true;
	}
}

void ABullet::Render()
{
	if (requestDelete)
	{
		return;
	}
	Actor::Render();
}
