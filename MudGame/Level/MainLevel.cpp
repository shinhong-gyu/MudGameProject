#include "MainLevel.h"
#include "Actor/Tree.h"
#include "Actor/Ground.h"
#include "Actor/Player.h"
#include "Engine/Timer.h"
#include "Actor/Animal.h"
#include "Game/Game.h"


#include <sstream>
#include <string>

MainLevel::MainLevel(vector<vector<char>> p_Map)
{
	Engine::Get().SetCursorType(CursorType::NoCursor);

	timer = new Timer(2.0f);
	mapEventTimer = new Timer(5.0f);
	mapEventTimer->bActive = true;

	int x = 0, y = 0;
	for (auto line : p_Map)
	{
		for (auto c : line)
		{
			if (c == '.')
			{
				auto* ground = new Ground(Vector2(x, y));
				map.push_back(ground);
				actors.push_back(ground);
			}
			else if (c == '#')
			{
				auto* tree = new Tree(Vector2(x, y));
				map.push_back(tree);
				trees.push_back(tree);
				actors.push_back(tree);
			}
			else if (c == 'P')
			{
				auto* ground = new Ground(Vector2(x, y));
				actors.push_back(ground);
				map.push_back(ground);

				player = new Player(Vector2(x, y));
				Game::Get().player = this->player;
				map.push_back(player);
				actors.push_back(player);
			}
			x++;
		}
		y++;
		x = 0;
	}

	//
	//
	// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢮⢝⡷⡈⢄⠢⢎⠡⠃⣧⢕⠡⡊⡘⣆⢂⡉⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// ⠀⠀⠀⠀⠀⠀⠀⢀⣀⢀⠀⢨⠊⡮⠠⡨⡪⠊⠔⠡⠊⣰⠃⠠⡈⠄⡈⠊⢆⠄⢨⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// ⠀⠀⠀⢀⡰⣜⢯⡳⣏⢟⢯⠿⢀⡁⢱⠘⡁⠑⠈⠢⠀⠺⡣⠀⢄⣔⡀⠐⠈⡢⢁⠔⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// ⠀⠀⡠⣞⣝⢮⢳⡭⣮⣻⡻⡓⢌⠄⢆⠑⠀⣱⣿⣶⣄⢝⣝⢬⡿⣟⣯⣤⣈⠈⡂⠚⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// ⠀⣬⢞⢵⡱⣻⡳⡹⢶⢽⣟⡑⠢⠢⡁⣜⣴⣻⣮⢿⡵⢙⠞⠌⠺⢝⣯⡷⣿⣤⠨⡀⠱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// ⡾⣝⢎⡳⣝⠵⣝⣽⡻⣷⢍⠄⡑⢠⢬⡾⣯⡿⣾⠏⡀⢨⣪⣶⡀⠀⠻⢝⣫⣮⣧⠐⠁⣅⠀⠀⠀⢀⣤⣶⢶⠀⠀⠀⠀⠀⠀
	// ⢯⣪⢯⠳⣕⣝⢮⣞⡽⣶⢅⠂⣈⢜⣯⡿⡯⢿⠷⠁⠀⣼⣷⣼⣟⠀⠀⢙⡽⣮⣛⡱⠕⢔⠄⠀⣰⡿⣿⣳⡟⠀⠀⠀⠀⠀⠀
	// ⢷⡱⣇⢟⣜⡪⣞⢮⣟⢾⡢⢁⠎⡼⣷⡶⣿⡟⡢⠐⠡⡸⣿⡻⡧⣐⠡⣪⢛⠮⢎⢍⡺⣨⢃⣰⣟⢷⣝⣽⠇⠀⠀⠀⠀⠀⠀
	// ⢷⢝⠼⡭⡮⣺⢕⡿⣺⣯⡢⢣⠨⣊⢞⢝⢳⠹⣎⡲⡱⡚⢗⡻⡩⣐⡵⣱⢵⣕⢵⠕⢜⡐⡣⣿⢞⡯⡾⠁⠀⠀⠀⠀⠀⠀⠀
	// ⢧⢣⡛⣜⠮⣺⣝⡽⡷⣕⡻⡐⢕⠜⡪⡫⡳⣧⣾⡽⣷⡝⣮⣪⣞⣾⣟⣟⢷⡣⣕⠱⡡⡪⢕⣯⡻⣽⠁⠀⠀⠀⠀⠀⠀⠀⠀
	// ⢧⡱⣣⢣⡻⢴⢯⣞⢗⢵⢊⢜⢔⢕⢕⢝⡜⡿⣵⢿⣿⢯⡿⣽⢞⡟⣾⣱⢫⡞⣔⢓⠔⡱⢊⠺⡟⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀
	// 
	// ⠵⡜⡵⡣⣝⢷⣫⡞⡕⢕⠱⣡⠗⡡⣪⡣⣟⢾⡺⡷⣫⣟⣞⢗⣟⢾⡪⡾⣕⡭⡪⡪⡪⡪⡊⡪⢊⠌⠀⠀⠀⠀⠀⠀⠀⠀⠀

	vector<wstring> image;
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠴⡢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡠⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⠠⢊⢯⣺⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ");
	image.push_back(L" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣗⢵⡱⠄⠄⢄⠀⠀⣀⣀⡠⣄⢤⡺⡡⡑⣸⡯⣳⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡳⣝⣷⢨⠊⡌⢯⢫⢗⢔⢕⠮⢲⢉⢆⠐⡘⢯⠪⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢮⢝⡷⡈⢄⠢⢎⠡⠃⣧⢕⠡⡊⡘⣆⢂⡉⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⠀⠀⠀⠀⠀⠀⢀⣀⢀⠀⢨⠊⡮⠠⡨⡪⠊⠔⠡⠊⣰⠃⠠⡈⠄⡈⠊⢆⠄⢨⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⠀⠀⢀⡰⣜⢯⡳⣏⢟⢯⠿⢀⡁⢱⠘⡁⠑⠈⠢⠀⠺⡣⠀⢄⣔⡀⠐⠈⡢⢁⠔⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⠀⡠⣞⣝⢮⢳⡭⣮⣻⡻⡓⢌⠄⢆⠑⠀⣱⣿⣶⣄⢝⣝⢬⡿⣟⣯⣤⣈⠈⡂⠚⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠀⣬⢞⢵⡱⣻⡳⡹⢶⢽⣟⡑⠢⠢⡁⣜⣴⣻⣮⢿⡵⢙⠞⠌⠺⢝⣯⡷⣿⣤⠨⡀⠱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⡾⣝⢎⡳⣝⠵⣝⣽⡻⣷⢍⠄⡑⢠⢬⡾⣯⡿⣾⠏⡀⢨⣪⣶⡀⠀⠻⢝⣫⣮⣧⠐⠁⣅⠀⠀⠀⢀⣤⣶⢶⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⢯⣪⢯⠳⣕⣝⢮⣞⡽⣶⢅⠂⣈⢜⣯⡿⡯⢿⠷⠁⠀⣼⣷⣼⣟⠀⠀⢙⡽⣮⣛⡱⠕⢔⠄⠀⣰⡿⣿⣳⡟⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⢷⡱⣇⢟⣜⡪⣞⢮⣟⢾⡢⢁⠎⡼⣷⡶⣿⡟⡢⠐⠡⡸⣿⡻⡧⣐⠡⣪⢛⠮⢎⢍⡺⣨⢃⣰⣟⢷⣝⣽⠇⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⢷⢝⠼⡭⡮⣺⢕⡿⣺⣯⡢⢣⠨⣊⢞⢝⢳⠹⣎⡲⡱⡚⢗⡻⡩⣐⡵⣱⢵⣕⢵⠕⢜⡐⡣⣿⢞⡯⡾⠁⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⢧⢣⡛⣜⠮⣺⣝⡽⡷⣕⡻⡐⢕⠜⡪⡫⡳⣧⣾⡽⣷⡝⣮⣪⣞⣾⣟⣟⢷⡣⣕⠱⡡⡪⢕⣯⡻⣽⠁⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⢧⡱⣣⢣⡻⢴⢯⣞⢗⢵⢊⢜⢔⢕⢕⢝⡜⡿⣵⢿⣿⢯⡿⣽⢞⡟⣾⣱⢫⡞⣔⢓⠔⡱⢊⠺⡟⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L" ⠵⡜⡵⡣⣝⢷⣫⡞⡕⢕⠱⣡⠗⡡⣪⡣⣟⢾⡺⡷⣫⣟⣞⢗⣟⢾⡪⡾⣕⡭⡪⡪⡪⡪⡊⡪⢊⠌⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	// 	image.push_back(L"⣽⢯⡿⡽⡯⣟⢷⢟⡯⡿⣽⢾⣻⣽⢯⡷⣟⣯⡿⣽⢾⠻⣽⣯⢷⣟⣯⡿⣽⢾⣻⣽⠯⡷⣟⣯⡿⣽⢾⠻⣽⣯⢷⣟⢯⢿⣽⢾⣻⣽");
	// 	image.push_back(L"⢾⣻⣽⣤⣴⣤⣴⣤⣴⠀⣿⣻⣽⣮⢤⣌⡤⡄⢘⠯⠿⠀⣿⣺⣿⠀⣤⢤⣤⣡⢼⣯⠀⣿⢯⣷⠛⠙⠋⠀⠛⠚⢹⢧⢘⣯⣟⣯⡿⣽");
	// 	image.push_back(L"⣿⡽⣷⣻⣞⡇⢸⡾⣾⠀⣯⣷⣟⣾⣻⢷⠻⢀⣿⣺⣞⠀⣿⣺⣽⠀⣿⡽⣾⢯⡿⣾⠀⣋⣛⣽⣟⠋⣩⣡⣉⠛⣿⡳⠈⠗⢟⣷⣟⣯");
	// 	image.push_back(L"⣷⢍⡉⣈⡉⣁⢈⡉⣉⢉⣉⣸⣷⠻⠙⣁⣶⣻⣧⣤⣤⠀⣯⡿⣾⣁⣠⣉⣈⣨⡬⣿⠀⣿⢽⡾⣧⠘⠯⠷⠻⢀⣷⢯⢘⡿⣯⡷⣯⡷");
	// 	image.push_back(L"⣻⣽⢯⠟⢉⣉⣉⡉⡋⢿⢾⡾⣽⣗⣯⢉⢊⢑⢉⢊⢉⠉⣷⣟⣯⢿⡽⠙⣉⣉⣉⠙⠲⣿⢽⣯⢿⣽⠒⠒⠚⠙⠚⠓⢺⢽⡷⣟⣯⡿");
	// 	image.push_back(L"⢿⢾⣏⠐⡿⣽⢯⣿⠳⢀⣿⢯⣷⢿⣞⡿⣯⣟⣯⣿⣻⠀⡿⣞⣯⣿⠀⠾⣯⣯⣟⡿⠀⣽⣟⣾⣟⣷⠀⣿⣟⣟⣯⣗⢘⣯⡿⣯⡷⣿");
	// 	image.push_back(L"⣻⡯⣿⣲⣤⡤⣅⣤⣴⣟⣾⣻⣽⢯⣷⣟⣿⣺⣟⣾⣽⣠⣟⣯⡷⣟⣷⢦⡤⣤⣠⣴⣺⢷⣻⣞⣷⣻⣄⣤⢤⡤⣤⢤⣸⣳⣟⣯⡿⣽");
	// 	image.push_back(L"⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯");

	images.push_back(image);

	image = vector<wstring>();


	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣞⢿⣿⣿⣿⣿⣿⣟⣾⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡽⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡽⣿⣟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣞⡭⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡯⢯⠻⣜⢮⢛⠮⡫⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡞⣿⣿⣿⣿⣿⣿⣿⢟⠎⢎⣶⢿⡔⡕⣞⣷⣕⠕⣝⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡼⣿⣿⣿⣿⣿⠏⡊⡐⡽⡮⢉⢯⢪⢇⠹⣺⢽⡄⠕⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣗⢿⣿⣿⣿⡷⡁⠢⢱⠸⡹⢮⢣⢣⠳⡹⡝⢵⢯⡂⡒⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡕⣿⡿⢝⠨⢀⠣⠑⢕⢌⢠⡣⣳⢱⡈⣄⠗⣔⡧⠠⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣨⡶⡁⢂⠅⡣⢅⠑⣓⢝⠎⢗⡹⡈⢠⢷⢯⠂⢂⢻⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣷⣟⢿⢿⣿⡯⡀⢂⢂⠪⡪⡣⣀⠡⢙⠩⢀⢀⢮⡯⣟⢌⠠⢩⠿⣫⣾⣿⡽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣮⣚⢇⢂⠌⡂⢅⢇⢏⢮⡪⡜⣜⢔⡗⡯⡞⣗⠔⡐⠅⣿⣿⣿⣿⣿⣝⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⢣⣿⣿⣿⣿⣿⣿⣿⡦⠁⠌⡢⢐⢜⢜⢕⠵⡹⡪⡣⣏⢗⢽⣱⠐⢀⢐⣽⣿⣿⣿⣿⣿⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⢣⣿⣿⣿⣿⣿⣿⣿⡦⠁⠌⡢⢐⢜⢜⢕⠵⡹⡪⡣⣏⢗⢽⣱⠐⢀⢐⣽⣿⣿⣿⣿⣿⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⢏⣾⣿⣿⣿⡿⡿⡿⣿⣯⠠⠀⡂⢂⢊⢎⢪⡓⡕⣏⢝⡜⡕⣕⢗⠈⠄⡂⡿⡛⣏⣏⣿⣿⣿⡸⣽⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⡿⢱⣿⣿⣿⣿⣟⢾⣮⡪⡊⡢⠡⠐⠠⢑⠌⡎⡎⡮⡪⡺⡸⡱⡸⡐⠠⢑⢈⣢⣿⣿⢇⢿⣿⣿⣿⡨⢿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⠁⣿⣿⣿⣿⣿⣷⡹⣿⣿⣷⡆⢁⢁⢁⠢⠡⠱⡱⡱⡱⡩⡪⡂⡇⡂⢅⠂⢼⣿⣿⣿⡸⣿⣿⣿⣿⣧⢊⢿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣗⣮⣿⣿⣿⣿⣿⣿⡌⣿⣿⣿⣷⡐⢘⠆⠅⠌⢌⠢⡑⢌⠒⠌⠢⢂⢊⢇⢊⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣷⢻⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣗⣿⣿⣿⣿⣿⣿⣿⣇⢿⣿⣿⣿⣮⠠⢹⢸⣎⠠⠑⡈⡂⠅⠅⣑⣦⠱⡁⣮⣿⣿⣿⡗⣽⣿⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣎⣿⣿⣿⣿⣿⣿⣿⣷⢹⣿⣿⣿⣿⣮⣼⡼⣿⣶⡀⠂⠂⠌⣰⣾⡟⣼⣴⣿⣿⣿⣿⡱⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⣿⣿⣿⣿⣿⣿⣷⢽⣿⣿⣷⣵⣷⣿⣿⢱⣿⣿⣿⣿⣿⣿⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⡿⡿⡛⡬⣿⡿⣿⢿⡿⣿⣟⠎⣿⢿⢿⢿⡿⣿⠏⣾⢿⡿⣿⢿⡿⣿⢌⡻⠿⡿⠿⣻⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣾⣾⣾⣯⣷⣿⣯⣟⣝⡱⣍⢆⣯⣿⣻⣯⣿⣽⢧⢨⡹⣩⣫⣿⣯⣟⣯⣷⣿⣽⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿");
	image.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");

	images.push_back(image);
}

MainLevel::~MainLevel()
{
	if (player)
	{
		map.erase(map.begin() + 1);
		delete player;
		player = nullptr;
	}

	delete timer;
	delete mapEventTimer;
	timer = nullptr;
	mapEventTimer = nullptr;

	//for(auto )

	for (auto& obj : map)
	{
		if (obj && obj->GetImage() != nullptr)
		{
			delete obj;
			obj = nullptr;
		}
	}
	map.clear();
}

void MainLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);


	if (this->bIsMainLevel == true)
	{
		dayCount += deltaTime;

		if (dayCount >= 24)
		{
			day++;
			dayCount = 0;
		}
	}

	if (!(mode == ModeType::MODE_Inventory))
	{
		timer->Update(deltaTime);
		mapEventTimer->Update(deltaTime);
	}

	if (mapEventTimer->IsTimeOut())
	{
		RandomTreeGrow();

		if (bToggle)
		{
			RandomAnimalAppear();

		}
		bToggle = !bToggle;
		mapEventTimer->Reset();
	}

	if (bPopUpImage)
	{
		imageClearTime -= deltaTime;
	}

	if (imageClearTime <= 0)
	{
		imageClearTime = 1.5f;
		bPopUpImage = false;
		Engine::Get().ClearImage(51, (int)images.size() + 100);
		SetConsoleOutputCP(949);
	}

	if (Engine::Get().GetKeyDown(VK_LSHIFT))
	{
		Game::Get().CraftMode();
	}
	if (Engine::Get().GetKeyDown(VK_TAB))
	{
		if (mode == ModeType::MODE_Play)
		{
			player->bGetControl = false;
			mode = ModeType::MODE_Inventory;
		}
		else
		{
			player->bGetControl = true;
			currentIndex = 0;
			mode = ModeType::MODE_Play;
		}
	}
	if (mode == ModeType::MODE_Inventory)
	{
		if (player->inventory.size() <= 0) return;

		if (Engine::Get().GetKeyDown(VK_UP))
		{
			currentIndex = (currentIndex - 1 + (int)player->inventory.size()) % (int)player->inventory.size();
		}
		if (Engine::Get().GetKeyDown(VK_DOWN))
		{
			currentIndex = (currentIndex + 1) % (int)player->inventory.size();
		}
		if (Engine::Get().GetKeyDown(VK_RETURN))
		{
			auto& item = player->inventory[currentIndex]->item;
			if (item->GetItemType() == ItemType::Meat || item->GetItemType() == ItemType::Medicine)
			{
				item->Use();
			}
			else
			{
				Engine::Get().SetCursorPosition(Vector2(8, 0));
				SetColor(Color::White);
				Log("현재 맵에서 사용할 수 없습니다.");
			}
		}

	}
}

