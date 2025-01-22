#pragma once
#include "Actor/DrawableActor.h"

enum class ItemType :unsigned short
{
	Wood = 1,
	Meat = 2,
	Weapon = 3,
	Medicine = 4,
};


class Player;

class Item : public DrawableActor
{
	RTTI_DECLARATIONS(Item, DrawableActor)
public:
	Item(const char* name, Player* value=nullptr);
	virtual ~Item();

	virtual void Use() = 0;
	char* GetName() const { return name; }
	ItemType GetItemType() const { return itemType; }

	void SetOwner(Player* value) { owner = value; }

protected:
	ItemType itemType = ItemType::Wood;
	char* name = nullptr;

	Player* owner = nullptr;
};