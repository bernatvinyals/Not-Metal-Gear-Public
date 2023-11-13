#pragma once
#include "Engine/Scene.h"
#include "Engine/ACharacter.h"
#include "Engine/UIText.h"
#include "Engine/MapManager.h"
#include "Engine/Camera.h"
#include "EnemyManager.h"
class SceneGame : public Scene
{
	UIText * lifeText;
	UIText* classText;
	MapManager * mapManager;
	EnemyManager* enemyManager;
	static ACharacter Player;
public:
	static Camera* cam;
	static bool gameResume;
	SceneGame();
	~SceneGame() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;

	static ACharacter* GetPlayer() {
		return &Player;
	}
};

