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

static int g_nScreenIndex;//콘솔 접근 인덱스
static HANDLE g_hScreen[2];//콘솔2개
int g_numOfFrame;//누적 프레임
int g_numOfFPS;//분당 프레임



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



	selections.push_back(new Selection("맨손 격투", []() {
		float randNo = RandomPercent(0, 1);
		if (randNo >= 0.1)
		{
			Game::Get().player->SetHP(Game::Get().player->GetHP() - 1);
			Game::Get().PrintLoseImage();
		}
		else
		{
			Game::Get().player->AddToInventory(new Meat("고 기"), 1);
			Game::Get().PrintWinImage();
		}
		}));
	selections.push_back(new Selection("도망치기", []()
		{
			if (auto* battleL = dynamic_cast<BattleScene*>(Game::Get().GetLevel()))
			{
				battleL->bIsExpired = false;
				battleL->timer->Reset();
				battleL->timer->bActive = false;
				battleL->bShowWeaponList = false;
			}
			Game::Get().BackToMainLevel();
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
			currentWeaponIndex = (currentWeaponIndex - 1 + weaponList.size()) % weaponList.size();
		}
		else
		{
			currentIndex = (currentIndex - 1 + selections.size()) % selections.size();
		}
	}
	if (Game::Get().GetKeyDown(VK_RIGHT))
	{
		if (bShowWeaponList)
		{
			currentWeaponIndex = (currentWeaponIndex + 1) % weaponList.size();
		}
		else
		{
			currentIndex = (currentIndex + 1) % selections.size();
		}
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
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

	SetConsoleOutputCP(CP_UTF8);

	// 콘솔 화면 초기화
	SetColor(Color::White);
	Engine::Get().SetCursorPosition(0, 0);

	for (const auto& line : images[0])
	{
		wcout << line << L"\n";
	}
	Log("__________________________________________________________________________");

	SetColor(unselectedColor);

	SetConsoleOutputCP(949);

	if (!bShowWeaponList)
	{
		for (int ix = 0; ix < selections.size(); ++ix)
		{
			SetColor(ix == currentIndex ? selectedColor : unselectedColor);
			cout << "\t" << selections[ix]->selection << "\t";
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


