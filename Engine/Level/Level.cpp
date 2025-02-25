#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
}
void Level::Update(float deltaTime)
{
	// 레벨에 포함된 액터를 순회하면서 Update 함수 호출
	for (Actor* actor : actors)
	{
		// 액터가 비활성 상태이거나 삭제 요청된 경우 건너뛰기.
		if (actor->isActive && !actor->isExpired)
		{
			actor->Update(deltaTime);
		}
	}
}

void Level::Draw()
{
	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출
	for (Actor* actor : actors)
	{
		if (actor->isActive && !actor->isExpired)
		{
			actor->Draw();
		}
	}

}
void Level::AddActor(Actor* newActor)
{
	//actors.PushBack(newActor);
	addRequestedActor = newActor;
}

// actor 추가를 프레임 뒤로 미루는 함수
void Level::ProcessAddedAndDestroyActor()
{
	// 액터 순회 후 삭제 요청된 액터를 처리.	
	for (int i = 0; i < actors.size();)
	{
		if (actors[i]->isExpired == true)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.erase(actors.begin()+i);
			continue;
		}
		++i;
	}

	// 추가 요청된 액터 처리
	if (addRequestedActor != nullptr)
	{
		actors.push_back(addRequestedActor);
		addRequestedActor = nullptr;
	}
}
