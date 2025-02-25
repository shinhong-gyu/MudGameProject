#pragma once
#pragma once
#include "Actor/DrawableActor.h"
#include "Container/List.h"
#include <string>

/*typedef void (*EventFunction)();*/

struct FEventStruct
{
	// EventFunction 타입 정의
	using EventFunction = void(*)();

	// FEventStruct 생성자 구현
	FEventStruct(std::string name, EventFunction func, int prob)
		: eventName(name), eventFunc(func), probability(prob)
	{
	}

	std::string eventName;
	EventFunction eventFunc;
	int probability;
};

class Tree : public DrawableActor
{
	RTTI_DECLARATIONS(Tree, DrawableActor)
public:
	Tree(const Vector2& position);

	void TriggerTreeEvent();

private:
	static void AttackByAnimal();
	static void GetWood();
	static void BitByInsect();
	static void GetMedicine();
private:
	List<FEventStruct*> events;
};
