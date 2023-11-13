#pragma once
#include "./Engine/Actor.h"
#include "Items.h"
#include "Engine/UIText.h"

//1.Jugador a sobre
//2.Show UI 
// -- Picked up
// -- ItemNAME
//3.Pause Joc
//4.wait for input
//5.En el transcriber mostrar info del objecte recollit

enum ITEM_TYPE
{
	WEAPON, UTILITY
};
class AItem : public Actor
{
protected:
	Actor* instigator;
	LAZY::TRANSFORM spawnPosition;
	ITEM_TYPE type;
	const char* itemName;
	bool obtained;
	int m_offX, m_offY;
	int quantity;
	UIText textRender;
public:
	bool showNotification;
	
	AItem();
	AItem(Actor* playerref, LAZY::TRANSFORM transform, const char * name, ITEM_TYPE _type, int offset_X = 0, int offset_Y = 0);
	AItem(Actor* playerref, LAZY::TRANSFORM transform, E_Items e_itemname, ITEM_TYPE _type, int offset_X = 0, int offset_Y = 0);

	~AItem();

	const char* GetName() { return itemName; };
	bool ToggleNotification() {
		showNotification = !showNotification;
		return showNotification;
	}
	void Update();
	void Render();
	bool CheckIfPlayerIsOnTop();
	ITEM_TYPE GetType() { return type; };

	void AddToQuantity() { quantity++; };
	void RemoveToQuantity() { quantity--; };
	int GetQuantity() { return quantity; };
	void RenderAsUI();
	void RenderAsInventory(int x, int y);
	void RenderName(int x, int y);
	void SetObtained(bool _val) {
		obtained = _val;
	};
};

