#include "SceneTranscriber.h"
#include "Engine/Input.h"
#include "Engine/SceneDirector.h"
#include "SceneGame.h"
SceneTranscriber::SceneTranscriber()
{
	m_SceneName = "TRANSCRIBER";
	demo = Actor();
	mReinit = true;
}

void SceneTranscriber::init()
{
	demo.CreateActor(0, 0, "./assets/img/transcriver/demo.png",true);
	mReinit = false;

}

void SceneTranscriber::render()
{
	demo.Render();
	SceneGame::GetPlayer()->RenderUI();
}

void SceneTranscriber::update()
{
	if (mReinit)
	{
		init();
	}
	if (Input::getInstance()->keyboard.KB_ESCAPE)
	{
		SceneDirector::getInstance()->changeScene(GAME, false, false);
	}
}

void SceneTranscriber::unload()
{
}
