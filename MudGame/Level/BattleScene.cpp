#include "BattleScene.h"
#include "Engine/Engine.h"

BattleScene::BattleScene()
{
	vector<wstring> image;
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢔⢇⢇⢗⡕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢆⠇⡧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⡹⡸⡸⡸⡰⡩⣂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡐⣷⢙⠪⠂⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠎⢎⢎⢆⢇⢇⢕⢕⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⣎⢪⢪⠊⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⡔⡮⣳⢱⢱⢱⢱⢱⢱⢢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢱⢱⢳⠅⠪⡨⠨⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣢⡲⡝⣎⢞⣜⢮⢣⢣⢣⢣⢱⢱⢑⢕⠆⠀⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢇⢣⢱⢑⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠊⠚⠊⠓⣑⢇⢇⢇⢇⢇⢇⢇⢇⢇⢝⠄⠀⠀⠀⠀⠀⠀⠀");
	image.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸⣘⢌⣎⢮⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡺⡸⣸⡸⣜⢜⢜⢜⢜⢜⢜⢜⢜⠄⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢎⢇⢎⠎⠲⡕⡵⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⢰⢣⡳⡝⡮⠮⠪⡎⡎⡎⡎⡆⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠺⡸⠘⠀⠀⠀⠘⢬⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢳⡱⣝⠎⠀⠀⠣⡣⡣⣓⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠑⠕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠉⠀⠀⠀⠀⠀⠘⠪⠒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");

	images.push_back(image);
}

void BattleScene::Update(float deltaTime)
{

}

void BattleScene::Draw()
{
	Engine::Get().ClearImage(Engine::Get().ScreenSize().x + 10, Engine::Get().ScreenSize().y + 10);

	SetConsoleOutputCP(CP_UTF8);

	SetColor(Color::White);

	for (auto& line : images[0])
	{
		wcout << line << "\n";
	}
}

