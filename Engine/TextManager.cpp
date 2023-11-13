#include "TextManager.h"
#include "ResourceManager.h"
#include "SDL_Image.h"
#include "Video.h"
#include <iostream>
TextManager::TextManager()
{
	mFirstFreeSlot = -1;
	TTF_Init();

}

Uint32 TextManager::updateFirstFreeSlotFont()
{
	for (int i = 0; i < mFontsVector.size(); i++)
	{
		if (mFontsVector[i] == NULL)
		{
			mFirstFreeSlot = i;
			return i;
		}
	}
	return -1;
}

Sint32 TextManager::addFont(const char* file, Uint32 size)
{
	if (mFirstFreeSlot != -1)
	{
		mFontsVector[mFirstFreeSlot] = TTF_OpenFont(file, size);
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		Uint32 temp = mFirstFreeSlot;
		mFirstFreeSlot = -1;
		return temp;
	}
	else
	{
		mFontsVector.push_back(TTF_OpenFont(file, size));
		if (!mFontsVector[mFontsVector.size() - 1])
		{
			mFontsVector.pop_back();
			printf("\n!!ERROR LOADING Font: %s\n", IMG_GetError());
			return -1;
		}
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mFontsVector.size() - 1));

		return mFontsVector.size() - 1;
	}
}

TextManager::~TextManager()
{
}

TextManager* TextManager::pInstance = NULL;
Sint32 TextManager::loadAndGetFontID(const char* file, Uint32 size)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end())
	{
		return addFont(file, size);
	}
	else
	{
		return it->second;
	}
}
std::string TextManager::getFontPathByID(Sint32 ID)
{
	std::map<std::string, Sint32>::iterator it;
	for (it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}
	return "";
}
void TextManager::removeFont(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	TTF_CloseFont(mFontsVector[it->second]);
	mFontsVector[it->second] = NULL;
	mIDMap.erase(file);
	updateFirstFreeSlotFont();
}
void TextManager::printLoadedFonts()
{
	std::map<std::string, Sint32>::iterator it;
	std::cout << "\n---- Loaded Fonts -----------------------------------" << "\n";
	for (it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		std::cout << "File Path: " << it->first << "\n";
	}
	std::cout << "------------------------------------------------------" << "\n";

}
int TextManager::writeText(Sint32 fontID, const char* string, int * width, int *height, SDL_Color color, std::string * outStr)
{
	std::string textString = "UI-";
	textString.append(getFontPathByID(fontID));
	textString.append("-");
	textString.append(string);


	
	int returnId = ResourceManager::getInstance()->getGraphicByPath(textString.c_str());
	if (returnId == -1)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(mFontsVector[fontID], string, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Video::getInstance()->gRenderer, surface);
		printf("\n SDL_ERROR: %s \n",SDL_GetError());
		textString.append(std::to_string(surface->w));
		textString.append("-");
		textString.append(std::to_string(surface->h));
		textString.append(std::to_string((rand() % 999 * 2)));
		int returned = ResourceManager::getInstance()->addRawGraphic(texture, textString.c_str());
		*height = surface->h;
		*width = surface->w;
		SDL_FreeSurface(surface);
		if (outStr != nullptr)
		{
			outStr->append(std::string(textString).c_str());
		}
		return returned;
	}
	else
	{
		if (outStr != nullptr)
		{
			outStr->append(std::string(textString).c_str());
		}
		return returnId;
	}
	//TODO 
	//Send now created text to render

	//Chance
	//DO a map to check if the current string has already a graphic created and display that instead
}
TextManager* TextManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new TextManager();
	}
	return pInstance;
}