void MainLevel::Draw()
{
	int width = Engine::Get().ScreenSize().x;
	int cnt = 0;

	if (player->GetHP() <= 0)
	{
		Game::Get().GameOver();
		return;
	}

	if (day >= 10)
	{
		Game::Get().AliveSuccess();
		return;
	}

	if (!bPopUpImage)
	{
		// 인벤토리 품목에 변화가 있다면 화면 한 번 갱신
		if (player->bInventoryChanged)
		{
			system("cls");
			player->bInventoryChanged = false;
		}

		SetConsoleOutputCP(949);
		// 생존 일수 표시
		SetColor(Color::White);
		Engine::Get().SetCursorPosition(0, 0);
		cout << "Day " << day + 1 << "\n";
		cout << "Time " << (float)dayCount;

		// 맵 그리기
		for (auto actor : map)
		{
			//플레이어 위치 확인
			if (actor->Position() == player->Position()) continue;

			if (actor->As<Animal>())
				SetConsoleOutputCP(CP_UTF8);
			actor->Draw();
			SetConsoleOutputCP(949);

			cnt++;
			if (cnt >= width)
			{
				cout << endl;
			}
		}

		player->Draw();

		if (timer->IsTimeOut())
		{
			Engine::Get().ClearInfoUI();
			timer->bActive = false;
			timer->Reset();
		}

		// GUI 그리기
		Engine::Get().SetCursorPosition(Vector2(0, 19));

		SetColor(Color::White);
		Log("_______________________________________");
		cout << "\t        <상태창>" << "\n";
		cout << "체 력 : ";
		for (int i = 0; i < player->GetHP(); i++)
		{
			cout << " ♥ ";
		}
		for (int i = 0; i < MAX_HP - player->GetHP(); i++)
		{
			cout << " ♡ ";
		}
		cout << "\n";

		cout << "포만감: ";

		for (int i = 0; i < player->GetStarve(); i++)
		{
			cout << " ★ ";
		}
		for (int i = 0; i < MAX_STARVE - player->GetStarve(); i++)
		{
			cout << " ☆ ";
		}
		cout << "\n";
		cout << "\t       <인벤토리>" << "\n";

		for (int i = 0; i < player->inventory.size(); i++)
		{
			SlotStruct* slot = player->inventory[i];
			SetColor(i == currentIndex ? selectedColor : unselectedColor);
			cout << slot << "\n";
		}
	}
}

