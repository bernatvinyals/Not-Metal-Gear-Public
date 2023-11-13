#pragma once
#include "AItem.h"
#include "ABullet.h"
#include <vector>
enum Weapon_Mod
{
	NONE, SILENCIER
};
enum Weapon_Behaviour
{
	Melee, Handgun, Auto
};
class AItem_Weapon : public AItem
{
	int ammo;
	Weapon_Mod mod;
	Weapon_Behaviour behaviour;
	int dmg;
	std::vector<ABullet*> bulletList;

public:
	AItem_Weapon(Actor* _instigator, LAZY::TRANSFORM transform, const char* name, int offset_X = 0, int offset_Y = 0, Weapon_Behaviour _behaviour = Auto, int _dmg = 30);

	~AItem_Weapon();
	virtual void Fire() ;
	int GetAmmo() { return ammo; }
	void AddAmmo(int _val) { ammo += _val; };
	void AddBullet(int direction);
	void Render();
	void Update();

};

