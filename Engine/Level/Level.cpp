#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}
void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ�� �����̰ų� ���� ��û�� ��� �ǳʶٱ�.
		if (actor->isActive && !actor->isExpired)
		{
			actor->Update(deltaTime);
		}
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��
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

// actor �߰��� ������ �ڷ� �̷�� �Լ�
void Level::ProcessAddedAndDestroyActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��.	
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

	// �߰� ��û�� ���� ó��
	if (addRequestedActor != nullptr)
	{
		actors.push_back(addRequestedActor);
		addRequestedActor = nullptr;
	}
}
