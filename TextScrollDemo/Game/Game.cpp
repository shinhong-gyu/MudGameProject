#include "Game.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	// �̱��� ��ü ����
	instance = this;

	// �޴����� ����
	menuLevel = new MenuLevel();

	// Ŀ�� ������ �ʰ� ����
	SetCursorType(CursorType::NoCursor);

}

Game::~Game()
{
	if (showMenu)
	{
		// Engine�� ���� ������ �޴� ������ ����.
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// Engine �� ���� ������ ���� ������ ����.
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	// ȭ�� �����
	system("cls");

	//�޴� �÷��� �� ������.
	showMenu = !showMenu;

	if (showMenu)
	{
		// ������ ���� ������ �ڿ� ����
		backLevel = mainLevel;

		// ���� �������� �޴� ������ ��ȯ.
		mainLevel = menuLevel;
	}
	else
	{
		// �޴��� ���ߴ� ���
		// �ڿ� �����ߴ� ���� ������ �ٽ� ���� ������ ����.
		mainLevel = backLevel;
	}
}
