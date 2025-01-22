#include "Medicine.h"
#include "../Player.h"

Medicine::Medicine(const char* name, Player* owner)
	: Item(name, owner)
{
	itemType = ItemType::Medicine;
}

void Medicine::Use()
{
	Engine::Get().SetCursorPosition(Vector2(14, 0));
	
	SetColor(Color::White);

	Log("치료제를 먹었다 (체력+1).");
	
	owner->SetHP(owner->GetHP() + 1);
	owner->RemoveFromInventory("치료제", 1);
}
