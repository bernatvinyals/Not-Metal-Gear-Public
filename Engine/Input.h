#pragma once
#ifdef _WIN64
#include "SDL.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#endif //Linux includes
#include "InputGamepad.h"
#include "KeyboardInfo.h"
#include "PlayerDirections.h"
class Input
{
	Input();

	static Input* instance;
	bool IsControler1;
	SDL_Event m_inputEvent;
	SDL_GameController* m_controller;

	PlayerDirections Player1Direction;
	bool exitRequested;
	//AUTOMATICALLY GETS SET ON CONSTRUCTION
	//DO NOT CALL
	void Init();
public:
	~Input();

	static Input* getInstance() {
		if (instance == NULL)
		{
			instance = new Input();
		}
		return instance;
	}
	PlayerDirections * GetInputDirectionsPlayer1() { return &Player1Direction; }

	InputGamepad gamepad;

	KeyboardInfo keyboard;

	/// <summary>
	/// Picks neccesary Input commands
	/// </summary>
	/// <param name="endGame"> returns if player wants to leave</param>
	void Update(bool &endGame);
	void Quit();
	void ExitGame() {
		exitRequested = true;
	}
};

