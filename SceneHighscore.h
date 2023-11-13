#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneHighscore :   public Scene
{
	Actor demo;
public:
	SceneHighscore();
	~SceneHighscore() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;
};

