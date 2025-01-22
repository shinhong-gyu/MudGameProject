#pragma once
#include "Level/Level.h"
#include <vector>
#include <string>
#include "Engine/Timer.h"

using namespace std;

struct Selection
{
	using OnSelected = void (*)();

	Selection(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		selection = new char[length + 1];
		strcpy_s(selection, length + 1, text);

		this->onSelected = onSelected;
	}

	~Selection()
	{
		delete[] selection;
	}

	char* selection;
	OnSelected onSelected;
};

class BattleScene : public Level
{
	RTTI_DECLARATIONS(BattleScene, Level)
	friend class Game;

public:
	BattleScene();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	vector<vector<wstring>> images;

	int idx = 0;

	int currentWeaponIndex = 0;
	int currentIndex = 0;

	Color unselectedColor = Color::White;
	Color selectedColor = Color::Green;

	Timer* timer = new Timer(2.0f);

	bool bIsExpired = false;
	bool bShowWeaponList= false;
	bool bOnce = false;

	vector<Selection*> selections;

	vector<class Item*> weaponList;

};