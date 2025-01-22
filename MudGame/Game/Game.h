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

	void PrintRunImage();

	void GameOver();

	void AliveSuccess();

	Level* GetCraftLevel() const { return craftLevel; }


	static Game& Get() { return *instance; }

	Player* player;

private:
	bool bShowMenu = false;
	bool bGameOver = false;

	Level* craftLevel = nullptr;
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;
	Level* battleScene = nullptr;
	Level* gameOverLevel = nullptr;

	vector<wstring> loseImage;
	vector<wstring> winImage;
	vector<wstring> runImage;
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
