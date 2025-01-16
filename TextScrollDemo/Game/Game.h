#pragma once

#include "Engine/Engine.h"

class Game :public Engine
{
public:
	Game();
	~Game();

	// 메뉴씬-데모씬 전환함수
	void ToggleMenu();

	static Game& Get()
	{
		// Lazy Singleton Pattern.
		//static Game* instance = new Game();
		//return *instance;
		
		return *instance;
	}

private:
	// 메뉴를 보여주고 있는지를 나타내는 변수
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;
	
	// 싱글톤 구현 객체.
	static Game* instance;

};