#include "ACharacter.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Input.h"
#include "Globals.h"
#include "SoundManager.h"
#include "../SceneGame.h"
#include "SceneDirector.h"
#include "MapManager.h"
#include "../AItem_Weapon.h"
#include "GameData.h"
ACharacter::ACharacter()
{
	m_applyMovement = false;
	m_debug = TRUE;
	m_frame = 0;
	m_frameH = 0;
	m_state = IDLE;
	m_velocity = 1;
	m_animtionRow = 0;
	m_a_animationTimer = 0;
	m_weaponInHand = true;
	m_maxFrame = 3;
	m_hp = 100; 
	SDL_Rect t_transform_UI_Health = { 50, SCREEN_HEIGHT -18, 48, 6 };
	SDL_Color t_color_UI_Health = { 255,0,0 };
	alreadyPunching = false;
	UIhpVar = nullptr;
	UIhpVar = new UIProggressBar({ 50,(GAMEPLAY_SCREEN_HEIGHT + 2),48,6 }, {255,0,0}); 

	UIBg = nullptr;
	UIBg = new Actor();
	UIBg->CreateActor(0, GAMEPLAY_SCREEN_HEIGHT, "./assets/img/ui/BotUI.png", true);
}

ACharacter::~ACharacter()
{
}
void ACharacter::Init()
{
	AItem_Weapon* temp = new AItem_Weapon(this, LAZY::TRANSFORM{ 8 * 8 + 20,640,16 * 2,16,0 }, "Disarmed", 4, 4, Melee);
	temp->ToggleNotification();
	GameData::getInstance()->AddItem(temp);

}

void ACharacter::SetSpriteSize(int w, int h)
{
	m_rect.w = w;
	m_rect.h = h;
	m_worldRect.w = w;
	m_worldRect.h = h;
}


void ACharacter::Update()
{
	if (m_hp <= 0 || Input::getInstance()->keyboard.KB_SEMICOLON)
	{
		SoundManager::getInstance()->haltSound();
		SceneDirector::getInstance()->changeScene(GAMEOVER, true,true);
	}
	int directions[LAZY::DIRECTIONS::_LAST] = { 0,0,0,0,0 };
	if (SceneGame::gameResume)
	{

		m_applyMovement = !m_applyMovement;
		if (m_applyMovement)
		{
			if (Input::getInstance()->keyboard.KB_SPACE && !alreadyPunching)
			{
				alreadyPunching = true;
				m_subState = ATTACK;
				dynamic_cast<AItem_Weapon*>(GameData::getInstance()->GetCurrentWeaponRef())->Fire();
				m_weaponInHand = GameData::getInstance()->GetCurrentWeapon() > 0;
				if (!m_weaponInHand)
				{
					SoundManager::getInstance()->playSound(
						SoundManager::getInstance()->getSoundByID(
							SoundManager::getInstance()->loadAndGetSoundID("./assets/sound/mg1_se15_punch1.ogg")));
				}
			}
			else if (!Input::getInstance()->keyboard.KB_SPACE)
			{
				alreadyPunching = false;
			}

			if (Input::getInstance()->GetInputDirectionsPlayer1()->right == 0)
			{
				m_state = IDLE;
			}
			if (Input::getInstance()->GetInputDirectionsPlayer1()->down <= -0.1)
			{
				m_state = UP;
				directions[LAZY::DIRECTIONS::UP] = 1;
				CheckColisionWithWorld(directions);
			}
			if (Input::getInstance()->GetInputDirectionsPlayer1()->down >= 0.1)
			{
				m_state = DOWN;
				directions[LAZY::DIRECTIONS::DOWN] = 1;
				CheckColisionWithWorld(directions);
			}


			m_worldRect.y += (int)(Input::getInstance()->GetInputDirectionsPlayer1()->down * m_velocity);
			if (m_subState != STAIRS)
			{
				m_worldRect.x += (int)(Input::getInstance()->GetInputDirectionsPlayer1()->right * m_velocity);

				if (Input::getInstance()->GetInputDirectionsPlayer1()->right <= -0.1)
				{
					m_state = LEFT;
					directions[LAZY::DIRECTIONS::LEFT] = 1;
					CheckColisionWithWorld(directions);

				}
				if (Input::getInstance()->GetInputDirectionsPlayer1()->right >= 0.1)
				{
					m_state = RIGHT;
					directions[LAZY::DIRECTIONS::RIGHT] = 1;
					CheckColisionWithWorld(directions);

				}
			}
			ChangeAnimationFrame();
		}
		if (Input::getInstance()->keyboard.KB_F4)
		{
			SceneDirector::getInstance()->changeScene(TRANSCRIBER, true);
		}
		if (Input::getInstance()->keyboard.KB_F3)
		{
			SceneDirector::getInstance()->changeScene(EQUIPMENT, true);
		}
		if (Input::getInstance()->keyboard.KB_F2)
		{
			SceneDirector::getInstance()->changeScene(INVENTORY, true);
		}
		m_rect.x = m_worldRect.x - SceneGame::cam->GetX();
		m_rect.y = m_worldRect.y - SceneGame::cam->GetY();


		//Do checks of animations bools in case of weapon in hands
		m_weaponInHand = GameData::getInstance()->GetCurrentWeapon() > 0;
	}

	GameData::getInstance()->GetCurrentWeaponRef()->Update();
}

