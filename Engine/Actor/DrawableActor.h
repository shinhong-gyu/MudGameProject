#pragma once

#include "Actor.h"
#include "RTTI.h"

class ENGINE_API DrawableActor : public Actor
{
	//RTTI
	RTTI_DECLARATIONS(DrawableActor, Actor)
public:
	DrawableActor(const char* image = " ");
	virtual ~DrawableActor() = default;

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPoistion) override;

protected:
	// 화면에 그릴 문자 값
	const char* image;

	Color color = Color::White;
};