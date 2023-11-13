#include "SceneDirector.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "../SceneMain.h"
#include "../SceneGame.h"
#include "../SceneTranscriber.h"
#include "../SceneEquipment.h"
#include "../SceneWeaponList.h"
#include "../SceneHighscore.h"
#include "../SceneGameOver.h"
SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance() {
	if (!pInstance) {
		pInstance = new SceneDirector();
	}
	return pInstance;
}

void SceneDirector::PrintLoaded()
{
	SoundManager::getInstance()->printLoadedSounds();
	ResourceManager::getInstance()->printLoadedGraphics();
}

void SceneDirector::PrintCurrSceneTitle()
{
	printf("Scene %s", mVectorScenes[mCurrScene]->GetName());
}

SceneDirector::SceneDirector() {
	init();
}

SceneDirector::~SceneDirector() {
}

void SceneDirector::init() {
	mVectorScenes.resize(NUM_SCENES);

	SceneMain* main = new SceneMain();
	SceneGame* game = new SceneGame();
	SceneEquipment* equipment = new SceneEquipment();
	SceneTranscriber* transcriber = new SceneTranscriber();
	SceneWeaponList* inventory = new SceneWeaponList();
	SceneHighscore* highscore = new SceneHighscore();
	SceneGameOver* gameOver = new SceneGameOver();

	mVectorScenes[MAIN] = main;
	mVectorScenes[GAME] = game;
	mVectorScenes[TRANSCRIBER] = transcriber;
	mVectorScenes[EQUIPMENT] = equipment;
	mVectorScenes[INVENTORY] = inventory;
	mVectorScenes[HIGHSCORE] = highscore;	
	mVectorScenes[GAMEOVER] = gameOver;


	main->init();
	mCurrScene = MAIN;
	mLastScene = MAIN;
	PrintCurrSceneTitle();
	PrintLoaded();
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit, bool unloadCurrent) {
	mLastScene = mCurrScene;
	if (unloadCurrent)
	{
		mVectorScenes[mLastScene]->unload();
	}
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
	PrintCurrSceneTitle();
	PrintLoaded();
}
