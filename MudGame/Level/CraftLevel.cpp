#include "CraftLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Item/Weapon/Club.h"
#include "Actor/Item/Weapon/WoodSword.h"

CraftLevel::CraftLevel()
{
	recipeList.push_back(new Recipe("나무 몽둥이", []()
		{
			if (2 <= Game::Get().player->GetQuantity("목 재"))
			{
				Game::Get().player->RemoveFromInventory("목재", 2);
				Game::Get().player->AddToInventory(new Club(), 1);
				system("cls");
				Log("\t나무 몽둥이 제작 성공 ! ");
			}
			else
			{
				system("cls");
				Log("\t나무 몽둥이 제작 실패... ");
			}
		}
	));
	recipeList.push_back(new Recipe("목   검", []()
		{
			if (4 <= Game::Get().player->GetQuantity("목 재"))
			{
				Game::Get().player->RemoveFromInventory("목재", 4);
				Game::Get().player->AddToInventory(new WoodSword(), 1);
				system("cls");
				Log("\t목검 제작 성공 ! ");
			}
			else
			{
				system("cls");
				Log("\t목검 제작 실패... ");
			}
		}
	));
}

void CraftLevel::Update(float deltaTime)
{
	timer->Update(deltaTime);

	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().BackToMainLevel();
	}

	if (Game::Get().GetKeyDown(VK_LEFT))
	{
		currentIndex = (currentIndex - 1 + recipeList.size()) % recipeList.size();
	}
	if (Game::Get().GetKeyDown(VK_RIGHT))
	{
		currentIndex = (currentIndex + 1) % recipeList.size();
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		timer->SetTimer(3.0f);
		timer->bActive = true;
		bIsExpired = true;
		recipeList[currentIndex]->onSelected();
	}

	if (timer->IsTimeOut())
	{
		Game::Get().BackToMainLevel();
		bIsExpired = false;
		timer->Reset();
		timer->bActive = false;
	}
}

void CraftLevel::Draw()
{
	if (bIsExpired) return;

	Engine::Get().SetCursorPosition(0, 0);

	SetColor(Color::Blue);

	Log("\t\t\t CRAFT MODE\n");
	SetColor(Color::Blue);
	Log("\t\t\t   조합법");
	SetColor(Color::White);
	Log("\t나무 몽둥이\t->\t목재 + 목재");
	Log("\t 목   검  \t->\t목재 + 목재 + 목재 + 목재");
	Log("______________________________________________________________________________");
	SetColor(Color::Blue);
	Log("\t\t\t   선 택");

	for (int ix = 0; ix < 2; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		cout << "\t" << recipeList[ix]->recipe << "\t";
	}
	cout << "\n";
}
