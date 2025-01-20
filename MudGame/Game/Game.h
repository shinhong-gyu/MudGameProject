#pragma once

#include <Engine/Engine.h>
#include <fstream>
#include <vector>

using namespace std;

class Game : public Engine
{
public:
	Game();
	~Game();

	void InitGame();

	vector<vector<char>> CreateRandomMap();

	void ToggleMenu();

	void SetMap();

	void IntoBattleScene();

	void BackToMainLevel();

	static Game& Get() { return *instance; }

private:
	bool bShowMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;
	Level* battleScene = nullptr;

private:
	static Game* instance;
};


// Save?
class GameLogger {
public:
	static GameLogger& Get() {
		static GameLogger instance;
		return instance;
	}

private:
	ofstream w_File;
	ifstream r_File;
};
