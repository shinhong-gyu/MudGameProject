#pragma once
#include "Item.h"

class Meat : public Item
{
	RTTI_DECLARATIONS(Meat, Item)
public:
	Meat(const char* name,Player* owner);
	virtual void Use() override;
private:
};