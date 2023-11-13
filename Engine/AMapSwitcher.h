#pragma once
#include "Actor.h"
#include "ACharacter.h"
#include "MapManager.h"
#include "Globals.h"
class AMapSwitcher : public Actor
{
	ACharacter *  playerREFERANCE;
	LAZY::DIRECTIONS playerDir;
public:
	AMapSwitcher();
	AMapSwitcher(ACharacter * playerref);
	AMapSwitcher(ACharacter* playerref, LAZY::DIRECTIONS playerDirections, LAZY::TRANSFORM transform, bool crateGraphic = false, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

	void Update();
	void CheckANDSendPlayer();
};

