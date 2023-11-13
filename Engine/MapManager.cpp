#include "MapManager.h"
#include "AMapSwitcher.h"
#include "../AItem_Weapon.h"
#include "../AEnemy.h"
MapManager* MapManager::instance = NULL;

MapManager::MapManager()
{
	m_image = -1;
	m_currentMap = 0;
	mapList = std::vector<AMap*>();
}
MapManager::MapManager(const char* tileset, ACharacter* pref)
{
	playerREF = pref;
	m_image = -1;
	m_currentMap = 0;
	m_image = ResourceManager::getInstance()->loadAndGetGraphicID(tileset);
	mapList = std::vector<AMap*>();
}

MapManager::~MapManager()
{
}

void MapManager::Init(Camera* _cam)
{

	AMap* temporalMap = new AMap("./assets/maps/B1-Floor1.tmx", m_image, _cam);
	mapList.push_back(temporalMap);
	
	AMapSwitcher* SWITCH_1_TO_5 = new AMapSwitcher(playerREF,
		LAZY::DIRECTIONS::UP,
		LAZY::TRANSFORM{ 8 * 6, 8 * 23, 8 * 16, 8 * 1, 0 },
		true);
	temporalMap->AddActor(SWITCH_1_TO_5);
	
	AMapSwitcher* SWITCH_1_TO_2 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::LEFT,
		LAZY::TRANSFORM{ 8 * 31, 8 * 4, 8, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_1_TO_2);

	AMapSwitcher* SWITCH_2_TO_1 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::RIGHT,
		LAZY::TRANSFORM{ 8 * 32, 8 * 4, 8, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_2_TO_1);

	AMapSwitcher* SWITCH_5_TO_1 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::DOWN,
		LAZY::TRANSFORM{ 8 * 6, 8 * 24, 8 * 16, 8 * 1, 0 },
		true);
	temporalMap->AddActor(SWITCH_5_TO_1);

	AMapSwitcher* SWITCH_5_TO_9 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::UP,
		LAZY::TRANSFORM{ 8 * 6, 8 * 47, 8 * 20, 8 * 1, 0 }, 
		true);
	temporalMap->AddActor(SWITCH_5_TO_9);

	AMapSwitcher* SWITCH_9_TO_5 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::DOWN,
		LAZY::TRANSFORM{ 8 * 6, 8 * 48, 8 * 20, 8 * 1, 0 }, 
		true);
	temporalMap->AddActor(SWITCH_9_TO_5);
	
	AMapSwitcher* SWITCH_9_TO_13 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::UP,
		LAZY::TRANSFORM{ 0, 8 * 71, 8 * 28, 8 * 1, 0 }, 
		true);
	temporalMap->AddActor(SWITCH_9_TO_13);
	
	AMapSwitcher* SWITCH_13_TO_9 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::DOWN,
		LAZY::TRANSFORM{ 0, 8 * 72, 8 * 28, 8 * 1, 0 },
		true);
	temporalMap->AddActor(SWITCH_13_TO_9);

	AMapSwitcher* SWITCH_13_TO_14 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::LEFT,
		LAZY::TRANSFORM{ 8 * 31, 8 * 88, 8 * 1, 8 * 7, 0 },
		true);
	temporalMap->AddActor(SWITCH_13_TO_14);

	AMapSwitcher* SWITCH_14_TO_13 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::RIGHT,
		LAZY::TRANSFORM{ 8 * 32, 8 * 88, 8 * 1, 8 * 7, 0 },
		true);
	temporalMap->AddActor(SWITCH_14_TO_13);

	AMapSwitcher* SWITCH_13_TO_17 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::UP,
		LAZY::TRANSFORM{ 8 * 12, (8 * 95) + 2, 8 * 8, 6, 0 }, 
		true);
	temporalMap->AddActor(SWITCH_13_TO_17);

	AMapSwitcher* SWITCH_17_TO_13 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::DOWN,
		LAZY::TRANSFORM{ 8 * 12, 8 * 96, 8 * 8, 6, 0 }, 
		true);
	temporalMap->AddActor(SWITCH_17_TO_13);


	AMapSwitcher* SWITCH_15_TO_14 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::LEFT,
		LAZY::TRANSFORM{ 8 * 63, 8 * 76, 8 * 1, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_15_TO_14);

	AMapSwitcher* SWITCH_14_TO_15 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::RIGHT,
		LAZY::TRANSFORM{ 8 * 64, 8 * 76, 8 * 1, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_14_TO_15);

	AMapSwitcher* SWITCH_3_TO_2 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::LEFT,
		LAZY::TRANSFORM{ 8 * 62, 8 * 14, 8 * 1, 8 * 4, 0 },
		true);
	temporalMap->AddActor(SWITCH_3_TO_2);

	AMapSwitcher* SWITCH_2_TO_3 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::RIGHT,
		LAZY::TRANSFORM{ 8 * 65, 8 * 14, 8 * 1, 8 * 4, 0 },
		true);
	temporalMap->AddActor(SWITCH_2_TO_3);

	AMapSwitcher* SWITCH_3_TO_4 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::LEFT,
		LAZY::TRANSFORM{ 8 * 95, 8 * 4, 8 * 1, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_3_TO_4);

	AMapSwitcher* SWITCH_4_TO_3 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::RIGHT,
		LAZY::TRANSFORM{ 8 * 96, 8 * 4, 8 * 1, 8 * 19, 0 },
		true);
	temporalMap->AddActor(SWITCH_4_TO_3);

	AMapSwitcher* SWITCH_4_TO_8 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::UP,
		LAZY::TRANSFORM{ 8 * 106, 8 * 23, 8 * 12, 8 * 1, 0 },
		true);	
	temporalMap->AddActor(SWITCH_4_TO_8);

	AMapSwitcher* SWITCH_8_TO_4 = new AMapSwitcher(
		playerREF,
		LAZY::DIRECTIONS::DOWN,
		LAZY::TRANSFORM{ 8 * 106, 8 * 24, 8 * 12, 8 * 1, 0 },
		true);
	temporalMap->AddActor(SWITCH_8_TO_4);


	//Items Map 1

	temporalMap->AddActor(new AItem(playerREF, LAZY::TRANSFORM{ 8 *8+20,105*8,16,16,0 }, "Cigarattes", ITEM_TYPE::UTILITY));
	temporalMap->AddActor(new AItem_Weapon(playerREF, LAZY::TRANSFORM{ 8 * 37, 8 * 16, 16 * 2,16,0 }, "Pistol", 0, 3, Weapon_Behaviour::Handgun));
}

void MapManager::Update()
{
	mapList[m_currentMap]->Update();
}

void MapManager::Render()
{
	mapList[m_currentMap]->Render();
}
