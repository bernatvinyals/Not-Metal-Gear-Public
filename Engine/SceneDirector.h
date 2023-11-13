#pragma once

#include <vector>
#include "Scene.h"

enum SceneEnum {
	MAIN, GAME, TRANSCRIBER, EQUIPMENT, INVENTORY, HIGHSCORE, GAMEOVER,
	_LASTSCENE
};
#define NUM_SCENES _LASTSCENE
class SceneDirector
{
public:
	~SceneDirector();

	void init();

	void changeScene(SceneEnum next_scene, bool reinit = true, bool unloadCurrent = false);

	SceneEnum getCurrSceneEnum() { return mCurrScene; };

	Scene* getCurrentScene() { return mVectorScenes[mCurrScene]; };


	SceneEnum getPreviousSceneEnum() { return mLastScene; };

	//To check something player might have done on game and act acordingly
	Scene* getPreviousScene() { return mVectorScenes[mLastScene]; };

	//! Gets pointer to instance
	static SceneDirector* getInstance();

	void PrintLoaded();
	void PrintCurrSceneTitle();

protected:
	SceneDirector();
	static SceneDirector* pInstance;	/*!<  pointer instance*/

	std::vector<Scene*>	mVectorScenes;
	SceneEnum		mCurrScene;
	SceneEnum		mLastScene;
};

