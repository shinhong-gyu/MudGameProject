#pragma once

#include "Core.h"

// 타이머 클래스
class ENGINE_API Timer
{

public:
	Timer(float targetTime);

	void Update(float deltaTime);

	void Reset();

	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }

	inline void SetTimer(float targetTime) { this->targetTime = targetTime; }
	
	bool bActive = false;

private:
	float elapsedTime = 0.0f;
	float targetTime = 0.0f;
};

