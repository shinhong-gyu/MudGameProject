#include "Tree.h"
#include "Engine/Engine.h"
#include "Player.h"
#include "Level/MainLevel.h"
#include "Item/Wood.h"


Tree::Tree(const Vector2& position)
	:DrawableActor("#")
{
	// 위치 설정.
	this->position = position;

	// 색상 지정.
	color = Color::Green;

	void (*EventFunction)() = AttackByAnimal;

	events.PushBack(new FEventStruct{ "AttackByAnimal",[]() {	Tree::AttackByAnimal(); },5 });
	events.PushBack(new FEventStruct{ "GetWood",[]() {	Tree::GetWood(); },90 });
	events.PushBack(new FEventStruct{ "BitByInsect",[]() {	Tree::BitByInsect(); },5 });
}

void Tree::TriggerTreeEvent()
{
	// 이벤트 선택을 위한 가중치 계산
	int totalWeight = 0;
	for (const auto& event : events) {
		totalWeight += event->probability;
	}

	// 랜덤 값 생성 (0 ~ totalWeight-1)
	int randomValue = rand() % totalWeight;

	// 랜덤 값에 따라 이벤트 실행
	int cumulativeWeight = 0;
	for (const auto& event : events) {
		cumulativeWeight += event->probability;
		if (randomValue < cumulativeWeight) {
			event->eventFunc();

			// 땅으로 바꾸기
			SetColor(Color::Brown);
			image = ".";

			return;
		}
	}
}

// 동물에게 공격당함
void Tree::AttackByAnimal()
{
	Engine::Get().ClearInfoUI();

	Engine::Get().SetCursorPosition(Vector2(12, 0));

	Log("동물에게 공격받았다.");

	if (auto* curLevel = dynamic_cast<MainLevel*>(Engine::Get().GetLevel()))
	{
		curLevel->bPopUpImage = true;
		Engine::Get().ClearImage(Engine::Get().ScreenSize().x + 10, Engine::Get().ScreenSize().y + 10);
		curLevel->PrintImage(0);
		curLevel->player->SetHP(curLevel->player->GetHP() - 1);
	}
}

// 목재를 얻음
void Tree::GetWood()
{
	Engine::Get().ClearInfoUI();

	Engine::Get().SetCursorPosition(Vector2(14, 0));

	Log("목재를 얻었다.");

	auto* map = dynamic_cast<MainLevel*>(Engine::Get().GetLevel());
	if (map)
	{
		map->player->AddToInventory(new Wood("목재"), 1);
	}
}

// 곤충에게 물림
void Tree::BitByInsect()
{
	Engine::Get().ClearInfoUI();

	Engine::Get().SetCursorPosition(Vector2(14, 0));

	Log("벌레에게 물렸다.");

	if (auto* curLevel = dynamic_cast<MainLevel*>(Engine::Get().GetLevel()))
	{
		curLevel->bPopUpImage = true;
		Engine::Get().ClearImage(Engine::Get().ScreenSize().x + 10, Engine::Get().ScreenSize().y + 10);
		curLevel->PrintImage(1);
		curLevel->player->SetHP(curLevel->player->GetHP() - 1);
	}
}

// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢴⣺⣯⣿⣽⣿⣽⢮⡦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠔⡴⣟⣞⣯⣷⡿⣾⣻⣾⡿⡿⣻⣽⣖⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣦⣆⠙⢽⣟⣷⡿⣿⡝⠁⠁⠀⠘⡷⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠂⡁⠺⡟⡟⢈⠠⢚⣿⣻⡳⣣⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠠⠡⡈⡂⡊⢌⠠⠀⡿⣟⣷⢝⢜⡌⡂⡡⡐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⡅⢕⠰⡰⣸⡰⡨⡀⡺⣿⣯⡳⡱⡱⡱⣼⢷⣢⠂⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⢱⡇⢎⢑⠛⢜⢔⣽⣟⣞⢮⢺⡸⣽⡿⣟⣯⡧⡂⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣼⣵⡑⣄⡪⣰⣯⡷⣗⣗⡝⡮⣺⣟⣿⡿⣿⣽⡪⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣾⢷⣻⢞⡽⣪⡺⣜⢽⢵⡿⣟⣿⣟⣷⣳⡑⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣷⢿⡿⠈⠈⠊⠑⠑⠧⡳⣻⢿⣿⣿⢿⣻⡵⣝⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣈⣿⣾⣿⠂⠀⠀⠀⠀⠀⠀⠀⠉⠛⠙⠚⠻⣯⣿⣟⣯⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣽⢷⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠋⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