#pragma once
#include "Core.h"
#include "Math/Vector2.h"

class Level;
class Actor;

// 입력 처리를 위한 구조체.
struct KeyState
{
	// 이전 프레임에 키가 눌렸는지 확인
	bool wasKeyDown = false;

	// 현재 프레임에 키가 눌렸는지 확인
	bool isKeyDown = false;
};

enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor,
};

// 게임 엔진 클래스
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가 함수
	void LoadLevel(Level* newLevel);

	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// 화면 좌표 관련 함수
	void SetCursorPosition(const Vector2& poisition);
	void SetCursorPosition(int x, int y);

	void SetTargetFrameRate(float targetFrameRate);

	// 입력 관련 함수.
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// 종료 함수.
	void QuitGame();

	// 싱글톤 객체 접근 함수
	static Engine& Get();

	void SetCursorType(CursorType cursorType);


protected:
	void ProcessInput();
	void Update(float deltaTime); // Tick()
	void Clear(); // 화면 지우기.
	void Draw(); // Render();

	// 이전 프레임의 키 상태를 저장하는 함수.
	void SavePreviousKeyStates();

protected:

	// 타겟 프레임 변수
	float targetFrameRate = 60.0f;

	// 한 프레임 시간 값 (단위 : 초).
	float targetOneFrameTime = 0.0f;

	// 종료할 때 설정할 변수.
	bool quit;

	// 키보드 입력 상태를 저장z할 배열.
	KeyState keyStates[255];

	// 싱글톤 구현을 위한 전역 변수 선언
	static Engine* instance;

	// 프레임을 업데이트 해야하는지 여부를 나타는낸 변수.
	bool bShouldUpdate = true;

	// 메인 레벨 변수.
	Level* mainLevel;
};