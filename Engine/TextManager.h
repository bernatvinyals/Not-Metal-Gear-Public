#pragma once
#ifdef _WIN64
#include "SDL.h"
#include "SDL_ttf.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif //Linux includes
#include <string>
#include <vector>
#include <map>
class TextManager
{
	TextManager();
	static TextManager* pInstance;
	std::vector<TTF_Font*> mFontsVector;
	std::map<std::string, Sint32>	mIDMap;
	Uint32				mFirstFreeSlot;

	Uint32 updateFirstFreeSlotFont();
	Sint32 addFont(const char* file, Uint32 size);
	

public:
	~TextManager();

	Sint32 loadAndGetFontID(const char* file, Uint32 size);
	std::string getFontPathByID(Sint32 ID);
	void removeFont(const char* file);
	void printLoadedFonts();

	int writeText(Sint32 fontID, const char* string, int* width, int* height, SDL_Color color = {255,255,255}, std::string* outStr = nullptr);

	void Quit() {TTF_Quit();}

	static TextManager* getInstance();
};

