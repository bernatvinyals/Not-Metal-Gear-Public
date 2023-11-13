#ifdef _WIN64
#include "SDL.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#endif //Linux includes

#include "Engine/Input.h"
#include "Engine/Video.h"
#include "Engine/SceneDirector.h"

#include <iostream>

SceneDirector* sDirector = NULL;
Input* sInputControl = NULL;

int main(int argc, char* args[]) 
{
	sInputControl = Input::getInstance();
	sDirector = SceneDirector::getInstance();

	bool endGame = false;
	while (!endGame)
	{
		if (sDirector->getCurrentScene()->mustReInit()) {
			sDirector->getCurrentScene()->Reinit();
			//Debug
			sDirector->PrintLoaded();
			sDirector->PrintCurrSceneTitle();
		}
		sInputControl->Update(endGame);

		sDirector->getCurrentScene()->update();


		//Render
		Video::getInstance()->clearScreen(0x100000);
		if (!sDirector->getCurrentScene()->mustReInit()) {
			sDirector->getCurrentScene()->render();
		}
		Video::getInstance()->updateScreen();
		Video::getInstance()->vSync();
	}
	Video::getInstance()->close();
	return 0;
}