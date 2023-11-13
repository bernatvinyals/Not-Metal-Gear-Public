#pragma once
#include "Actor.h"
#include <string>
class UIText : public Actor
{
	int fontId;
	std::string* assignedText;
public:
	UIText() {};
	UIText(const char* text, const char* fontPath, unsigned int scale, SDL_Rect position, SDL_Color color);
	~UIText();

	void Update();
	void Flush();
};

