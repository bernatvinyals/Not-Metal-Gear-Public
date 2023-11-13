#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneGameOver :   public Scene
{
	Actor demo;
public:
	SceneGameOver();
	~SceneGameOver() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;
};

