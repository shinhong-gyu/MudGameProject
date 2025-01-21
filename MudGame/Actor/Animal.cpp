#include "Animal.h"

Animal::Animal(const Vector2& position)
	:DrawableActor("A")
{
	this->position = position;

	SetColor(Color::Red);
}
