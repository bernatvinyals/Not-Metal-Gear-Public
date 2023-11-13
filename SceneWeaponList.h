#pragma once
#include "Engine/Scene.h"
#include "Engine/Actor.h"
class SceneWeaponList :   public Scene
{
	Actor demo;
	Actor cursor;
	int SelectedIndex;
	int maxAmount;
	bool notPressedDown;
public:
	SceneWeaponList();
	~SceneWeaponList() {};

	virtual void init() override;

	virtual void render() override;

	virtual void update() override;

	virtual void unload() override;
};

