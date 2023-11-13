#pragma once

#include "AMap.h"
#include "ACharacter.h"
#include "ResourceManager.h"

#include <vector>

class MapManager
{
	ACharacter* playerREF;
	std::vector <AMap*> mapList;
	int m_image;
	int m_currentMap;

	static MapManager* instance;

	MapManager();
	MapManager(const char* tileset, ACharacter * pref);
public:

	static MapManager* getInstance() {
		if (instance == NULL)
		{
			instance = new MapManager();
		}
		return instance;
	}
	~MapManager();

	AMap* GetMapPointer(int index) { return mapList[index]; }
	AMap* GetCurrentMapPointer() { return mapList[m_currentMap]; }

	std::vector <AMap*>* GetMaps(int index) { return &mapList; }
	std::vector<std::vector<int>>* GetCurrentMapArray(int index) { return mapList[index]->GetMapArray(); }
	void ChangeMap(int index) { m_currentMap = index; }
	void SetPlayerRef(ACharacter* pref) {playerREF = pref;}
	void SetTilemap(const char* tileset) {m_image = ResourceManager::getInstance()->loadAndGetGraphicID(tileset);}
	void Init(Camera * _cam);
	void Update();
	void Render();
};

