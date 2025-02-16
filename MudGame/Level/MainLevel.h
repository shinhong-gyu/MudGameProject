#pragma once
#pragma once
#include "Level/Level.h"
#include "Container/List.h"
#include "Actor/DrawableActor.h"


class Actor;
class Player;
class Tree;
class Animal;

enum class ModeType
{
	MODE_Play = 0,
	MODE_Inventory= 1,
};


class MainLevel :public Level
{
	RTTI_DECLARATIONS(MainLevel, Level)
public:
	MainLevel(vector<vector<char>> map);

	~MainLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


	void RandomTreeGrow();
	void RandomAnimalAppear();
	Animal* IsAnimal(const Vector2& pos);

	void SetMap(vector<vector<char>> map);

	Tree* IsTree(const Vector2& pos);
	bool IsGround(const Vector2& pos);

	void ChoppingTree(const Vector2& pos);
	void HuntAnimal(const Vector2& pos);

	void PrintImage(int printCode);

	Player* player = nullptr;

	bool bPopUpImage = false;

private:
	vector<Tree*> trees;

	vector<Animal*> animals;

	vector<DrawableActor*> map;

	Timer* timer = new Timer(2.0f);
	Timer* mapEventTimer = new Timer(5.0f);

	float imageClearTime = 3.0f;

	// 한 줄씩 저장할 벡터
	vector<vector<wstring>> images;

	bool bToggle = false;

	int maxTreeCount = 50;
	int maxAnimalCount = 10;

	int treeCnt = 0;
	int animalCnt = 0;

	ModeType mode = ModeType::MODE_Play;

	int currentIndex = 0;

	Color unselectedColor = Color::White;
	Color selectedColor = Color::Green;

	int day = 0;
	float dayCount = 0; 
};