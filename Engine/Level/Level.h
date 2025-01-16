#pragma once

#include "Core.h"

#include "Container/List.h"

#include "RTTI.h"

using namespace std;

class Actor;

class ENGINE_API Level :public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();
	// 레벨의 루프 처리 함수.
	virtual void Update(float deltaTime);

	virtual void Draw();

	// 액터 추가 함수
	void AddActor(Actor* newActor);

	// 삭제 요청이 된 액터를 정리하는 함수.
	//void DestroyActor();
	void ProcessAddedAndDestroyActor();

protected:

	// 게임 공간에 배치되는 물체(액터) 배열
	List<Actor*> actors;

	// 추가 요청된 액터
	Actor* addRequestedActor = nullptr;
};

