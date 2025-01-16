#pragma once

#include "Actor.h"
#include "RTTI.h"

class ENGINE_API DrawableActor : public Actor
{
	//RTTI
	RTTI_DECLARATIONS(DrawableActor, Actor)
public:
	DrawableActor(char image = ' ');
	virtual ~DrawableActor() = default;

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPoistion) override;

private:
	// ȭ�鿡 �׸� ���� ��
	char image;
};