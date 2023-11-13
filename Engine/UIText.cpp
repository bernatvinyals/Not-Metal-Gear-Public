#include "UIText.h"
#include "TextManager.h"
#include "ResourceManager.h"

UIText::UIText(const char* text, const char* fontPath, unsigned int scale, SDL_Rect position, SDL_Color  color)
{
	canBeRendered = true;
	fontId = TextManager::getInstance()->loadAndGetFontID(fontPath, scale);
	int width=0, height=0;
	assignedText = new std::string();
	m_image = TextManager::getInstance()->writeText(fontId, text,&width,&height, color, assignedText);
	m_rect = {
		position.x, position.y,
		width,height 
	};
}

UIText::~UIText()
{
}

void UIText::Update()
{
	
}

void UIText::Flush()
{
	if (assignedText != nullptr)
	{
		ResourceManager::getInstance()->removeGraphic(assignedText->c_str());
	}
}
