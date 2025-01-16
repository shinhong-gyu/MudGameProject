#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem("Resume Game", []() {Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() {Game::Get().QuitGame(); }));

	itemCount = (int)items.size();
}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		delete item;
	}

	items.clear();
}

void MenuLevel::Update(float deltaTime)
{

	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}
	if (Game::Get().GetKeyDown(VK_UP))
	{
		// 인덱스 변환
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 변환
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	// 엔터
	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		items[currentSelectedIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{
	Super::Draw();

	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unselectedColr);
	cout << "Text Scroll Demo Menu \n\n";

	// 루프 순회하면서 메뉴 텍스트 출력.
	for (int i = 0; i < itemCount; ++i)
	{
		SetConsoleTextAttribute(handle, i == currentSelectedIndex ? selectedColr : unselectedColr);
		cout << items[i]->text << "\n";
	}

}
