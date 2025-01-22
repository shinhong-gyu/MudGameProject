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

	Log("��⸦ �Ծ��� (������ +1).");

	owner->SetStarve(owner->GetStarve() + 1);
	owner->RemoveFromInventory("�� ��", 1);
}
