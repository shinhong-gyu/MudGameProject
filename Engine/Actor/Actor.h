#pragma once

#include "Engine/Engine.h"
#include "Math/Vector2.h"

#include "RTTI.h"
#include "Core.h"

// ������ �⺻ ��ü
class ENGINE_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)
	
	// Level Ŭ������ friend�� ����.
	// private �� ������ �����ϵ��� -> Get/Set �����ϴ� ���� ��ü������
	friend class Level;
public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�.
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

	// ID(�ؽ�)/�̸� ��.
	// Ȱ��ȭ ���������� ��Ÿ���� ����.
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����.
	bool isExpired;
};

