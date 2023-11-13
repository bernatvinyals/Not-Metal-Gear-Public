#pragma once
#ifdef _WIN64
#include "SDL.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#endif //Linux includes
#include "PlayerDirections.h"
class InputGamepad
{
protected:
	float lx;
	float ly;
	float rx;
	float ry;
	float padding;
public:
	InputGamepad();
	~InputGamepad();

	float GetLeftX() const { return lx; }
	float GetLeftY() const { return ly; }
	float GetRightX() const { return rx; }
	float GetRightY() const { return ry; }


	void SetLeftX(float value) { lx = value; }
	void SetLeftY(float value) { ly = value; }
	void SetRightX(float value) { rx = value; }
	void SetRightY(float value) { ry = value; }
	
	float NormalizeAxis(int value);
	void ResetAxis();
	void StopAxis(PlayerDirections *pDirections);

};

