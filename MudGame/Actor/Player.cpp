#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector2.h"
#include "Level/MainLevel.h"
#include "Game/Game.h"
#include "Tree.h"
#include "Animal.h"

#include <algorithm>


Player::Player(const char* image)
	: Super(image)
{
}

Player::Player(const Vector2& position, const char* image)
	: DrawableActor(image)
{
	this->position = position;

	color = Color::Purple;

	starveTimer->bActive = true;
	starveTimer->SetTimer(12.0f);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 메뉴 토글
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		SetConsoleOutputCP(949);
		if (auto* level = dynamic_cast<MainLevel*>(Engine::Get().GetLevel()))
		{
			if (level->bPopUpImage)
			{
				level->bPopUpImage = false;
				system("cls");
			}
			else
			{
				Game::Get().ToggleMenu();
			}
		}
		else
		{
			Game::Get().ToggleMenu();
		}
	}

	if (!bGetControl) return;

	starveTimer->Update(deltaTime);

	if (starveTimer->IsTimeOut())
	{
		if (starve > 0)
		{
			starve--;
		}
		else
		{
			hp--;
			starveTimer->SetTimer(9.0f);
		}
		starveTimer->Reset();
	}
	// 엔진의 mainLevel을 가져와서 MainLevel로 캐스팅
	auto* curLevel = Engine::Get().GetLevel()->As<MainLevel>();

	// MainLevel이 아닌 상태라면 return 
	if (curLevel == nullptr) return;

	if (curLevel->bPopUpImage) return;

	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		// 나무 쪽으로 이동하려면 나무와 인터렉션
		if (auto* tree = curLevel->IsTree(Vector2(position.x - 1, position.y)))
		{
			tree->TriggerTreeEvent();
			curLevel->ChoppingTree(tree->Position());
			return;
		}

		if (auto* animal = curLevel->IsAnimal(Vector2(position.x - 1, position.y)))
		{
			Game::Get().IntoBattleScene();
			curLevel->HuntAnimal(animal->Position());
			return;
		}



		// 가려는 곳이 갈 수 있는 곳인지 검사
		if (!curLevel->IsGround(Vector2(position.x - 1, position.y)))
			return;


		position.x -= 1;
		position.x = position.x < 0 ? 0 : position.x;
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// 나무 쪽으로 이동하려면 나무와 인터렉션
		if (auto* tree = curLevel->IsTree(Vector2(position.x + 1, position.y)))
		{
			
			curLevel->ChoppingTree(tree->Position());
			tree->TriggerTreeEvent();
			return;
		}

		if (auto* animal = curLevel->IsAnimal(Vector2(position.x + 1, position.y)))
		{
			Game::Get().IntoBattleScene();
			curLevel->HuntAnimal(animal->Position());
			return;
		}


		// 가려는 곳이 갈 수 있는 곳인지 검사
		if (!curLevel->IsGround(Vector2(position.x + 1, position.y))) return;


		position.x += 1;
		position.x = position.x > Engine::Get().ScreenSize().x ? Engine::Get().ScreenSize().x : position.x;
	}
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		// 나무 쪽으로 이동하려면 나무와 인터렉션
		if (auto* tree = curLevel->IsTree(Vector2(position.x, position.y - 1)))
		{
			curLevel->ChoppingTree(tree->Position());
			tree->TriggerTreeEvent();
			return;
		}

		if (auto* animal = curLevel->IsAnimal(Vector2(position.x, position.y - 1)))
		{
			Game::Get().IntoBattleScene();
			curLevel->HuntAnimal(animal->Position());
			return;
		}

		// 가려는 곳이 갈 수 있는 곳인지 검사
		if (!curLevel->IsGround(Vector2(position.x, position.y - 1))) return;


		position.y -= 1;
		position.y = position.y < 0 ? 0 : position.y;
	}
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		// 나무 쪽으로 이동하려면 나무와 인터렉션
		if (auto* tree = curLevel->IsTree(Vector2(position.x, position.y + 1)))
		{
			curLevel->ChoppingTree(tree->Position());
			tree->TriggerTreeEvent();
			return;
		}

		if (auto* animal = curLevel->IsAnimal(Vector2(position.x, position.y + 1)))
		{
			Game::Get().IntoBattleScene();
			curLevel->HuntAnimal(animal->Position());
			return;
		}

		// 가려는 곳이 갈 수 있는 곳인지 검사
		if (!curLevel->IsGround(Vector2(position.x, position.y + 1))) return;

		position.y += 1;
		position.y = position.y > Engine::Get().ScreenSize().y ? Engine::Get().ScreenSize().y : position.y;
	}
}

void Player::AddToInventory(Item* item, int quantity)
{
	for (SlotStruct& slot : inventory)
	{
		if (strcmp(slot.item->GetName(), item->GetName()) == 0)
		{
			slot.quantity += quantity;
			return;
		}
	}

	SlotStruct slot;

	slot.item = item;
	slot.quantity = quantity;

	inventory.push_back(slot);
}

void Player::RemoveFromInventory(const char* name, int quantity)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		SlotStruct& slot = inventory[i];
		if (strcmp(slot.item->GetName(), name) == 0)
		{
			slot.quantity -= quantity;
			if (slot.quantity <= 0) {
				inventory.erase(inventory.begin() + i);
				bInventoryChanged = true;
			}
			return;
		}
	}
}

bool Player::SearchItemByType(ItemType type)
{
	for (auto& slot : inventory)
	{
		if (slot.item->GetItemType() == type) return true;
	}
	return false;
}

vector<Item*> Player::GetItemListByType(ItemType type)
{
	vector<Item*> temp;

	for (auto& slot : inventory)
	{
		if (slot.item->GetItemType() == type)
		{
			temp.push_back(slot.item);
		}
	}

	return temp;
}

int Player::GetQuantity(const char* name)
{
	for (auto& slot : inventory)
	{
		if (strcmp(slot.item->GetName(), name) == 0)
		{
			return slot.quantity;
		}
	}
	return -1;
}
