#pragma once
#include "Globals.h"
class Camera
{
	LAZY::TRANSFORM transform;
	bool HasChanged;
public:
	Camera();
	~Camera();
	LAZY::TRANSFORM* GetTransform() { return &transform; }
	bool HasMoved() { return HasChanged; }
	int GetX() { return transform.x; }
	int GetY() { return transform.y; }
	void SetX(int _x) { 
		HasChanged = true;
		transform.x = _x; }
	void SetY(int _y) { 
		HasChanged = true;
		transform.y = _y; }

	void Update(){ HasChanged = false; }
};

