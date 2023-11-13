#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneTranscriber :   public Scene
{
	Actor demo;
public:
	SceneTranscriber();
	~SceneTranscriber() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;
};

