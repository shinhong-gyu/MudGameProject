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
		// �ε��� ��ȯ
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		// �ε��� ��ȯ
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	// ����
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

	// ���� ��ȸ�ϸ鼭 �޴� �ؽ�Ʈ ���.
	for (int i = 0; i < itemCount; ++i)
	{
		SetConsoleTextAttribute(handle, i == currentSelectedIndex ? selectedColr : unselectedColr);
		cout << items[i]->text << "\n";
	}

}
