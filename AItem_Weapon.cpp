#include "AItem_Weapon.h"
#include "EnemyManager.h"
#include "Engine/ACharacter.h"
AItem_Weapon::AItem_Weapon(Actor* _instigator, LAZY::TRANSFORM transform, const char* name, int offset_X, int offset_Y, Weapon_Behaviour _behaviour, int _dmg)
{
	ammo = 200;

	instigator = _instigator;
	spawnPosition = transform;
	itemName = name;
	type = ITEM_TYPE::WEAPON;
	quantity = 1;

	obtained = false;
	CreateActor(spawnPosition, ITEMS_GX_PATH);
	m_worldRect = spawnPosition;
	behaviour = _behaviour;
	m_rect.w = spawnPosition.w;
	m_rect.h = spawnPosition.h;
	m_offX = offset_X;
	m_offY = offset_Y;
	dmg = _dmg;
	bulletList = std::vector<ABullet*>();
	textRender = UIText(name, "./assets/fonts/Mulish-Regular.ttf", 14, { 25,10,0,0 }, { 255,255,255 });

}

AItem_Weapon::~AItem_Weapon()
{
}

void AItem_Weapon::Fire()
{
	printf("Fired!\n");
	ACharacter* player = (ACharacter*)instigator;
	if (behaviour == Weapon_Behaviour::Melee)
	{
		LAZY::TRANSFORM* playerbox = instigator->GetWorldRect();
		LAZY::TRANSFORM hitbox; 
		switch (instigator->GetLookingDirection())
		{
		case 0:
			hitbox = { playerbox->x + 0, playerbox->y + 16, 16, 10 };
			break;
		case 1:
			hitbox = { playerbox->x - 10, playerbox->y + 0, 10, 16 };
			break;
		case 2:
			hitbox = { playerbox->x + 0, playerbox->y - 10, 16, 10 };
			break;
		case 3:
			hitbox = { playerbox->x + 16, playerbox->y + 0, 10, 16 };
			break;
		default:
			break;
		}
		//PRINT_TRANSFORM_(hitbox)
		EnemyManager::getInstance()->Hit(hitbox, 20);
	}
	else if (behaviour == Weapon_Behaviour::Handgun)
	{
		AddBullet(instigator->GetLookingDirection());
	}
}

void AItem_Weapon::AddBullet(int direction)
{
	LAZY::TRANSFORM* instigatorbox = instigator->GetWorldRect();
	if (AEnemy* check = dynamic_cast<AEnemy*>(instigator)) {
		//Is enemy
		bulletList.push_back(new ABullet(false, { instigatorbox->x + (instigatorbox->w / 2), instigatorbox->y + (instigatorbox->h / 2) , 8,8,0 }, direction, 1, dmg));
	}
	else if (ACharacter* check = dynamic_cast<ACharacter*>(instigator)) {
		//Is Player
		bulletList.push_back(new ABullet(true,{ instigatorbox->x + (instigatorbox->w / 2), instigatorbox->y + (instigatorbox->h / 2) , 8,8,0 }, direction, 1, dmg));

	}
	else
	{
		return;
	}
}


void AItem_Weapon::Update()
{

	AItem::Update();
	for (unsigned int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->Update();
	}
}

void AItem_Weapon::Render()
{

	AItem::Render();
	for (unsigned int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->Render();
	}
}
