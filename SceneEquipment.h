#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneEquipment :   public Scene
{
	Actor demo;
	Actor cursor;
	int SelectedIndex;
	int maxAmount;
	bool notPressedDown;
public:
	SceneEquipment();
	~SceneEquipment() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;
};

