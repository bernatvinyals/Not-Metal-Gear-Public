#include "AItem.h"
#include "Engine/Video.h"
#include "Engine/GameData.h"
#include "Engine/ACharacter.h"
AItem::AItem()
{
	instigator = nullptr;
	spawnPosition = {0,0,0,0};
	itemName = "Please use Constructor";
	obtained = false;
	type = ITEM_TYPE::WEAPON;
	quantity = 1;
	showNotification = true;
}

AItem::AItem(Actor* playerref, LAZY::TRANSFORM transform, const char* name, ITEM_TYPE _type, int offset_X, int offset_Y)
{
	instigator = playerref;
	spawnPosition = transform;
	itemName = name;
	type = _type;
	quantity = 1;

	obtained = false;
	CreateActor(spawnPosition, ITEMS_GX_PATH);
	m_worldRect = spawnPosition;
	m_rect.w = spawnPosition.w;
	m_rect.h = spawnPosition.h;
	m_offX = offset_X;
	m_offY = offset_Y;
	textRender = UIText(name, "./assets/fonts/Mulish-Regular.ttf", 14, { 26,10,0,0 }, { 255,255,255 });
	showNotification = true;
}

AItem::AItem(Actor* playerref, LAZY::TRANSFORM transform, E_Items e_itemname, ITEM_TYPE _type, int offset_X, int offset_Y )
{
	instigator = playerref;
	spawnPosition = transform;
	itemName = "";
	type = _type;
	quantity = 1;

	obtained = false;
	CreateActor(spawnPosition, ITEMS_GX_PATH);
	m_worldRect = spawnPosition;
	m_rect.w = spawnPosition.w;
	m_rect.h = spawnPosition.h;
	m_offX = offset_X;
	m_offY = offset_Y;
	showNotification = true;
}

AItem::~AItem()
{
}

void AItem::Update()
{
	if (!obtained)
	{
		Actor::Update();
	
		if (CheckIfPlayerIsOnTop())
		{
			GameData::getInstance()->AddItem(this);
			obtained = true;
		}
	}
	
}

void AItem::Render()
{
	if (!obtained)
	{
		Video::getInstance()->renderGraphic(m_image, m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.w * m_offX, m_rect.h * m_offY);
	}
}

bool AItem::CheckIfPlayerIsOnTop()
{
	ACharacter* player= ((ACharacter*)instigator);
	LAZY::TRANSFORM* pTRNF = player->GetWorldRect();

	if (m_worldRect.x < pTRNF->x + pTRNF->w
		&& m_worldRect.x + m_worldRect.w > pTRNF->x
		&& m_worldRect.y < pTRNF->y + pTRNF->h
		&& m_worldRect.h + m_worldRect.y > pTRNF->y)
	{
		return true;
	}
	return false;
}

void AItem::RenderAsUI()
{
	switch (type)
	{
	case WEAPON:
		Video::getInstance()->renderGraphic(m_image, 160, GAMEPLAY_SCREEN_HEIGHT + 2, m_rect.w, m_rect.h, m_rect.w * m_offX, m_rect.h * m_offY);
		break;
	case UTILITY:
		Video::getInstance()->renderGraphic(m_image, 223, GAMEPLAY_SCREEN_HEIGHT + 2, m_rect.w, m_rect.h, m_rect.w * m_offX, m_rect.h * m_offY);
		break;
	default:
		break;
	}
}

void AItem::RenderAsInventory(int x, int y)
{
	Video::getInstance()->renderGraphic(m_image, x, y, m_rect.w, m_rect.h, m_rect.w * m_offX, m_rect.h * m_offY);
}

void AItem::RenderName(int x, int y)
{
	textRender.SetScreenX(x);
	textRender.SetScreenY(y);

	textRender.Render();
}
