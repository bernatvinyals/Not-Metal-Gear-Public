#include "SceneGame.h"
#include "Engine/SceneDirector.h"
#include "Engine/Input.h"
#include "Engine/Globals.h"
#include "Engine/GameData.h"
#include "Engine/SoundManager.h"

Camera* SceneGame::cam = new Camera();
ACharacter SceneGame::Player = ACharacter();
bool SceneGame::gameResume = true;
SceneGame::SceneGame() {
	m_SceneName = "GAME";
	classText = nullptr;
	lifeText = nullptr;
	mReinit = true;
	enemyManager = EnemyManager::getInstance();
	mapManager = MapManager::getInstance();
	mapManager->SetTilemap("./assets/img/persistent/persistentMapTileset.png");
	mapManager->SetPlayerRef(&Player);
	Player.CreateActor(13 * 8, 103 * 8, "./assets/img/SolidSnake/SolidSnake128x128.png", false);

}

void SceneGame::init()
{
	//SDL_Color color = { 255,255,255 };
	//14*8, 140*8
	SoundManager::getInstance()->haltSound();
	GameData::getInstance()->StartPlay();
	Player.Init();
	Player.SetX(13 * 8);
	Player.SetY(103 * 8);
	Player.SetSpriteSize(16, 32);
	Player.SetVelocity(2);
	Player.SetHP(100);
	mapManager->Init(cam);
	
	enemyManager->Init();
	cam->SetY(96 * 8);
	mReinit = false;
	SoundManager::getInstance()->playSound(
		SoundManager::getInstance()->getSoundByID(
			SoundManager::getInstance()->loadAndGetSoundID("./assets/sound/mg1_bgm03_main.ogg")),-1);
}

void SceneGame::render()
{
	mapManager->Render();
	enemyManager->Render();
	Player.Render();
	Player.RenderUI();
	GameData::getInstance()->RenderAsUiInGame();
}

void SceneGame::update()
{
	if (mReinit)
	{
		init();
	}
	if (gameResume)
	{
		mapManager->Update();
		enemyManager->Update();
	}

	Player.Update();

	cam->Update();
}

void SceneGame::unload()
{
}
