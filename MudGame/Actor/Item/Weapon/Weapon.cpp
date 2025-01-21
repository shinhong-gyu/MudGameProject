#include "Weapon.h"

Weapon::Weapon(const char* name)
	:Item(name)
{
	itemType = ItemType::Weapon;
}
