#include "Camera.h"

Camera::Camera()
{
	transform = { 0,0,GAMEPLAY_SCREEN_WIDTH, GAMEPLAY_SCREEN_HEIGHT,0 };
	HasChanged = false;
}

Camera::~Camera()
{
}
