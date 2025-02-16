#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor(), image(image)
{
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 색상 설정.
	SetColor(color);

	// 그리기.
	// 1단계 : 콘솔 좌표 옮기기
	Engine::Get().SetCursorPosition(position+ Vector2(4, 2));

	// 2단계 : 그리기 (콘솔 출력)
	std::cout << image;

	// 색상 복구
	SetColor(Color::White);

}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	// 이전의 위치를 먼저 지우기.
	Engine::Get().SetCursorPosition(position);
	Log(" ");

	// 위치를 새로 옮기기.
	Super::SetPosition(newPosition);
}