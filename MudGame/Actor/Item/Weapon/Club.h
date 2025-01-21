#pragma once
#include "Weapon.h"

class Club : public Weapon
{
	RTTI_DECLARATIONS(Club, Weapon)
public:
	Club();
	virtual void Use() override;
private:
};