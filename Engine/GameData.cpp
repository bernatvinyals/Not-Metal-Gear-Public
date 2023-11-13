#include "GameData.h"
#include "../AItem_Weapon.h"

GameData* GameData::pInstance = 0;


GameData::GameData()
{
	equipment = std::vector<AItem*>();
	utilities = std::vector<AItem*>();
	m_selectedWeapon = -1;
	m_selectedUtility = -1;
	m_notification = ANotification();
	m_firstObj = true;
}


GameData* GameData::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new GameData();
	}
	return pInstance;
}

GameData::~GameData()
{
}

void GameData::StartPlay()
{
	m_notification.StartPlay();
	for (size_t i = 0; i < equipment.size(); i++)
	{
		delete equipment[i];
	}
	for (size_t i = 0; i < utilities.size(); i++)
	{
		delete utilities[i];
	}
	equipment = std::vector<AItem*>();
	utilities = std::vector<AItem*>();
}

void GameData::AddItem(AItem* val)
{
	bool alreadyOn = false;
	switch (val->GetType())
	{
	case ITEM_TYPE::UTILITY:
		for (int i = 0; i < utilities.size(); i++)
		{
			if (utilities[i]->GetName() == val->GetName())
			{
				utilities[i]->AddToQuantity();
				i = utilities.size();
				alreadyOn = true;
			}
		}
		if (!alreadyOn)
		{
			utilities.push_back(val);
			if (!m_firstObj)
			{
				if (val->showNotification)
				{
					m_notification.AddNotification(val->GetName());

				}

			}
			else
			{
				m_firstObj = false;
			}

		}
		if (m_selectedUtility == -1)
		{
			m_selectedUtility = 0;
		}

		break;
	case ITEM_TYPE::WEAPON:
		for (int i = 0; i < equipment.size(); i++)
		{
			if (equipment[i]->GetName() == val->GetName())
			{
				AItem_Weapon* asWeapon = dynamic_cast<AItem_Weapon*>(equipment[i]);
				if (asWeapon != nullptr)
				{
					asWeapon->AddAmmo(20);														//We instead Add more ammo to it
				}
				i = equipment.size();
				alreadyOn = true;
			}
		}
		if (!alreadyOn)
		{
			equipment.push_back(val);
			if (!m_firstObj)
			{
				if (val->showNotification)
				{
					m_notification.AddNotification(val->GetName());
				}
			}
			else
			{
				m_firstObj = false;
			}
		}
		if (m_selectedWeapon == -1)
		{
			m_selectedWeapon = 0;
		}

		break;
	default:
		break;
	}
	if (m_debug)
	{
		printf("Item Added :: %s\n", val->GetName());
		printf("Equipment Inventory::\n");
		for (UINT i = 0; i < equipment.size(); i++)
		{
			AItem_Weapon* asWeapon = dynamic_cast<AItem_Weapon*>(equipment[i]);
			if (asWeapon != nullptr)
			{
				printf("Item %d :: %s  Ammo: %d\n", i, equipment[i]->GetName(), asWeapon->GetAmmo());
			}
		}
		printf("Utilities Inventory::\n");
		for (UINT i = 0; i < utilities.size(); i++)
		{
			printf("Item %d :: %s  Q: %d\n", i, utilities[i]->GetName(), utilities[i]->GetQuantity());
		}
	}
}

void GameData::RenderAsUiInGame()
{
	m_notification.Render();

	if (m_selectedUtility > -1)
	{
		utilities[m_selectedUtility]->RenderAsUI();
	}
	if (m_selectedWeapon > -1)
	{
		equipment[m_selectedWeapon]->RenderAsUI();
	}
}
