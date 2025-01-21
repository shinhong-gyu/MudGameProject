#include "Wood.h"

Wood::Wood(const char* name)
	: Item(name)
{
	itemType = ItemType::Wood;

	size_t length = strlen("목재") + 1;

	this->name = new char[length];

	strcpy_s(this->name, length, "목재");
}

void Wood::Use()
{
}
