#pragma once
#include "Actor/DrawableActor.h"

enum class ItemType :unsigned short
{
	Wood = 1,
	Meet = 2,
	Weapon = 3,
};



class Item : public DrawableActor
{
	RTTI_DECLARATIONS(Item, DrawableActor)
public:
	Item(const char* name);
	virtual ~Item();

	virtual void Use() = 0;
	char* GetName() const { return name; }
	ItemType GetItemType() const { return itemType; }
protected:
	ItemType itemType = ItemType::Wood;
	char* name = nullptr;
};