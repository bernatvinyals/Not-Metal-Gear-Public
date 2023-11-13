#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneMain : public Scene
{
	Actor logo;
	Actor cursor;
	int SelectedIndex;
	bool notPressedDown;
	bool firstFrame;
public:
	SceneMain();
	~SceneMain() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;

};

