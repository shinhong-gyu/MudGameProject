#include "Weapon.h"

Weapon::Weapon(const char* name,float demage)
	:Item(name),demage(demage)
{
	itemType = ItemType::Weapon;
}
