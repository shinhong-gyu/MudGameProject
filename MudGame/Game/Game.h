#pragma once

#include <Engine/Engine.h>
#include <fstream>
#include <vector>

using namespace std;

class Player;

class Game : public Engine
{
public:
	Game();
	~Game();

	void InitGame();

	vector<vector<char>> CreateRandomMap();

	void ToggleMenu();
	void CraftMode();

	void SetMap();

	void IntoBattleScene();

	void BackToMainLevel();

	void PrintLoseImage();

	void PrintWinImage();

	static Game& Get() { return *instance; }

	Player* player;

private:
	bool bShowMenu = false;
	
	Level* menuLevel = nullptr;
	Level* craftLevel = nullptr;
	Level* backLevel = nullptr;
	Level* battleScene = nullptr;

	vector<wstring> loseImage;
	vector<wstring> winImage;
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