void ACharacter::CheckColisionWithWorld(int * directions)
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
			if (CurrentMap->GetTileFromMap(1, m_worldRect.x + 4, m_worldRect.y + m_rect.h -2) > 0
				||
				CurrentMap->GetTileFromMap(1, m_worldRect.x + m_rect.w - 4, m_worldRect.y + m_rect.h -2) > 0
				)
			{
				m_worldRect.y -= 1;
			}
			else
			{
				validPos = true;
			}
		}
	}
}

void ACharacter::ChangeAnimationFrame()
{

	//Timer
	m_a_animationTimer += Video::getInstance()->GetDeltaTime();
	m_a_animationTimerStairs += Video::getInstance()->GetDeltaTime();
	if (m_a_animationTimer > 200 && (m_subState != ATTACK))
	{
		m_frame++;
		if (m_frame >= m_maxFrame)//Frames per animation
		{
			if (m_weaponInHand)
			{
				m_frame = 3;
			}
			else
			{
				m_frame = 0;
			}
				
		}
		m_a_animationTimer = 0;
	}
	if (m_a_animationTimerStairs > 200)
	{
		m_frameH++;
		if (m_frameH >= m_maxFrame)//Frames per animation
		{
			m_frameH = 0;
		}
		m_a_animationTimerStairs = 0;
	}

	
	switch (m_state)
	{
	case IDLE:
		if (m_weaponInHand)
		{
			m_frame = 3;
		}
		else
		{
			m_frame = 0;
		}
		break;
	case CUTSCENE:
		break;
	case LEFT:
		m_animtionRow = 1;
		if (m_weaponInHand)
		{
			m_maxFrame = 6;
		}
		else
		{
			m_maxFrame = 3;
		}
		break;
	case RIGHT:
		m_animtionRow = 3;
		if (m_weaponInHand)
		{
			m_maxFrame = 6;
		}
		else
		{
			m_maxFrame = 3;
		}
		break;
	case UP:
		if (m_subState == STAIRS)
		{
			if (m_frameH == 0)
			{
				m_animtionRow = 1;
			}
			if (m_frameH >= 1)
			{
				m_animtionRow = 0;
			}		
		}
		else
		{
			m_animtionRow = 2;
			if (m_weaponInHand)
			{
				m_maxFrame = 6;
			}
			else
			{
				m_maxFrame = 3;
			}

		}
		break;
	case DOWN:
		if (m_subState == STAIRS)
		{
			if (m_frameH == 0)
			{
				m_animtionRow = 1;
			}
			if (m_frameH >= 1)
			{
				m_animtionRow = 0;
			}
		}
		else
		{
			m_animtionRow = 0;
			if (m_weaponInHand)
			{
				m_maxFrame = 6;
			}
			else
			{
				m_maxFrame = 3;
			}
		}
		break;
	default:
		break;
	}

	switch (m_subState)
	{
	case STAIRS:
		m_frame = 7;
		m_maxFrame = 2;
		break;
	case ATTACK:
		if (m_weaponInHand == false)
		{
			// horizontal * 3
			m_frame = 6;

		}
		m_subState = NOTATTACK;
		break;
	case NOTATTACK:
		break;
	default:
		break;
	}
}


void ACharacter::Render()
{
	Video::getInstance()->renderGraphic(m_image,m_rect.x,m_rect.y,m_rect.w,m_rect.h,m_rect.w * m_frame,m_rect.h * m_animtionRow);
	if (m_debug)
	{
		//PRINT_PLAYER_CENTER
		//printf("World: %d :: %d\n", m_worldRect.x, m_worldRect.y);
	}
}

void ACharacter::RenderUI()
{	
	UIBg->Render();
	UIhpVar->Render();
}

int ACharacter::CheckOuterColison()
{
	if (m_rect.x + m_rect.w > GAMEPLAY_SCREEN_WIDTH)
	{
		m_rect.x = (GAMEPLAY_SCREEN_WIDTH - m_rect.w);
	}
	if (m_rect.x < 0)
	{
		m_rect.x = 0;
	}
	if (m_rect.y + m_rect.h > GAMEPLAY_SCREEN_HEIGHT)
	{
		m_rect.y = (GAMEPLAY_SCREEN_HEIGHT - m_rect.h);
	}
	if (m_rect.y < -8)
	{
		m_rect.y = 0;
	}
	return 0;
}

