#include "SceneWeaponList.h"
#include "Engine/Input.h"
#include "Engine/SceneDirector.h"
#include "SceneGame.h"
#include "Engine/GameData.h"
#include "Engine/SoundManager.h"

SceneWeaponList::SceneWeaponList()
{
	m_SceneName = "EQUIPMENT";
	demo = Actor();
	cursor = Actor();
	mReinit = true;
}

void SceneWeaponList::init()
{
	demo.CreateActor(0, 0, "./assets/img/inventory/DemoWeaponInv.png",true, false);
	cursor.CreateActor(0, 0, "./assets/img/persistent/Selector.png", true, false);
	mReinit = false;
	maxAmount = 0;
}

void SceneWeaponList::render()
{
	demo.Render();
	std::vector<AItem*>* itemlist = GameData::getInstance()->GetInventory(1);
	maxAmount = itemlist->size();
	int counter = 0;
	int x = 1;
	for (unsigned int i = 0; i < itemlist->size(); i++)
	{
		if (counter > 3)
		{
			x++;
			counter = 0;
		}
		itemlist->at(i)->RenderAsInventory(38*x,30+(18*counter));
		counter++;
	}
	cursor.SetScreenX(28 * ((SelectedIndex / 4)+1));
	cursor.SetScreenY(30 + (18*(SelectedIndex % 4)+1));
	cursor.Render();
	itemlist->at(SelectedIndex)->RenderName(23, 105);
	SceneGame::GetPlayer()->RenderUI();
	GameData::getInstance()->RenderAsUiInGame();
}

void SceneWeaponList::update()
{
	if (mReinit)
	{
		init();
	}
	if (Input::getInstance()->keyboard.KB_ESCAPE)
	{
		SceneDirector::getInstance()->changeScene(GAME, false, false);
		
	}
	if (Input::getInstance()->keyboard.KB_UP && notPressedDown)
	{
		notPressedDown = false;
		SelectedIndex--;
		if (SelectedIndex < 0)
		{
			SelectedIndex = 0;
		}
	}
	else if (Input::getInstance()->keyboard.KB_DOWN && notPressedDown)
	{
		notPressedDown = false;
		SelectedIndex++;
		if (SelectedIndex >= maxAmount)
		{
			SelectedIndex = SelectedIndex-1;
		}
	}
	if (Input::getInstance()->keyboard.KB_RETURN && notPressedDown)
	{
		notPressedDown = false;

		GameData::getInstance()->SetSelectedWeapon(SelectedIndex);
		SoundManager::getInstance()->playSound(
			SoundManager::getInstance()->getSoundByID(
				SoundManager::getInstance()->loadAndGetSoundID("./assets/sound/mg1_se11_item_select.ogg")), 1);
	}
	if (!Input::getInstance()->keyboard.KB_UP && !Input::getInstance()->keyboard.KB_DOWN && !Input::getInstance()->keyboard.KB_RETURN)
	{
		notPressedDown = true;
	}
}

void SceneWeaponList::unload()
{
}
