#include "GameOverLevel.h"
#include "Game/Game.h"

GameOverLevel::GameOverLevel()
{
	menuItems.push_back(new EndMenuItem("예", []() { Game::Get().InitGame(); }));
	menuItems.push_back(new EndMenuItem("아니오", []() { Game::Get().QuitGame(); }));

	length = (int)menuItems.size();
	timer->bActive = false;
}

GameOverLevel::~GameOverLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void GameOverLevel::Update(float deltaTime)
{
	timer->Update(deltaTime);

	if (Game::Get().GetKeyDown(VK_LEFT))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_RIGHT))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
		timer->Reset();
		bOnce = false;
	}
}

void GameOverLevel::Draw()
{
	if (timer->IsTimeOut())
	{
		if (!bOnce)
		{
			bOnce = true;
			system("cls");
		}

		SetConsoleOutputCP(949);

		Engine::Get().SetCursorPosition(0, 0);

		SetColor(Color::Red);

		cout << "   게임을 다시 하시겠습니까?\n\n\t";

		SetColor(unselectedColor);

		for (int ix = 0; ix < length; ++ix)
		{
			SetColor(ix == currentIndex ? selectedColor : unselectedColor);
			cout << menuItems[ix]->menuText << "\t";
		}
	}
}
