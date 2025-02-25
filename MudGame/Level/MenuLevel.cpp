#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	menuItems.push_back(new MenuItem("게임 시작", []() { Game::Get().InitGame(); }));
	menuItems.push_back(new MenuItem("게임 종료", []() { Game::Get().QuitGame(); }));
	menuItems.push_back(new MenuItem("게임 이어서 하기", []() { Game::Get().ToggleMenu(); }));

	length = (int)menuItems.size();
}

MenuLevel::~MenuLevel()
{
	for (auto* item : menuItems)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
}

void MenuLevel::Update(float deltaTime)
{
	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{
	Super::Draw();

	Engine::Get().SetCursorPosition(0, 0);

	SetColor(unselectedColor);

	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n", menuItems[ix]->menuText);
	}
}