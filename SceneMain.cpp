#include "SceneMain.h"
#include "Engine/SceneDirector.h"
#include "Engine/Video.h"
#include "Engine/Globals.h"
#include "Engine/Input.h"
#include "Engine/ResourceManager.h"
#include "Engine/SoundManager.h"

SceneMain::SceneMain()
{
	m_SceneName = "MENU";
	logo = Actor();
	mReinit = true;
	cursor = Actor();
	SelectedIndex = 0;
	notPressedDown = true;
	firstFrame = true;
	logo.CreateActor(0, 0, "./assets/img/menu/menu.png", true);
	cursor.CreateActor(0, 0, "./assets/img/persistent/Selector.png", true, false);

}

void SceneMain::init()
{
	SoundManager::getInstance()->haltSound();
	logo.SetY(SCREEN_HEIGHT);
	cursor.SetScreenX(70);
	SoundManager::getInstance()->playSound(
		SoundManager::getInstance()->getSoundByID(
			SoundManager::getInstance()->loadAndGetSoundID("./assets/sound/mg1_se00_title.ogg")));
	mReinit = false;
	firstFrame = true;
}

void SceneMain::render()
{
	logo.SetScreenX(0);
	logo.SetScreenY(0);
	logo.Render();
	cursor.SetScreenY(100 + (16 * (SelectedIndex % 4) + 1));
	cursor.Render();
}

void SceneMain::update()
{
	if (firstFrame) {
		firstFrame = false;
		return;
	}
	logo.Update();
	Video::getInstance()->GetDeltaTime();
	logo.SetY(0);

	//Play
	if (Input::getInstance()->keyboard.KB_SPACE || Input::getInstance()->keyboard.KB_RETURN)
	{
		switch (SelectedIndex)
		{
		case 0:
			SceneDirector::getInstance()->changeScene(GAME, true);
			break;
		case 1:
			SceneDirector::getInstance()->changeScene(GAME, true);
			// --- TODO ---
			//Function to load game --> HERE
			break;
		case 2:
			SceneDirector::getInstance()->changeScene(HIGHSCORE, true);
			break;
		case 3:
			Input::getInstance()->ExitGame();
			break;
		default:
			break;
		}
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
		if (SelectedIndex >= 4)
		{
			SelectedIndex = SelectedIndex - 1;
		}
	}
	if (!Input::getInstance()->keyboard.KB_UP && !Input::getInstance()->keyboard.KB_DOWN)
	{
		notPressedDown = true;
	}

}

void SceneMain::unload()
{
}
