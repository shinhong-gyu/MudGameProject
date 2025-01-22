#pragma once
#include "Item.h"


class Medicine : public Item
{
	RTTI_DECLARATIONS(Medicine, Item)

public:
	Medicine(const char* name, Player* owner);
	virtual void Use() override;
private:
};