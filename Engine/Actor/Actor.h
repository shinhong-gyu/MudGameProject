#pragma once

#include "Engine/Engine.h"
#include "Math/Vector2.h"

#include "RTTI.h"
#include "Core.h"

// 레벨의 기본 물체
class ENGINE_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)
	
	// Level 클래스를 friend로 선언.
	// private 에 접근이 가능하도록 -> Get/Set 설정하는 것이 객체지향적
	friend class Level;
public:
	Actor();
	virtual ~Actor();

	// 루프 처리 함수.
	virtual void Update(float deltaTime);

	virtual void Draw();

	// Getter/Setter
	virtual void SetPosition(const Vector2& newPosition);

	inline Vector2 Position() const;

	inline bool IsActive() const { return isActive; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	Vector2 position;

	// ID(해시)/이름 값.
	// 활성화 상태인지를 나타ㅐ는 변수.
	bool isActive;

	// 액터의 제거 요청이 됐는지 여부를 나타내는 변수.
	bool isExpired;
};

