#include "BattleScene.h"
#include "Engine/Engine.h"
#include <thread>
#include <tchar.h>
#include <cmath>
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Item/Meat.h"
#include "Actor/Item/Item.h"
#include "Actor/Item/Weapon/Weapon.h"


BattleScene::BattleScene()
{
	vector<wstring> image;
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢔⢇⢇⢗⡕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢆⠇⡧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⡹⡸⡸⡸⡰⡩⣂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡐⣷⢙⠪⠂⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠎⢎⢎⢆⢇⢇⢕⢕⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⣎⢪⢪⠊⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⡔⡮⣳⢱⢱⢱⢱⢱⢱⢢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢱⢱⢳⠅⠪⡨⠨⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣢⡲⡝⣎⢞⣜⢮⢣⢣⢣⢣⢱⢱⢑⢕⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢇⢣⢱⢑⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠊⠚⠊⠓⣑⢇⢇⢇⢇⢇⢇⢇⢇⢇⢝⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸⣘⢌⣎⢮⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡺⡸⣸⡸⣜⢜⢜⢜⢜⢜⢜⢜⢜⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢎⢇⢎⠎⠲⡕⡵⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⢰⢣⡳⡝⡮⠮⠪⡎⡎⡎⡎⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠺⡸⠘⠀⠀⠀⠘⢬⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢳⡱⣝⠎⠀⠀⠣⡣⡣⣓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠑⠕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠉⠀⠀⠀⠀⠀⠘⠪⠒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");

	images.push_back(image);

	idx = Random(0, 2) % 3;



	selections.push_back(new Selection("맨손 격투(이길 확률 10%)", []() {
		float randNo = RandomPercent(0, 1);
		if (randNo >= 0.1)
		{
			Game::Get().player->SetHP(Game::Get().player->GetHP() - 3);
			Game::Get().PrintLoseImage();
		}
		else
		{
			Game::Get().player->AddToInventory(new Meat("고 기", Game::Get().player), 1);
			Game::Get().PrintWinImage();
		}
		}));
	selections.push_back(new Selection("도망치기", []()
		{
			Game::Get().PrintRunImage();
			if (auto* battleL = dynamic_cast<BattleScene*>(Game::Get().GetLevel()))
			{
				battleL->bIsExpired = false;
				battleL->timer->Reset();
				battleL->timer->bActive = false;
				battleL->bShowWeaponList = false;
				battleL->bOnce = false;
			}
		}));
}

void BattleScene::Update(float deltaTime)
{
	timer->Update(deltaTime);

	weaponList = Game::Get().player->GetItemListByType(ItemType::Weapon);

	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().BackToMainLevel();
		bShowWeaponList = false;
		timer->Reset();
		timer->bActive = false;
		bIsExpired = false;
	}

	if (Game::Get().GetKeyDown(VK_LEFT))
	{
		if (bShowWeaponList)
		{
			currentWeaponIndex = (currentWeaponIndex - 1 + (int)weaponList.size()) % (int)weaponList.size();
		}
		else
		{
			currentIndex = (currentIndex - 1 + (int)selections.size()) % (int)selections.size();
		}
	}
	if (Game::Get().GetKeyDown(VK_RIGHT))
	{
		if (bShowWeaponList)
		{
			currentWeaponIndex = (currentWeaponIndex + 1) % (int)weaponList.size();
		}
		else
		{
			currentIndex = (currentIndex + 1) % (int)selections.size();
		}
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		if (bIsExpired) return;

		if (bShowWeaponList)
		{
			weaponList[currentWeaponIndex]->Use();
			bShowWeaponList = !bShowWeaponList;
			timer->bActive = true;
			bIsExpired = true;

			return;
		}
		selections[currentIndex]->onSelected();
		if (!bShowWeaponList)
		{
			timer->bActive = true;
			bIsExpired = true;
		}
	}
	if (timer->IsTimeOut())
	{
		Game::Get().BackToMainLevel();
		bIsExpired = false;
		timer->Reset();
		timer->bActive = false;
		bOnce = false;
	}

	if (!bIsExpired && Game::Get().player->SearchItemByType(ItemType::Weapon) && !bOnce)
	{
		bOnce = true;
		for (auto& s : selections)
		{
			if (strcmp(s->selection, "무기 사용") == 0) {
				return;
			}
		}

		selections.push_back(new Selection(("무기 사용"), []()
			{
				if (auto* battleL = dynamic_cast<BattleScene*>(Game::Get().GetLevel()))
				{
					battleL->bShowWeaponList = true;
					battleL->currentIndex = 0;

					system("cls");
				}
			}
		));
	}
}

void BattleScene::Draw()
{
	if (bIsExpired)
	{
		return;
	}

	SetColor(Color::White);

	Engine::Get().SetCursorPosition(22, 0);
	cout << "곰을 만났다.";

	SetConsoleOutputCP(CP_UTF8);

	Engine::Get().SetCursorPosition(0, 1);
	// 콘솔 화면 초기화

	for (const auto& line : images[0])
	{
		wcout << line << L"\n";
	}
	Log("__________________________________________________________________________");

	SetColor(unselectedColor);

	SetConsoleOutputCP(949);

	if (!bShowWeaponList)
	{
		int count = 0;
		for (int ix = 0; ix < selections.size(); ++ix)
		{
			count++;
			SetColor(ix == currentIndex ? selectedColor : unselectedColor);
			cout << "\t" << selections[ix]->selection << "\t";
			if (count == 2)
			{
				count = 0;
				cout << "\n";
			}
		}
		cout << "\n";
	}
	else
	{
		for (int ix = 0; ix < weaponList.size(); ++ix)
		{
			SetColor(ix == currentWeaponIndex ? selectedColor : unselectedColor);
			cout << "\t" << weaponList[ix]->GetName() << "\t";
		}
	}
}


