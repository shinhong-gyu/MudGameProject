#include "Item.h"

Item::Item(const char* name)
{
	size_t length = strlen(name) + 1;

	this->name = new char[length];

	strcpy_s(this->name, length, name);
}

Item::~Item()
{
	delete[] name;
}
