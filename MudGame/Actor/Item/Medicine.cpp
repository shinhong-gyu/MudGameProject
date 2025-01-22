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

	Log("ġ������ �Ծ��� (ü��+1).");
	
	owner->SetHP(owner->GetHP() + 1);
	owner->RemoveFromInventory("ġ����", 1);
}
