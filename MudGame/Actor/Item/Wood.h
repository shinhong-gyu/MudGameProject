#pragma once
#include "Item.h"

class Wood : public Item
{
	RTTI_DECLARATIONS(Wood, Item)
public:
	Wood();

	virtual void Use() override;
private:
	
};