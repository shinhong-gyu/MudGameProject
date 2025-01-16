#pragma once

#include "Level/Level.h"
#include <vector>
#include <Windows.h>

// 메뉴 아이템.
struct MenuItem
{
	// 이벤트 선언
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;

		this->text = new char[length];

		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		delete[] text;
	}
	// 메뉴에서 보여줄 텍스트.
	char* text;

	// 선택했을 때 실행할 함수를 저장하는 포인터.
	OnSelected onSelected;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// 현재 선택된 메뉴 번호(인덱스).
	int currentSelectedIndex = 0;

	// 선택된 메뉴의 색상.
	int selectedColr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	int unselectedColr = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;

	vector<MenuItem*> items;

	int itemCount = 0;
};