#include "Meat.h"
#include "Actor/Player.h"

Meat::Meat(const char* name)
	:Item(name)
{
	itemType = ItemType::Meat;
}

void Meat::Use()
{
	owner->SetStarve(owner->GetStarve() + 1);
}
