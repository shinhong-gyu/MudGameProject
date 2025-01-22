#include "Meat.h"
#include "Actor/Player.h"

Meat::Meat(const char* name,Player* owner)
	:Item(name,owner)
{
	itemType = ItemType::Meat;
}

void Meat::Use()
{

	Engine::Get().SetCursorPosition(Vector2(14, 0));

	SetColor(Color::White);

	Log("고기를 먹었다 (포만감 +1).");

	owner->SetStarve(owner->GetStarve() + 1);
	owner->RemoveFromInventory("고 기", 1);
}
