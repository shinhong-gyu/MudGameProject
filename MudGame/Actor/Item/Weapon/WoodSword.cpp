#include "WoodSword.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "../Meat.h"

WoodSword::WoodSword()
	: Weapon("목 검")
{
	itemType = ItemType::Weapon;
}

void WoodSword::Use()
{
	float randNo = RandomPercent(0.0f, 1.0f);
	if (randNo <= 0.2f)
	{
		Game::Get().player->SetHP(Game::Get().player->GetHP() - 3);
		Game::Get().PrintLoseImage();
	}
	else
	{
		Game::Get().player->AddToInventory(new Meat("고 기", Game::Get().player), 1);
		Game::Get().PrintWinImage();
	}
}
