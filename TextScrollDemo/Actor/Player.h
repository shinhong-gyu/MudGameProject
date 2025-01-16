#pragma once

#include "Actor/DrawableActor.h"

class Player :public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)
public:
	Player(char image = 'p');

	virtual void Update(float deltaTime) override;

};