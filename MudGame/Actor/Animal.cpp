#include "Animal.h"

Animal::Animal(const Vector2& position)
	:DrawableActor("@")
{
	this->position = position;

	SetColor(Color::Red);
}
