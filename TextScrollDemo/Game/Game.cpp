#include "Game.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	// 싱글톤 객체 설정
	instance = this;

	// 메뉴레벨 생성
	menuLevel = new MenuLevel();

	// 커서 보이지 않게 설정
	SetCursorType(CursorType::NoCursor);

}

Game::~Game()
{
	if (showMenu)
	{
		// Engine의 메인 레벨이 메뉴 레벨인 상태.
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// Engine 의 메인 레벨이 데모 레벨인 상태.
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	// 화면 지우기
	system("cls");

	//메뉴 플래그 값 뒤집기.
	showMenu = !showMenu;

	if (showMenu)
	{
		// 현재의 메인 레벨을 뒤에 저장
		backLevel = mainLevel;

		// 메인 레벨으ㄹ 메뉴 레벨로 전환.
		mainLevel = menuLevel;
	}
	else
	{
		// 메뉴를 감추는 경우
		// 뒤에 저장했던 데모 레벨을 다시 메인 레벨로 설정.
		mainLevel = backLevel;
	}
}
