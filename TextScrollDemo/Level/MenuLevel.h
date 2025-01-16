#pragma once

#include "Level/Level.h"
#include <vector>
#include <Windows.h>

// �޴� ������.
struct MenuItem
{
	// �̺�Ʈ ����
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
	// �޴����� ������ �ؽ�Ʈ.
	char* text;

	// �������� �� ������ �Լ��� �����ϴ� ������.
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
	// ���� ���õ� �޴� ��ȣ(�ε���).
	int currentSelectedIndex = 0;

	// ���õ� �޴��� ����.
	int selectedColr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	int unselectedColr = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;

	vector<MenuItem*> items;

	int itemCount = 0;
};