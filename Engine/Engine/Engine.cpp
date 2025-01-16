#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "Level/Level.h"
#include "Actor/Actor.h"

using namespace std;

// 전역 변수 초기화.
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(new Level())
{
	// 싱글톤 객체 설정.
	instance = this;

	// 기본 타겟 프레임 속도 설정
	SetTargetFrameRate(60.0f);
}


Engine::~Engine()
{
	// 메인 레벨 메모리 해제
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	// 시작 타임 스탬프 저장
	// timeGetTime() : 현재 시간을 ms 단위로 반환 (1//1000초) 단위라서 부정확함
	// unsigned long currentTime = timeGetTime();
	// unsigned long previousTime = 0;

	// CPU 시계 사용Up
	// 시스템 시계 -> 고해상도 카운터 (10000000)
	// 메인보드에 존재함
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 시작 시간 및 이전 시간을 위한 변수.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// 프레임 제한
	//float targetFrameRate = 60.0f;

	// 한 프레임 시간 계산.
	//float targetOneFrameTime = 1.0f / targetFrameRate;


	while (!quit)
	{
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		targetOneFrameTime = 1.0f / targetFrameRate;

		// 프레임 확인
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			// 업데이트 가능한 상태에서만 프레임 업데이트 처리
			if (bShouldUpdate)
			{
				Update(deltaTime);
				// 상용엔진에서 병목이 많이 걸림 (Data Setting -> DrawCall(CPU) -> GPU => 최적화 대상)
				Draw();
			}

			// 키 상태 저장
			SavePreviousKeyStates();

			// 현재 시간을 저장
			previousTime = currentTime;

			// 액터 정리(삭제 요청된 액터들 정리).
			if (mainLevel)
			{
				mainLevel->ProcessAddedAndDestroyActor();
			}

			// 프레임 업데이트 활성화
			bShouldUpdate = true;
		}

		//Sleep(0.1);
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 메인 레벨 설정
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// 예외 처리
	if (mainLevel != nullptr)
	{
		bShouldUpdate = false;
		mainLevel->AddActor(newActor);
	}
}

void Engine::DestroyActor(Actor* targetActor)
{
	// 예외 처리
	if (mainLevel != nullptr)
	{
		bShouldUpdate = false;
		targetActor->Destroy();
	}
}

void Engine::SetCursorPosition(const Vector2& poisition)
{
	SetCursorPosition(poisition.x, poisition.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	// 현재의 키상태 반환
	return keyStates[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	// 전에 키가 안눌렸었는데 지금 눌려있다면 
	return keyStates[key].isKeyDown && !keyStates[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	// 전에 키가 눌렸었는데 지금 안눌려있다면
	return !keyStates[key].isKeyDown && keyStates[key].wasKeyDown;;
}

void Engine::QuitGame()
{
	// 게임 종료
	quit = true;
}

Engine& Engine::Get()
{
	// 싱글톤 객체 반환
	return *instance;
}

void Engine::SetCursorType(CursorType cursorType)
{
	CONSOLE_CURSOR_INFO info = { };

	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;
	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;
	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::ProcessInput()
{
	for (int ix = 0; ix < 255; ix++)
	{
		// GetAsyncKeyState : 키보드의 상태를 가져옴
		keyStates[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) != 0;
	}
}

void Engine::Update(float deltaTime)
{
	// ESC 키로 게임 종료
// 	if (GetKeyDown(VK_ESCAPE)) 
// 		QuitGame();

	// cout << "Deltatime : " << deltaTime << ", FPS:" << (1.0f / deltaTime) << "\n";

	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Clear()
{
	// 화면의 (0,0)으로 이동.
	SetCursorPosition(0, 0);
	int height = 25;

	for (int i = 0; i < height; i++)
	{
		Log("                               ");
	}

	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// 화면 지우기
	Clear();
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int ix = 0; ix < 255; ix++)
	{
		keyStates[ix].wasKeyDown = keyStates[ix].isKeyDown;
	}
}
