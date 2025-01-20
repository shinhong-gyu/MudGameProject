#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector2.h"
#include "Level/MainLevel.h"
#include "Game/Game.h"
#include "Tree.h"

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
	starveTimer->SetTimer(15.0f);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
	starveTimer->Update(deltaTime);

	// 메뉴 토글
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		SetConsoleOutputCP(949);
		Game::Get().ToggleMenu();
	}

	if (starveTimer->IsTimeOut())
	{
		starve--;
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
		if (slot.item->GetItemType() == item->GetItemType())
		{
			slot.quantity += quantity;
			return;
		}
	}

	SlotStruct slot;

	slot.item = item;
	slot.quantity = quantity;

	inventory.PushBack(slot);
}
