#include "AMapSwitcher.h"

AMapSwitcher::AMapSwitcher()
{
	playerREFERANCE = nullptr;
}

AMapSwitcher::AMapSwitcher(ACharacter* playerref)
{
	playerREFERANCE = nullptr;
	SetCanBeRendered(false);
}

AMapSwitcher::AMapSwitcher(ACharacter* playerref, LAZY::DIRECTIONS playerDirections, LAZY::TRANSFORM transform, bool crateGraphic, Uint8 r, Uint8 g, Uint8 b)
{
	playerDir = playerDirections;
	playerREFERANCE = playerref;
	SetCanBeRendered(false);
	CreateActor(transform.x, transform.y, NULL, false, crateGraphic, transform.w, transform.h, r, g, b);
}


void AMapSwitcher::Update()
{
	Actor::Update();
	if (CheckIfOutOfBounds())
	{
		return;
	}
	CheckANDSendPlayer();
}

void AMapSwitcher::CheckANDSendPlayer()
{

	int Spaceing = 10;

	int Inside_UPLeftX = playerREFERANCE->GetWorldRect()->x + Spaceing;
	int Inside_UPLeftY = playerREFERANCE->GetWorldRect()->y + Spaceing;
	int Inside_UPRightX = playerREFERANCE->GetWorldRect()->x + (playerREFERANCE->GetWorldRect()->w - Spaceing);
	int Inside_UPRightY = playerREFERANCE->GetWorldRect()->y + Spaceing;

	int Inside_DownLeftX = playerREFERANCE->GetWorldRect()->x + Spaceing;
	int Inside_DownLeftY = playerREFERANCE->GetWorldRect()->y + (playerREFERANCE->GetWorldRect()->h - Spaceing);
	int Inside_DownRightX = playerREFERANCE->GetWorldRect()->x + (playerREFERANCE->GetWorldRect()->w - Spaceing);
	int Inside_DownRightY = playerREFERANCE->GetWorldRect()->y + (playerREFERANCE->GetWorldRect()->h - Spaceing);


	bool UpLeft_Inside = 
		Inside_UPLeftX > m_worldRect.x
		&&
		Inside_UPLeftX < m_worldRect.x + m_rect.w
		&&
		Inside_UPLeftY > m_worldRect.y
		&&
		Inside_UPLeftY < m_worldRect.y + m_rect.h;

	bool UpRight_Inside =
		Inside_UPRightX > m_worldRect.x
		&&
		Inside_UPRightX < m_worldRect.x + m_rect.w
		&&
		Inside_UPRightY > m_worldRect.y
		&&
		Inside_UPRightY < m_worldRect.y + m_rect.h;
	/*
	printf("\n Player %d %d %d %d \n",
		playerREFERANCE->GetWorldRect()->x,
		playerREFERANCE->GetWorldRect()->y,
		playerREFERANCE->GetWorldRect()->x + playerREFERANCE->GetWorldRect()->w,
		playerREFERANCE->GetWorldRect()->y + playerREFERANCE->GetWorldRect()->h
	);

	printf("\n Smaller Point UP %d %d %d %d \n",
		Inside_UPLeftX,
		Inside_UPLeftY,
		Inside_UPRightX,
		Inside_UPRightY
	);
	printf("\n Smaller Point Down %d %d %d %d \n",
		Inside_DownLeftX,
		Inside_DownLeftY,
		Inside_DownRightX,
		Inside_DownRightY
	);
	*/
	bool DownLeft_Inside =
		Inside_DownLeftX > m_worldRect.x
		&&
		Inside_DownLeftX < m_worldRect.x + m_rect.w
		&&
		Inside_DownLeftY > m_worldRect.y
		&&
		Inside_DownLeftY < m_worldRect.y + m_rect.h;


	bool x1 = Inside_DownRightX > m_worldRect.x
		;
	bool x2 = Inside_DownRightX < m_worldRect.x + m_rect.w
		;
	bool x3 = Inside_DownRightY > m_worldRect.y
		;
	bool x4 = Inside_DownRightY < m_worldRect.y + m_rect.h;
	;
	bool DownRight_Inside = x1 && x2 && x3 && x4;



	if (UpLeft_Inside || UpRight_Inside || DownLeft_Inside || DownRight_Inside)
	{
		switch (playerDir)
		{
		case LAZY::UP:
			playerREFERANCE->SetY(playerREFERANCE->GetY() + 34);
			MapManager::getInstance()->GetCurrentMapPointer()->CamaraStepDown();
			break;
		case LAZY::DOWN:
			playerREFERANCE->SetY(playerREFERANCE->GetY() - 38);
 			MapManager::getInstance()->GetCurrentMapPointer()->CamaraStepUp();
			break;
		case LAZY::LEFT:
			playerREFERANCE->SetX(playerREFERANCE->GetX() + 38);
			MapManager::getInstance()->GetCurrentMapPointer()->CamaraStepRight();
			break;
		case LAZY::RIGHT:
			playerREFERANCE->SetX(playerREFERANCE->GetX() - 38);
			MapManager::getInstance()->GetCurrentMapPointer()->CamaraStepLeft();
			break;
		case LAZY::CENTER:
			break;
		default:
			break;
		}

	}
}
