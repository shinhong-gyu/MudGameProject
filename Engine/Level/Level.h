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
	// ������ ���� ó�� �Լ�.
	virtual void Update(float deltaTime);

	virtual void Draw();

	// ���� �߰� �Լ�
	void AddActor(Actor* newActor);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�.
	//void DestroyActor();
	void ProcessAddedAndDestroyActor();

protected:

	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭
	List<Actor*> actors;

	// �߰� ��û�� ����
	Actor* addRequestedActor = nullptr;
};

