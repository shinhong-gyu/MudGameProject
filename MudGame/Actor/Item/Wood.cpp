#include "Wood.h"

Wood::Wood()
{
	itemType = ItemType::Wood;

	int length = strlen("목재") + 1;

	this->name = new char[length];

	strcpy_s(this->name,length,"목재");
}

void Wood::Use()
{
}
