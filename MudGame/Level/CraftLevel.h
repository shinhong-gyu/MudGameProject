#pragma once
#include "Level/Level.h"
#include "Engine/Timer.h"

struct Recipe
{
	using OnSelected = void (*)();

	Recipe(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		recipe = new char[length + 1];
		strcpy_s(recipe, length + 1, text);

		this->onSelected = onSelected;
	}

	~Recipe()
	{
		delete[] recipe;
	}

	char* recipe;
	OnSelected onSelected;
};

class CraftLevel : public Level
{
	RTTI_DECLARATIONS(CraftLevel, Level)

public:
	CraftLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	vector<Recipe*> recipeList;

	int currentIndex = 0;

	Color unselectedColor = Color::White;
	Color selectedColor = Color::Green;

	bool bIsExpired = false;

	Timer* timer = new Timer(2.0f);
	vector<wstring> clubImage;
	vector<wstring> woodSwordImage;

};