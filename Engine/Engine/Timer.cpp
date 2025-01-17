#include "PreCompiledHeader.h"
#include "Timer.h"

Timer::Timer(float targetTime)
	:targetTime(targetTime)
{
}

void Timer::Update(float deltaTime)
{
	if (bActive)	elapsedTime += deltaTime;
}

void Timer::Reset()
{
	elapsedTime = 0.0f;
}
