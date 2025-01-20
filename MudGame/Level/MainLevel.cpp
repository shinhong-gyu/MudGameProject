#include "MainLevel.h"
#include "Actor/Tree.h"
#include "Actor/Ground.h"
#include "Actor/Player.h"
#include "Engine/Timer.h"
#include "Actor/Animal.h"

#include <sstream>
#include <string>

MainLevel::MainLevel()
{
	timer = new Timer(2.0f);
	mapEventTimer = new Timer(7.0f);
}

MainLevel::MainLevel(vector<vector<char>> p_Map)
{
	Engine::Get().SetCursorType(CursorType::NoCursor);

	timer = new Timer(2.0f);
	mapEventTimer = new Timer(7.0f);
	mapEventTimer->bActive = true;

	int x = 0, y = 0;
	for (auto line : p_Map)
	{
		for (auto c : line)
		{
			if (c == '.')
			{
				auto* ground = new Ground(Vector2(x, y));
				map.PushBack(ground);
				actors.PushBack(ground);
			}
			else if (c == '#')
			{
				auto* tree = new Tree(Vector2(x, y));
				map.PushBack(tree);
				trees.PushBack(tree);
				actors.PushBack(tree);

				treeCnt++;
			}
			else if (c == 'P')
			{
				auto* ground = new Ground(Vector2(x, y));
				actors.PushBack(ground);
				map.PushBack(ground);

				player = new Player(Vector2(x, y));
				map.PushBack(player);
				actors.PushBack(player);
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
	image.push_back(L"⣽⢯⡿⡽⡯⣟⢷⢟⡯⡿⣽⢾⣻⣽⢯⡷⣟⣯⡿⣽⢾⠻⣽⣯⢷⣟⣯⡿⣽⢾⣻⣽⠯⡷⣟⣯⡿⣽⢾⠻⣽⣯⢷⣟⢯⢿⣽⢾⣻⣽");
	image.push_back(L"⢾⣻⣽⣤⣴⣤⣴⣤⣴⠀⣿⣻⣽⣮⢤⣌⡤⡄⢘⠯⠿⠀⣿⣺⣿⠀⣤⢤⣤⣡⢼⣯⠀⣿⢯⣷⠛⠙⠋⠀⠛⠚⢹⢧⢘⣯⣟⣯⡿⣽");
	image.push_back(L"⣿⡽⣷⣻⣞⡇⢸⡾⣾⠀⣯⣷⣟⣾⣻⢷⠻⢀⣿⣺⣞⠀⣿⣺⣽⠀⣿⡽⣾⢯⡿⣾⠀⣋⣛⣽⣟⠋⣩⣡⣉⠛⣿⡳⠈⠗⢟⣷⣟⣯");
	image.push_back(L"⣷⢍⡉⣈⡉⣁⢈⡉⣉⢉⣉⣸⣷⠻⠙⣁⣶⣻⣧⣤⣤⠀⣯⡿⣾⣁⣠⣉⣈⣨⡬⣿⠀⣿⢽⡾⣧⠘⠯⠷⠻⢀⣷⢯⢘⡿⣯⡷⣯⡷");
	image.push_back(L"⣻⣽⢯⠟⢉⣉⣉⡉⡋⢿⢾⡾⣽⣗⣯⢉⢊⢑⢉⢊⢉⠉⣷⣟⣯⢿⡽⠙⣉⣉⣉⠙⠲⣿⢽⣯⢿⣽⠒⠒⠚⠙⠚⠓⢺⢽⡷⣟⣯⡿");
	image.push_back(L"⢿⢾⣏⠐⡿⣽⢯⣿⠳⢀⣿⢯⣷⢿⣞⡿⣯⣟⣯⣿⣻⠀⡿⣞⣯⣿⠀⠾⣯⣯⣟⡿⠀⣽⣟⣾⣟⣷⠀⣿⣟⣟⣯⣗⢘⣯⡿⣯⡷⣿");
	image.push_back(L"⣻⡯⣿⣲⣤⡤⣅⣤⣴⣟⣾⣻⣽⢯⣷⣟⣿⣺⣟⣾⣽⣠⣟⣯⡷⣟⣷⢦⡤⣤⣠⣴⣺⢷⣻⣞⣷⣻⣄⣤⢤⡤⣤⢤⣸⣳⣟⣯⡿⣽");
	image.push_back(L"⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯⢿⡯⣿⢯⡿⣯");

	images.push_back(image);
}

MainLevel::~MainLevel()
{
}

void MainLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	timer->Update(deltaTime);

	mapEventTimer->Update(deltaTime);

	//player->Update(deltaTime);

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
		imageClearTime = 3.0f;
		bPopUpImage = false;
		Engine::Get().ClearImage(51, (int)images.size() + 100);
		SetConsoleOutputCP(949);
	}
}

void MainLevel::Draw()
{
	int width = Engine::Get().ScreenSize().x;
	int cnt = 0;

	if (!bPopUpImage)
	{
		for (auto actor : map)
		{
			//플레이어 위치 확인.

			if (actor->Position() == player->Position()) continue;

			actor->Draw();
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

		SetColor(Color::Green);
		Log("_______________________________________");
		cout << "\t\t상태창" << "\n";
		cout << "체 력 : ";
		for (int i = 0; i < player->GetHP(); i++)
		{
			cout << " ♥ ";
		}
		for (int i = 0; i < 10 - player->GetHP(); i++)
		{
			cout << " ♡ ";
		}
		cout << "\n";

		cout << "배고픔: ";

		for (int i = 0; i < player->GetStarve(); i++)
		{
			cout << " ★ ";
		}
		for (int i = 0; i < 10 - player->GetStarve(); i++)
		{
			cout << " ☆ ";
		}
		cout << "\n";
		cout << "\t\t인벤토리" << "\n";

		for (SlotStruct slot : player->inventory)
		{
			cout << slot << "\n";
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

		// 해당 좌표에 이미 나무가 있는지 확인하기 위한 bool 변수
		bool bAlreadyTree = false;
		for (int i = 0; i < trees.Size(); i++)
		{
			// 만약 trees 배열 안에 생성한 좌표와 같은 좌표를 같는 요소가 있다면
			if (trees[i]->Position() == Vector2(x, y))
			{
				// check
				bAlreadyTree = true;

				// 반복문 종료
				break;
			}
		}

		// 해당 좌표에 나무가 있지 않고 플레이어도 해당 위치에 있지 않다면
		if (bAlreadyTree == false && player->Position() != Vector2(x, y))
		{
			// 땅을 지우고
			for (int i = 0; i < map.Size(); i++)
			{
				if (map[i]->Position() == Vector2(x, y))
				{
					if (map[i]->As<Ground>())
						map.Erase(i);
					break;
				}
			}

			// 나무 생성
			auto* tree = new Tree(Vector2(x, y));

			map.PushBack(tree);
			trees.PushBack(tree);
			actors.PushBack(tree);

			// 횟수 감소
			treeCount--;

			// 맵의 나무 개수 추가
			treeCnt++;
		}
	}
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

		// 해당 좌표에 이미 동물이 있는지 확인하기 위한 bool 변수
		bool bAlreadyAnimal = false;
		for (int i = 0; i < animals.Size(); i++)
		{
			// 만약 trees 배열 안에 생성한 좌표와 같은 좌표를 같는 요소가 있다면
			if (animals[i]->Position() == Vector2(x, y))
			{
				// check
				bAlreadyAnimal = true;

				// 반복문 종료
				break;
			}
		}

		// 해당 좌표에 동물이 있지 않고 플레이어도 해당 위치에 있지 않다면
		if (bAlreadyAnimal == false && player->Position() != Vector2(x, y))
		{
			// 땅을 지우고
			for (int i = 0; i < map.Size(); i++)
			{
				if (map[i]->Position() == Vector2(x, y))
				{
					if (map[i]->As<Ground>())
						map.Erase(i);
					break;
				}
			}

			// 동물 생성
			auto* animal = new Animal(Vector2(x, y));

			map.PushBack(animal);
			animals.PushBack(animal);
			actors.PushBack(animal);

			// 횟수 감소
			animalCount--;

			// 맵의 동물 개수 증가
			animalCnt++;
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

void MainLevel::ChoppingTree(const Vector2& pos)
{
	timer->bActive = true;

	for (int i = 0; i < trees.Size(); i++)
	{
		if (trees[i]->Position() == pos)
		{
			trees.Erase(i);
			treeCnt--;
			break;
		}
	}

	for (int i = 0; i < map.Size(); i++)
	{
		if (map[i]->Position() == pos)
		{
			if (map[i]->As<Tree>())
			{
				map.Erase(i);
				break;
			}
		}
	}
	for (int i = 0; i < actors.Size(); i++)
	{
		if (actors[i]->Position() == pos)
		{
			if (actors[i]->As<Tree>())
			{
				actors.Erase(i);
				break;
			}
		}
	}

	auto* ground = new Ground(pos);
	actors.PushBack(ground);
	map.PushBack(ground);
}

void MainLevel::PrintImage(int printCode)
{
	SetConsoleOutputCP(CP_UTF8);

	SetColor(Color::White);

	for (auto& line : images[printCode])
	{
		wcout << line << "\n";
	}
}
