#include "Actor.h"
#include "ResourceManager.h"
#include "Video.h"
#include <iostream>
#include <time.h>
#include "Globals.h"
#include "../SceneGame.h"

#define DEBUG true
Actor::Actor()
{
	m_debug = false;
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 0;
	m_rect.h = 0;
	m_image = NULL;
	hasImage = false;
	m_angle = 0;
	canBeRendered = true;
	m_worldRect = { 0,0,0,0,0 };
}
Actor::~Actor()
{
}

int Actor::CreateActor(int p_x, int p_y, const char* file, bool isUI, bool crateGraphic, int w_x, int w_y, Uint8 r, Uint8 g, Uint8 b)
{
	if (isUI)
	{
		m_rect.x = p_x;
		m_rect.y = p_y;
	}
	else
	{
		m_worldRect.x = p_x;
		m_worldRect.y = p_y;
	}
	
	if (file != NULL && !crateGraphic)
	{
		m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
		if (m_image == -1)
		{
			m_image = ResourceManager::getInstance()->loadAndGetGraphicID(ResourceManager::getInstance()->getDefaultTetxure());
			hasImage = false;
		}
		else
		{
			hasImage = true;
		}
	}
	else
	{
		if (crateGraphic)
		{
			m_image = ResourceManager::getInstance()->createGraphic("Genereated-Actor-Graphic", w_x, w_y,r,g,b);
		}
		else
		{
			m_image = ResourceManager::getInstance()->loadAndGetGraphicID(ResourceManager::getInstance()->getDefaultTetxure());
		}
		hasImage = false;
	}
	if (crateGraphic)
	{
		m_rect.w = w_x;
		m_rect.h = w_y;
		m_worldRect.w = w_x;
		m_worldRect.h = w_y;
	}
	else
	{
		ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
		m_worldRect.w = m_rect.w;
		m_worldRect.h = m_rect.h;
	}
	return 0;
}
int Actor::CreateActor(LAZY::TRANSFORM transform, const char* file, bool crateGraphic, LAZY::COLOR rgb)
{
	CreateActor(transform.x, transform.y, file, false, crateGraphic,transform.w,transform.h,rgb.r,rgb.g,rgb.b);
	return 0;
}
int Actor::CreateCentredActorScale(int w, int h) {

	m_rect.w = w;
	m_rect.h = h;
	CenterActor();
	//Pick surface and passit to render scaled
	//m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
	//ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	//ResourceManager::getInstance()->printLoadedGraphics();
	return 0;
}
int Actor::CreateActorWithImage(const char* file)
{
	m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
	ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	ResourceManager::getInstance()->printLoadedGraphics();
	hasImage = true;
	return 0;
}
int Actor::GetLookingDirection()
{
	return 0;
}
void Actor::ChangeTransform(int p_x, int p_y, int p_sx, int p_sy)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = p_sx;
	m_rect.h = p_sy;
}

void Actor::CenterActor()
{
	m_rect.x = (SCREEN_WIDTH / 2) - m_rect.w / 2;
	m_rect.y = (SCREEN_HEIGHT / 2) - m_rect.h / 2;
}


void Actor::SetAlpha(int alpha)
{
	ResourceManager::getInstance()->setAlphaGraphic(m_image, alpha);
}

void Actor::StartPlay()
{
}

void Actor::Update()
{
	UpdateRelToCam();
	
}

void Actor::Render()
{
	if (canBeRendered)
	{
		Video::getInstance()->renderGraphic(m_image, m_rect.x, m_rect.y, m_rect.w, m_rect.h,m_angle,NULL,SDL_FLIP_NONE);
	}
}

void Actor::UpdateRelToCam()
{
	m_rect.x = m_worldRect.x - SceneGame::cam->GetX();
	m_rect.y = m_worldRect.y - SceneGame::cam->GetY();
}

int Actor::CheckIfOutOfBounds()
{
	if (m_rect.x < 0 || m_rect.y < 0 || m_rect.x + m_rect.w > GAMEPLAY_SCREEN_WIDTH || m_rect.y + m_rect.h > GAMEPLAY_SCREEN_HEIGHT)
	{
		return 1;
	}
	return 0;
}

void Actor::SetImage(const char* file) {
	CreateActorWithImage(file);
}