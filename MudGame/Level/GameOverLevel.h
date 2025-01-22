#pragma once

#include "Level/Level.h"
#include "Container/List.h"
#include "Engine/Timer.h"

struct EndMenuItem
{
	using OnSelected = void (*)();

	EndMenuItem(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		menuText = new char[length + 1];
		strcpy_s(menuText, length + 1, text);

		this->onSelected = onSelected;
	}

	~EndMenuItem()
	{
		delete[] menuText;
	}

	char* menuText;
	OnSelected onSelected;
};

class GameOverLevel : public Level
{
	RTTI_DECLARATIONS(GameOverLevel, Level)

public:
	GameOverLevel();
	~GameOverLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void TimerWork() {timer->bActive = true;}

private:
	int currentIndex = 0;
	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	vector<EndMenuItem*> menuItems;
	int length = 0;

	Timer* timer = new Timer(3.0f);

	bool bOnce = false;
};