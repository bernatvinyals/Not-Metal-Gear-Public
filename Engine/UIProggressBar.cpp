#include "UIProggressBar.h"

UIProggressBar::UIProggressBar(SDL_Rect position, SDL_Color color)
{
	percentage = 1;
	m_color = color;
	CreateActor(position.x, position.y, NULL, true, true, position.w, position.h, color.r, color.g, color.b);
	horizontalSize = m_rect.w;
}

UIProggressBar::~UIProggressBar()
{
}

void UIProggressBar::ChangePercentage(int value, int max)
{
	percentage = value;
	m_rect.w = (int)map(value,0,max, 0, horizontalSize);
}
