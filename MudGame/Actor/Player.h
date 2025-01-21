#pragma once

#include "Actor/DrawableActor.h"
#include "Container/List.h"
#include "../Level/MainLevel.h"
#include "Item/Item.h"

class Timer;

struct SlotStruct
{
	Item* item = nullptr;
	int quantity = 0;

	friend std::ostream& operator<<(std::ostream& os, const SlotStruct& s)
	{
		return os << (s.item ? s.item->GetName() : "NULL") << "\t" << s.quantity;
	}
};

class Player :public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)
		friend class MainLevel;
public:
	Player(const char* image = "p");

	Player(const Vector2& position, const char* image = "P");

	virtual void Update(float deltaTime) override;

	void AddToInventory(Item* item, int quantity);
	void RemoveFromInventory(const char* name, int quantity);

	bool SearchItemByType(ItemType type);

	vector<Item*> GetItemListByType(ItemType type);

	int GetQuantity(const char* name);

	int GetHP() const { return hp; }
	void SetHP(int value) { hp = value; }
	int GetStarve() const { return starve; }
	void SetStarve(int value) { starve = value; }

private:
	vector<SlotStruct> inventory;

	int hp = 8;
	int	starve = 8;

	Timer* starveTimer = new Timer(10.0f);

	bool bGetControl = true;
};