Animal* MainLevel::IsAnimal(const Vector2& pos)
{
	for (auto* actor : map)
	{
		if (actor->Position() == pos)
		{
			if (auto* animal = actor->As<Animal>())
			{
				return animal;
			}
			break;
		}
	}
	return nullptr;
}

void MainLevel::RandomAnimalAppear()
{
	// 1~3번 랜덤으로 생성
	int animalCount = Random(1, 3);

	if (maxAnimalCount <= animalCnt + animalCount) return;


	// 화면 너비,높이
	int width = Engine::Get().ScreenSize().x;
	int height = Engine::Get().ScreenSize().y;

	// treeCount번
	while (animalCount > 0) {
		// 화면 안에 랜덤 좌표 생성
		int x = Random(0, width) % width;
		int y = Random(0, height) % height;


		// 생성하려는 위치에 동물이 이미 있다면 다음으로 넘어감
		if (IsAnimal(Vector2(x, y)) != nullptr) continue;

		// 생성하려는 위치에 나무가 있다면 다음으로 넘어감
		if (IsTree(Vector2(x, y)) != nullptr) continue;

		// 해당 좌표에 동물이 있지 않고 플레이어도 해당 위치에 있지 않다면
		if (player->Position() != Vector2(x, y))
		{
			// 땅을 지우고
			for (int i = 0; i < map.size(); i++)
			{
				if (map[i]->Position() == Vector2(x, y))
				{
					if (map[i]->As<Ground>())
						map.erase(map.begin() + i);
					break;
				}
			}

			// 동물 생성
			auto* animal = new Animal(Vector2(x, y));

			map.push_back(animal);
			animals.push_back(animal);
			actors.push_back(animal);

			// 횟수 감소
			animalCount--;

			// 맵의 동물 개수 증가
			animalCnt++;
		}
	}
}



