#pragma once
#include "Actor/DrawableActor.h"

class Animal : public DrawableActor
{
	RTTI_DECLARATIONS(Animal, DrawableActor)
public:
	Animal(const Vector2& position);
private:
};