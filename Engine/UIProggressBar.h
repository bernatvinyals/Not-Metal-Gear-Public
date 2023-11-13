#pragma once
#include "Actor.h"
class UIProggressBar : public Actor
{
	int percentage;
	SDL_Color m_color;
	int horizontalSize;
public:
	UIProggressBar() {};
	UIProggressBar(SDL_Rect position, SDL_Color color);
	~UIProggressBar();
	 
	/// <summary>
	/// Change The with of progressbar
	/// </summary>
	/// <param name="value">A float between 0 and 1 </param>
	void ChangePercentage(int value, int max);
};