void MainLevel::RandomTreeGrow()
{

	// 1~3번 랜덤으로 생성
	int treeCount = Random(1, 3);

	if (maxTreeCount <= treeCnt + treeCount) return;

	// 화면 너비,높이
	int width = Engine::Get().ScreenSize().x;
	int height = Engine::Get().ScreenSize().y;

	// treeCount번
	while (treeCount > 0) {
		// 화면 안에 랜덤 좌표 생성
		int x = Random(0, width) % width;
		int y = Random(0, height) % height;

		// 생성하려는 위치에 동물이 이미 있다면 다음으로 넘어감
		if (IsAnimal(Vector2(x, y)) != nullptr) continue;

		// 생성하려는 위치에 나무가 있다면 다음으로 넘어감
		if (IsTree(Vector2(x, y)) != nullptr) continue;

		// 해당 좌표에 나무가 있지 않고 플레이어도 해당 위치에 있지 않다면
		if (player->Position() != Vector2(x, y))
		{
			// 땅을 지우고
			for (int i = 0; i < map.size(); i++)
			{
				if (map[i]->Position() == Vector2(x, y))
				{
					if (map[i]->As<Ground>())
						map.erase(map.begin() + i);
					break;
				}
			}

			// 나무 생성
			auto* tree = new Tree(Vector2(x, y));

			map.push_back(tree);
			trees.push_back(tree);
			actors.push_back(tree);

			// 횟수 감소
			treeCount--;

			// 맵의 나무 개수 추가
			treeCnt++;
		}
	}
}

