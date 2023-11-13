#pragma once
#include <vector>
#include "../AItem.h"
#include "ANotification.h"


class GameData
{
	bool m_debug;
	bool m_firstObj;
	std::vector<AItem*> equipment;
	std::vector<AItem*> utilities;

	int m_selectedUtility;
	int m_selectedWeapon;


	ANotification m_notification;

	static GameData* pInstance;		/*!<  Singleton instance*/
protected:
	//! Constructor of an empty GameData.
	GameData();
public:
	static GameData* getInstance();
	~GameData();
	void StartPlay();
	void AddItem(AItem* val);
	std::vector<AItem*>* GetInventory(int _isEquipment) {
		if (_isEquipment)
		{
			return &equipment;
		}
		return &utilities;
	}

	int GetCurrentWeapon() {
		return m_selectedWeapon;
	};
	int GetCurrentUtility() {
		return m_selectedUtility;
	};
	AItem* GetCurrentWeaponRef() {
		return equipment.at(m_selectedWeapon);
	};
	AItem* GetCurrentUtilityRef() {
		return utilities.at(m_selectedUtility);
	};
	void SetSelectedWeapon(int _val) { m_selectedWeapon = _val; };
	void SetSelectedUtility(int _val) { m_selectedUtility = _val; };
	void RenderAsUiInGame();
};

