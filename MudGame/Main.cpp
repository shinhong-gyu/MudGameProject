#include <vector>
#include <locale>
#include <fcntl.h>
#include <tchar.h>
#include <io.h>
#include <Windows.h>
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Container/List.h"
#include "Level/MainLevel.h"

int main()
{
	std::wcout.imbue(std::locale("en_US.UTF-8"));

	Game game;
	game.LoadLevel(new MenuLevel());
	//game.SetMap();
	game.Run();
}