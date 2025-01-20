#pragma once
#include "Level/Level.h"
#include "Container/List.h"
#include "Actor/DrawableActor.h"


class Actor;
class Player;
class Tree;
class Animal;


class MainLevel :public Level
{
	RTTI_DECLARATIONS(MainLevel, Level)
public:
	MainLevel();
	MainLevel(vector<vector<char>> map);

	~MainLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


	void RandomTreeGrow();
	void RandomAnimalAppear();

	void SetMap(vector<vector<char>> map);

	bool IsGround(const Vector2& pos);
	Tree* IsTree(const Vector2& pos);
	Animal* IsAnimal(const Vector2& pos);

	void ChoppingTree(const Vector2& pos);
	void PrintImage(int printCode);

	Player* player = nullptr;

	bool bPopUpImage = false;

private:
	List<Tree*> trees;

	List<Animal*> animals;

	List<DrawableActor*> map;

	Timer* timer = new Timer(2.0f);
	Timer* mapEventTimer = new Timer(15.0f);

	float imageClearTime = 3.0f;

	// 한 줄씩 저장할 벡터
	vector<vector<wstring>> images;

	bool bToggle = false;

	int maxTreeCount = 50;
	int maxAnimalCount = 10;

	int treeCnt = 0;
	int animalCnt = 0;

};