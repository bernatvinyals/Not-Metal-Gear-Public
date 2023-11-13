#include "SceneHighscore.h"
#include "Engine/Input.h"
#include "Engine/SceneDirector.h"
#include "SceneGame.h"
SceneHighscore::SceneHighscore()
{
	m_SceneName = "TRANSCRIBER";
	demo = Actor();
	mReinit = true;
}

void SceneHighscore::init()
{
	//demo.CreateActor(0, 0, "./assets/img/transcriver/demo.png",true);
	mReinit = false;

}

void SceneHighscore::render()
{
	demo.Render();
 }

void SceneHighscore::update()
{
	if (mReinit)
	{
		init();
	}
	if (Input::getInstance()->keyboard.KB_ESCAPE)
	{
		SceneDirector::getInstance()->changeScene(MAIN, false, false);
	}
}

void SceneHighscore::unload()
{
}
