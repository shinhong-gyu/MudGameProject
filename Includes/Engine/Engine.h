#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include "Timer.h"


class Level;
class Actor;

// �Է� ó���� ���� ����ü.
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool wasKeyDown = false;

	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool isKeyDown = false;
};

enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor,
};

// ���� ���� Ŭ����
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void LoadLevel(Level* newLevel);

	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// ȭ�� ��ǥ ���� �Լ�
	void SetCursorPosition(const Vector2& poisition);
	void SetCursorPosition(int x, int y);

	void SetTargetFrameRate(float targetFrameRate);

	// ȭ�� ũ�� ��ȯ �Լ�
	inline Vector2 ScreenSize() const { return screenSize; }

	// �Է� ���� �Լ�.
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// ���� �Լ�.
	void QuitGame();

	// �̱��� ��ü ���� �Լ�
	static Engine& Get();

	void SetCursorType(CursorType cursorType);

	Level* GetLevel() { return mainLevel; }

	void ClearInfoUI();
	void ClearImage(int x ,int y);
protected:
	void ProcessInput();
	void Update(float deltaTime); // Tick()
	void Clear(); // ȭ�� �����.
	void Draw(); // Render();

	// ���� �������� Ű ���¸� �����ϴ� �Լ�.
	void SavePreviousKeyStates();

protected:

	// Ÿ�� ������ ����
	float targetFrameRate = 60.0f;

	// �� ������ �ð� �� (���� : ��).
	float targetOneFrameTime = 0.0f;

	// ������ �� ������ ����.
	bool quit;

	// Ű���� �Է� ���¸� ����z�� �迭.
	KeyState keyStates[255];

	// �̱��� ������ ���� ���� ���� ����
	static Engine* instance;

	// �������� ������Ʈ �ؾ��ϴ��� ���θ� ��Ÿ�³� ����.
	bool bShouldUpdate = true;

	// ���� ���� ����.
	Level* mainLevel;

	// ȭ�� ũ��
	Vector2 screenSize;

	char* emptyStringBuffer = nullptr;
};