void MainLevel::SetMap(vector<vector<char>> map)
{

}

bool MainLevel::IsGround(const Vector2& pos)
{
	for (auto* actor : map)
	{
		if (actor->Position() == pos)
		{
			if (actor->As<Ground>()) return true;
			break;
		}
	}
	return false;
}

Tree* MainLevel::IsTree(const Vector2& pos)
{
	for (auto* actor : map)
	{
		if (actor->Position() == pos)
		{
			if (auto tree = actor->As<Tree>())
			{
				return tree;
			}
			break;
		}
	}
	return nullptr;
}

void MainLevel::ChoppingTree(const Vector2& pos)
{
	timer->bActive = true;

	for (int i = 0; i < trees.size(); i++)
	{
		if (trees[i]->Position() == pos)
		{
			trees.erase(trees.begin() + i);
			break;
		}
	}

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i]->Position() == pos)
		{
			if (map[i]->As<Tree>())
			{
				map.erase(map.begin() + i);
				break;
			}
		}
	}
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->Position() == pos)
		{
			if (actors[i]->As<Tree>())
			{
				actors.erase(actors.begin() + i);
				break;
			}
		}
	}
	treeCnt--;

	auto* ground = new Ground(pos);
	actors.push_back(ground);
	map.push_back(ground);
}

void MainLevel::HuntAnimal(const Vector2& pos)
{
	for (int i = 0; i < animals.size(); i++)
	{
		if (animals[i]->Position() == pos)
		{
			animals.erase(animals.begin() + i);
			break;
		}
	}

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i]->Position() == pos)
		{
			if (map[i]->As<Animal>())
			{
				map.erase(map.begin() + i);
				break;
			}
		}
	}
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->Position() == pos)
		{
			if (actors[i]->As<Animal>())
			{
				actors.erase(actors.begin() + i);
				break;
			}
		}
	}
	animalCnt--;
	auto* ground = new Ground(pos);
	actors.push_back(ground);
	map.push_back(ground);
}

void MainLevel::PrintImage(int printCode)
{
	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	SetColor(Color::White);

	for (auto& line : images[printCode])
	{
		wcout << line << "\n";
	}
	SetConsoleOutputCP(949);
	SetColor(Color::Red);
	if (1 == printCode)
	{
		cout << "벌레에게 물렸다. (HP -1)\n";
	}
	else
	{
		cout << "숨어있던 동물에게 습격당했다. (HP -1)\n";
	}
}
