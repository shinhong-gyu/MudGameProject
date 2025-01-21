#include "CraftLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Item/Weapon/Club.h"
#include "Actor/Item/Weapon/WoodSword.h"

CraftLevel::CraftLevel()
{
	recipeList.push_back(new Recipe("���� ������", []()
		{
			if (2 <= Game::Get().player->GetQuantity("�� ��"))
			{
				Game::Get().player->RemoveFromInventory("����", 2);
				Game::Get().player->AddToInventory(new Club(), 1);
				system("cls");
				Log("\t���� ������ ���� ���� ! ");
			}
			else
			{
				system("cls");
				Log("\t���� ������ ���� ����... ");
			}
		}
	));
	recipeList.push_back(new Recipe("��   ��", []()
		{
			if (4 <= Game::Get().player->GetQuantity("�� ��"))
			{
				Game::Get().player->RemoveFromInventory("����", 4);
				Game::Get().player->AddToInventory(new WoodSword(), 1);
				system("cls");
				Log("\t��� ���� ���� ! ");
			}
			else
			{
				system("cls");
				Log("\t��� ���� ����... ");
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
	Log("\t\t\t   ���չ�");
	SetColor(Color::White);
	Log("\t���� ������\t->\t���� + ����");
	Log("\t ��   ��  \t->\t���� + ���� + ���� + ����");
	Log("______________________________________________________________________________");
	SetColor(Color::Blue);
	Log("\t\t\t   �� ��");

	for (int ix = 0; ix < 2; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		cout << "\t" << recipeList[ix]->recipe << "\t";
	}
	cout << "\n";
}
