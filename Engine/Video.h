#pragma once
#ifdef _WIN64
#include "SDL.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#endif //Linux includes
#define FPS 60

//SDL_BLENDMODE_ADD TO CHANGE TONE OF COLOR TO BRIGHTER
//SDL_BLENDMODE_ADD TO CHANGE TONE OF COLOR TO dARKER
//SDL_SetSurfaceColorMod(surface to change, r,g,b)

class Video
{
	static Video* pInstance;

	unsigned int lastTime;
	unsigned int currentTime;
	unsigned int deltaTime;


	Video();
	~Video();
public:
	static Video * getInstance();
	void renderGraphic(int img, int posX, int posY, int width, int height, int auxX = 0, int auxY = 0, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderGraphic(SDL_Texture *tex, int posX, int posY, int width, int height, int auxX, int auxY, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	void waitTime(int ms);

	int GetTicks();
	int GetDeltaTime();

	//!Limits FPS
	void vSync();
	void close();

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

};