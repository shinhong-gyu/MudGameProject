#include "TextScrollActor.h"
#include "Game/Game.h"

TextScrollActor::TextScrollActor(const char* message)
{
	temp = new char[printWidth + 1];
	// ���ڿ� ���� ���ϱ�
	length = (int)strlen(message);

	// ���ڿ� ����.
	string = new char[length + 1];
	strcpy_s(string, length + 1, message);

	// Ŀ�� ���߱�
	Engine::Get().SetCursorType(CursorType::NoCursor);
}

TextScrollActor::~TextScrollActor()
{
	delete[] temp;
	delete[] string;
}

void TextScrollActor::Update(float deltaTime)
{


	// ������ �ֱ�
	elapsedTime += deltaTime;

	if (elapsedTime >= delayTime)
	{

		// ȭ�鿡 �׸� ���ڿ��� ���� �ε��� ������Ʈ.
		//index = (index + 1) % length;

		if (shouldUpdata)
		{
			if (direction == Direction::Right)
			{
				index = (index - 1 + length) % length;
			}
			if (direction == Direction::Left)
			{
				index = (index + 1) % length;
			}
		}
		else
		{
			index = (index + 1) % length;
		}

		elapsedTime = 0.0f;
	}

	// ESC ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}

	if (Engine::Get().GetKey(VK_LEFT))
	{
		direction = Direction::Left;
		shouldUpdata = true;
	}
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		direction = Direction::Right;
		shouldUpdata = true;
	}
	if (!Engine::Get().GetKey(VK_LEFT) && !Engine::Get().GetKey(VK_RIGHT))
	{
		shouldUpdata = false;
	}
}

void TextScrollActor::Draw()
{
	// �ӽ� ���ڿ� ����.
	//char* temp = new char[printWidth + 1];
	int tempIndex = index;

	for (int i = 0; i < printWidth; i++)
	{
		temp[i] = string[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	temp[printWidth] = '\0';
	Log(temp);

	//delete[] temp;

	Engine::Get().SetCursorPosition(0, 0);
}
