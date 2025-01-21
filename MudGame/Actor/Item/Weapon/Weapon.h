#pragma once
#include "../Item.h"


class Weapon : public Item
{
	RTTI_DECLARATIONS(Weapon, Item)

public:
	Weapon(const char* name, float demage);

	virtual void Use() = 0;
protected:
	float demage = 0;
};