#include "SceneGameOver.h"
#include "Engine/Input.h"
#include "Engine/SceneDirector.h"
#include "SceneGame.h"
#include "Engine/SoundManager.h"
SceneGameOver::SceneGameOver()
{
	m_SceneName = "GameOver";
	demo = Actor();
	mReinit = true;
}

void SceneGameOver::init()
{
	demo.CreateActor(0, 0, "./assets/img/gameOver/gameover.png",true);
	mReinit = false;
	SoundManager::getInstance()->playSound(
		SoundManager::getInstance()->getSoundByID(
			SoundManager::getInstance()->loadAndGetSoundID("./assets/sound/mg1_bgm01_continue.ogg")), 0);
}

void SceneGameOver::render()
{
	demo.Render();
 }

void SceneGameOver::update()
{
	if (mReinit)
	{
		init();
	}
	if (Input::getInstance()->keyboard.KB_SPACE)
	{
		SceneDirector::getInstance()->changeScene(MAIN, false, false);
	}
}

void SceneGameOver::unload()
{
}
