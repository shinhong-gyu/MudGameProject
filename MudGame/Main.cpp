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

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::wcout.imbue(std::locale("en_US.UTF-8"));

	Game game;
	game.LoadLevel(new MenuLevel());
	//game.SetMap();
	game.Run();
}