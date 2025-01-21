#include "Club.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Item/Meat.h"

Club::Club()
	: Super("³ª¹« ¸ùµÕÀÌ")
{
	itemType = ItemType::Weapon;
}

void Club::Use()
{
	float randNo = RandomPercent(0, 1);
	if (randNo >= 0.5)
	{
		Game::Get().player->SetHP(Game::Get().player->GetHP() - 1);
		Game::Get().PrintLoseImage();
	}
	else
	{
		Game::Get().player->AddToInventory(new Meat("°í ±â"), 1);
		Game::Get().PrintWinImage();
	}
}
