#pragma once

#include "Engine/Engine.h"

class Game :public Engine
{
public:
	Game();
	~Game();

	// �޴���-����� ��ȯ�Լ�
	void ToggleMenu();

	static Game& Get()
	{
		// Lazy Singleton Pattern.
		//static Game* instance = new Game();
		//return *instance;
		
		return *instance;
	}

private:
	// �޴��� �����ְ� �ִ����� ��Ÿ���� ����
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;
	
	// �̱��� ���� ��ü.
	static Game* instance;

};