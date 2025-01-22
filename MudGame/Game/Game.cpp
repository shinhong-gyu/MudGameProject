#include "Game.h"

#include "Level/MenuLevel.h"
#include "Level/MainLevel.h"
#include "Level/BattleScene.h"
#include "Level/CraftLevel.h"

#include "Actor/Player.h"
#include "Level/GameOverLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	SetCursorType(CursorType::NoCursor);

	menuLevel = new MenuLevel();
	mainLevel = new MainLevel(CreateRandomMap());
	mainLevel->bIsMainLevel = true;
	craftLevel = new CraftLevel();
	gameOverLevel = new GameOverLevel();

	player = mainLevel->As<MainLevel>()->player;

	battleScene = new BattleScene();

	loseImage.push_back(L"⣿⣿⣟⢿⣿⣿⡿⡿⣿⣿⡿⡻⡫⣿⣿⣿⣿⡻⣝⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢟⣿⣿⣿⣿⣿⣿⣿⡇⠆⠕⢌⠪⡢⡹⡙⣟⢿");
	loseImage.push_back(L"⣿⣿⣿⡪⢻⣿⡗⡕⣕⢕⡗⡝⣎⣿⣿⡿⡣⣳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣎⡟⣿⣿⣿⣿⣿⣿⡑⢕⠱⡱⡸⡸⡸⡰⡹");
	loseImage.push_back(L"⣿⣿⣿⣇⢣⢙⠇⡎⡪⡺⡜⡕⣱⠿⡋⣇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣕⢝⢿⣿⣿⣿⡏⢜⢸⢸⢸⢸⢱⢹⢸");
	loseImage.push_back(L"⣿⣿⣿⣿⡌⢆⠕⡸⣘⢎⢮⢣⢊⠪⣼⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⡪⡎⣛⠫⡊⡌⢎⢜⢜⢜⢜⢜");
	loseImage.push_back(L"⣿⣿⣿⣿⡇⢆⠣⡱⡪⣪⢣⢣⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⡪⡣⡪⡨⡊⡎⡎⡎⡎⡧⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⠨⢪⢸⢜⢎⡇⡇⣺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡜⡜⣜⢜⡌⡎⡎⡮⣫⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⡘⢜⢜⢜⢵⡱⡱⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⢜⡜⡜⡌⡎⡮⣺⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⡪⡪⡪⡳⡕⡇⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢪⢣⡳⣹⢸⢸⢸⢺⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⢪⢪⡪⡇⡯⡪⡪⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⡻⡻⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣗⢕⢧⢳⡹⣸⡱⡽⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⢱⢱⢱⢕⢧⢣⢫⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⠱⡱⡱⡱⡕⡝⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⡫⡪⡣⣏⢶⡱⣻");
	loseImage.push_back(L"⣿⣿⣿⣿⡯⡪⡪⣪⢳⡹⡸⡸⣿⣿⣿⣿⣿⣿⣿⣿⣟⠢⡃⡇⡣⡃⡇⡷⣝⣟⠿⡻⡻⣿⣿⣿⣿⣿⣿⣿⣇⢇⢏⢗⡕⡧⣻⢺⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⡯⡪⡪⣪⢣⡳⡕⣝⣿⣿⣿⣿⣿⣿⣿⣟⡔⠡⡊⢎⠮⡮⡪⣪⢳⠣⡃⡎⡆⡇⡻⣿⣿⣿⣿⣿⡇⡇⣏⢞⢎⢯⣪⣻⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⡇⡗⡝⡜⡎⣞⢜⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣭⣮⣬⣮⣽⢝⣝⠢⠨⢂⢮⡪⣳⢱⢡⢹⣿⣿⣿⣿⢸⢸⡸⣕⢏⢧⣣⣻");
	loseImage.push_back(L"⣿⣿⣿⣿⡇⡗⡕⣝⢜⢎⢇⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢗⢝⠴⡍⡎⡎⡎⡎⢮⣣⢣⡑⣿⣿⣿⣟⢜⢜⢼⡸⡵⣹⢜⣾⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⡇⡇⡏⡎⡎⡎⣎⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⡎⡎⣝⢮⡣⣏⢮⡊⣜⢮⢪⠢⣿⣿⣿⡏⡎⣗⡕⣗⡝⡮⣳⣻⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⡪⡣⡫⡪⡪⢪⢪⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣛⢜⢎⢑⢜⣞⢼⡪⣞⢌⢎⢮⢣⢃⣿⣿⣿⢱⢱⢵⡹⣪⢮⡫⣞⣿");
	loseImage.push_back(L"⣿⣿⣿⣿⢜⢎⢮⢣⢣⢣⢣⠣⢿⣿⣿⣿⠿⠿⡻⢛⢫⠱⡘⡔⡅⢖⢰⢑⠜⢕⢍⠬⡂⢱⡝⣎⢆⢻⣿⢣⢣⢳⢵⡴⡻⡳⣑⡛⢻");
	loseImage.push_back(L"⣿⣿⣿⡟⡕⡝⡜⡜⡕⡕⡕⡑⠍⢟⢟⠱⡑⡕⢌⠪⡘⢜⠜⡜⢜⢔⢅⠣⡊⡎⡮⣪⢇⢪⢺⡸⢬⡿⡣⡱⡵⡹⡜⣎⢗⡝⡔⡕⣿");
	loseImage.push_back(L"⣿⣿⣿⡟⡕⡝⡜⡜⡕⡕⡕⡑⠍⢟⢟⠱⡑⡕⢌⠪⡘⢜⠜⡜⢜⢔⢅⠣⡊⡎⡮⣪⢇⢪⢺⡸⢬⡿⡣⡱⡵⡹⡜⣎⢗⡝⡔⡕⣿");
	loseImage.push_back(L"⣿⣿⣿⢣⠣⡣⡑⢌⠪⢌⠢⡡⡱⢰⢸⢸⢘⢌⠪⡨⠨⡂⠕⡌⡆⢕⢱⢱⢱⢨⢫⢺⢨⣖⠵⡸⡚⡕⡕⡵⡹⡸⡹⣜⢵⢱⢱⢩⣿");
	loseImage.push_back(L"⣿⣿⣿⢣⠣⡣⡑⢌⠪⢌⠢⡡⡱⢰⢸⢸⢘⢌⠪⡨⠨⡂⠕⡌⡆⢕⢱⢱⢱⢨⢫⢺⢨⣖⠵⡸⡚⡕⡕⡵⡹⡸⡹⣜⢵⢱⢱⢩⣿");
	loseImage.push_back(L"⣿⡿⢋⠢⡑⠔⢌⠢⡑⢅⠕⡌⢆⢇⠣⠣⡑⡔⢌⢔⡑⡜⡌⡖⡜⣢⢑⢕⢝⢎⢇⠮⣺⠪⡑⡔⡎⢎⢪⢸⢸⢸⢱⡱⢕⢱⢑⢜⣿");
	loseImage.push_back(L"⠯⡡⡱⡸⡄⢱⢱⡓⢮⢜⡼⢄⢑⡔⡝⢜⠬⡸⡸⡰⡱⡱⡱⡱⡱⡑⡅⡕⡝⡎⡘⢮⠣⡁⡪⢨⠘⢌⢢⢑⠕⠕⠕⡍⢎⠢⢣⠢⠻");
	loseImage.push_back(L"⣗⣝⢮⡳⣝⢵⡳⣱⢌⡇⢜⢜⡲⣢⠨⢢⢣⠣⡃⡣⣑⢅⢦⡣⡣⡧⣳⢸⡨⡪⡪⢕⠨⡬⣪⢗⠨⡊⡢⡑⢅⢃⢅⠑⡅⡣⢡⡱⣑");
	loseImage.push_back(L"⣿⣾⣳⢽⣪⢗⡯⣺⢵⢝⢮⣪⡪⣪⢪⡰⣱⢱⢝⢮⢮⡳⣳⢽⢝⡾⡵⡯⡾⡽⡵⣵⢫⠞⡕⣑⢑⡬⡲⣜⢎⡗⡭⡳⡬⡨⢂⠯⣎");
	loseImage.push_back(L"⣿⣾⣳⢽⣪⢗⡯⣺⢵⢝⢮⣪⡪⣪⢪⡰⣱⢱⢝⢮⢮⡳⣳⢽⢝⡾⡵⡯⡾⡽⡵⣵⢫⠞⡕⣑⢑⡬⡲⣜⢎⡗⡭⡳⡬⡨⢂⠯⣎");
	loseImage.push_back(L"⣿⣿⣿⣿⣿⣿⣿⣷⣝⣮⡺⣝⡵⡻⣺⡪⡯⡯⣯⡻⡮⣗⣟⣞⣮⢯⢯⣗⢯⢾⢽⢽⢵⡳⣝⢮⡺⣪⡳⡭⣣⣫⣮⣮⣧⣳⣵⣷⣿");
	loseImage.push_back(L"⡿⣿⣿⢿⡿⣿⢿⣿⢿⡿⣿⣾⣾⢿⢾⡾⣽⣽⡾⣽⡽⣷⣻⣞⣷⣻⡽⡾⣽⢯⣯⢿⣷⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡿");

	winImage.push_back(L"⠀⠀⠀⢀⢀⢄⢔⠰⡑⡌⢆⠣⡊⡢⡱⡘⢔⢑⢌⠢⡑⠔⡐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⠄⢠⢪⢪⢢⢰⢁⢆⢤⠂⢄⠀⠀⠀⠀");
	winImage.push_back(L"⠀⠠⡊⠔⡑⢔⢅⢣⢱⢘⢜⢌⠪⡂⡮⡘⢌⠢⡕⢅⠇⠕⡨⡊⠀⠀⠀⠀⠀⠀⢠⢢⢌⣇⠡⠩⡂⡇⡇⠌⣖⠁⢗⢕⠅⡕⢔⢅⠀⠀");
	winImage.push_back(L"⢈⠢⢊⠌⢌⢢⠣⢕⢱⢱⠈⡎⠊⢮⡪⡨⠂⢡⢣⠣⢃⠜⠡⠂⠀⠀⠀⠀⠀⠀⡨⡪⢱⠑⠅⠁⠑⡁⠰⡁⠊⡀⠸⢰⡑⡅⠣⡑⢌⠢");
	winImage.push_back(L"⠠⡡⡑⢌⢆⢎⢜⠨⡘⢜⢆⢕⠀⣗⢕⠐⢀⢎⢇⠏⠂⠊⠀⠀⠀⠀⠀⠀⠀⠀⢢⢕⠤⡡⠈⠢⣁⠀⢪⠂⠨⠀⢢⠐⡄⢐⠀⠐⠀⠀");
	winImage.push_back(L"⠈⠄⢇⢇⢗⠕⠅⠈⠢⡈⢮⡳⡀⡗⣕⠀⣜⢎⠅⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠉⠂⠈⢲⣀⠱⢄⠈⡆⠒⢄⢈⡳⡅⠘⢜⠀⠀⠀");
	winImage.push_back(L"⠀⠀⠈⠈⠂⠫⢮⠀⡖⠈⢳⢹⢜⢞⡜⡮⡪⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢢⢱⡀⢇⠆⠀⠘⢮⡳⡀⡸⠀⠀⠀");
	winImage.push_back(L"⠀⠀⠀⠀⠀⠀⢸⡺⡂⠀⠀⡯⣪⢣⢳⡱⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⢣⡱⠀⠀⠀⠈⡮⣣⡫⠀⢀⠔");
	winImage.push_back(L"⠀⠀⠀⠀⠀⠀⢘⢮⠃⠀⠀⡯⣪⡣⡇⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⠀⠀⠀⡳⠭⠀⠀⠀⠀⢙⢞⡦⡰⠁⠀");
	winImage.push_back(L"⠀⠀⡸⡂⠀⠀⢰⢝⠅⠀⠀⣯⡲⣕⢝⡌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠀⠀⢨⢝⡀⠀⠀⠀⠀⣟⣞⠅⠀⠀");
	winImage.push_back(L"⠀⠀⡱⡡⠀⠀⢸⢝⠅⠠⡔⡧⡳⣱⢣⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⠈⡖⢭⠄⢀⢀⠀⢸⣞⡆⠀⠀");
	winImage.push_back(L"⠀⢐⢕⢝⡄⠀⢸⢵⠁⠀⢱⡣⣫⡪⡺⡂⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡄⠀⠀⠀⡂⠑⢄⢇⢇⢇⡀⠈⠒⣜⡮⣗⠀⠀");
	winImage.push_back(L"⠀⡱⡱⡕⡬⡂⢮⡳⡅⠀⢸⢸⢒⢝⣜⠠⠀⠀⠀⠀⠠⣺⡐⡔⡀⠀⠀⠀⠀⠄⡂⠊⠀⠀⠀⠀⡣⡂⠈⢪⢪⢣⡣⡀⠀⠘⣽⡺⡄⠀");
	winImage.push_back(L"⠆⣫⢪⡺⡸⡠⣫⢾⡐⡀⢸⢸⢸⡱⣪⡊⠨⢀⢀⢀⡈⣘⠎⢎⢄⢠⢀⠢⠁⠁⠀⠀⠀⣖⡀⠠⡱⡰⠀⡱⡱⡱⡕⣕⠤⠀⢸⢽⡢⠀");
	winImage.push_back(L"⠜⢼⡸⡸⡸⣘⢮⢗⢕⠂⡎⡎⡮⡪⢮⠀⠈⠐⠀⠕⢝⢼⠸⡸⡸⡈⠀⠀⠀⠀⠀⠀⡸⡵⡳⣌⢪⢨⢑⢕⢕⢕⠭⡲⡠⡀⠸⣝⢮⠀");
	winImage.push_back(L"⢎⡇⡇⡇⢇⢇⡯⡯⡢⡃⣇⠧⡳⡹⡪⠀⠀⠀⠀⠀⢡⡳⡕⣎⢎⡂⠀⠀⠀⠀⢐⠤⢎⢯⢺⢜⢵⡙⡢⡑⢜⢌⢎⢎⢲⢹⢰⡀⡳⣝⢆");
	winImage.push_back(L"⢣⡣⡇⡇⡇⡇⣟⢮⠢⡣⡪⣪⢺⢸⠪⠀⠨⡀⠀⠀⡼⣸⢺⢸⢪⠀⠀⠀⠀⢐⠤⢎⢯⢺⢜⢵⡙⡢⡑⢜⢌⢎⢎⢲⢹⢰⡀⡳⣝⢆");
	winImage.push_back(L"⠮⡢⡫⡪⡎⣖⣗⢧⠣⡹⡸⡸⡸⡱⡕⠀⡜⡬⠀⠀⣹⣪⡳⡵⣝⠄⠀⢀⠂⢪⢪⡪⡮⣳⡹⣕⢗⢮⢨⠸⡸⡰⡱⡱⡱⣕⢅⢫⢮⢧");
	winImage.push_back(L"⢘⢜⡝⣜⡱⣜⢮⢇⠇⡏⡎⡎⡇⡧⡣⡀⡇⡇⡅⢠⢳⠵⣝⢮⢳⡁⠀⠰⡱⡱⡱⣱⢝⣜⢮⢎⡯⡮⣆⢣⠣⡊⡎⣎⢎⡪⡢⢹⣪⢳");
	winImage.push_back(L"⠸⡸⡜⡎⡮⣪⢯⢣⡫⡪⡪⡪⡪⡪⡪⡜⢜⢜⠌⣜⠮⣝⠪⡳⡳⡱⡀⠪⡪⡪⡪⡮⣳⢕⢗⡳⣕⢧⡑⢕⢕⢱⢱⠱⣕⢵⢹⢪⢎⢷");
	winImage.push_back(L"⢸⢠⢣⢣⢳⡱⡝⢎⢪⢸⠸⡸⢕⡝⡜⡮⡱⣑⢅⡗⡝⡆⠀⠉⡮⡳⡢⡱⡸⢜⢝⣝⢮⣫⡳⣝⡮⣣⡫⡢⡣⢪⢸⡸⡜⡮⡪⡮⣫⣳");
	winImage.push_back(L"⢼⣸⢸⡸⡼⣪⡪⡪⡪⡊⠔⡐⡑⣳⢹⢸⠪⡲⢱⢕⡝⢄⠁⠀⡼⡸⡸⣸⢸⢱⡳⡳⢫⢸⢞⠵⠫⡓⠝⡌⢎⢜⢜⢜⢜⢮⡳⡹⡪⡎");
	winImage.push_back(L"⡝⣮⡳⠽⡝⡶⡵⣕⣕⢕⠡⠂⡂⠔⢐⢀⠂⡂⣱⢳⠁⡂⠨⢀⠹⣜⡅⠄⢂⠁⡂⢐⠐⡐⡐⠌⠌⢄⢕⡪⡱⡱⣕⢇⡏⣇⠯⣏⢗⠀");
	winImage.push_back(L"⡕⠵⡽⣝⢮⢝⢜⡔⡆⡇⡇⡅⡂⡁⠢⡂⢆⣢⣢⢣⠨⡘⡜⡌⡊⡌⣆⣂⠐⡀⢂⠐⡐⢐⢄⢥⢕⢧⡣⡣⣝⡜⣎⢗⣝⢼⢹⢼⢱⠁");
	winImage.push_back(L"⢱⠱⡱⡱⣣⢫⡓⡵⡜⡜⡌⡎⢆⠂⠅⠕⡑⡑⠜⡐⢅⠕⡨⠨⢊⠔⡑⠕⢑⠐⡀⡆⣆⢖⢇⢇⢇⡇⡗⡽⣪⣚⢎⡏⣮⡳⡕⡇⢇⠕");
	winImage.push_back(L"⢕⢕⠱⡘⡌⣓⢎⢎⢎⢳⡑⡕⢕⠕⡅⣂⢐⠠⠑⠨⠐⢐⠠⠑⡐⠐⡈⣈⢴⡘⡮⡯⢮⢮⢺⢕⢵⢫⢮⡻⡜⣎⢇⢗⢕⠕⢅⠣⡡⠅");

	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣦⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣟⣟⢟⡿⣽⣷⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⢝⣽⣯⣾⣿⣿⣿⣿⣿⣦⣶⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⢿⣟⣿⣿⣿⡿⣿⡿⣿⣿⣿⣿⣿⣶⣦⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣷⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⢿⣯⣿⣿⣾⣿⣿⣿⣷⣿⣷⣿⡟⠙⠚⠓⠛⠝⠟⠿⠛⠛⢿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣽⣿⣽⣿⢷⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣬⠀⠀⠀⠀⠀⣰⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⢺⣿⣿⣿⡿⢿⣾⣿⢿⣯⣿⣿⣟⣿⡿⣿⣟⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣖⢶⡶⣾⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠇⠸⣿⣿⣿⣿⡿⣿⡿⣿⣿⡿⣿⣿⣧⣀⣀⣤⣤⣤⣤⣤⡾⣿⣿⢿⣿⣿⢿⣷⡷⣻⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⡀⠀⠀⠀⣿⣿⣿⠀⠀⢹⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⢷⣹⣿⣿⣟⣿⡷⣿⣻⣿⣟⣿⣯⣟⣏⢻⣿⣽⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠈⠐⠤⣀⢹⣿⡿⠀⠀⠈⣿⣿⣿⣿⣯⣿⣿⣷⣿⣿⣯⣿⠺⣿⣽⣿⣽⣿⢿⣿⣿⣿⣿⢯⢿⡟⣼⡿⢧⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠈⢿⣾⣷⡀⠀⠀⣿⣿⢿⣷⣿⣿⣯⣿⣿⣷⣿⣿⣻⣿⣿⣿⣽⣿⣿⣿⣿⣻⣿⣿⣿⣷⣿⡜⣣⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠈⠋⠉⠙⢶⣤⣸⣿⣿⣿⣯⣿⣿⣻⣷⣻⡾⣶⣹⣿⣿⣽⣯⣿⣷⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣶⡀⠀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣷⣿⣿⢗⣿⢾⣽⣻⢾⣾⡿⣯⣿⣟⣿⣻⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣶⡀⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⢷⣿⣞⡿⣽⣻⣗⣯⡿⣫⠺⠿⣿⣽⡏⠋⠙⣟⣯⣿⣿⣿⣿⣌⠙⣥⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣻⡾⣟⣿⣽⡳⣟⡾⣹⡗⠱⣄⢹⣾⠁⠀⠀⠘⢿⣿⣿⣿⢿⣿⣿⣿⡿⣿⢿⠿⣿⡄⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣽⣻⣟⣿⣻⣿⠝⠞⠟⢠⣿⢻⣧⡁⠀⠀⠀⠀⠀⠻⢿⣿⢿⢟⣾⣿⣿⣿⣿⣿⣟⡅⠀⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⣯⢿⣽⣟⡿⠀⠀⠀⠀⠘⣷⣽⡇⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠈⠉⠉⠉⠑⢯⣾⡯⣄⡀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣫⣷⣟⣿⡽⣦⡀⠀⠀⠙⠞⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀");
	runImage.push_back(L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠺⣽⣞⣯⠿⡽⠢⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
}

Game::~Game()
{
	if (bShowMenu)
	{
		if (backLevel)
		{
			delete backLevel;
			backLevel = nullptr;
			mainLevel = nullptr;
		}
	}
	else
	{
		if (!mainLevel->As<GameOverLevel>())
		{
			delete gameOverLevel;
		}
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	delete craftLevel;
	delete battleScene;
	menuLevel = nullptr;
	gameOverLevel = nullptr;
	battleScene = nullptr;
	craftLevel = nullptr;
}

void Game::InitGame()
{
	Engine::Get().ClearImage(100, 100);

	mainLevel = new MainLevel(CreateRandomMap());
	mainLevel->bIsMainLevel = true;
	player = mainLevel->As<MainLevel>()->player;

	menuLevel = new MenuLevel();
	craftLevel = new CraftLevel();
	gameOverLevel = new GameOverLevel();
	battleScene = new BattleScene();
	backLevel = menuLevel;
}

vector<vector<char>> Game::CreateRandomMap()
{
	const char EMPTY = '.';
	const char TREE = '#';
	const char PLAYER = 'P';

	int height = Engine::Get().ScreenSize().y;
	int width = Engine::Get().ScreenSize().x;

	vector<vector<char>> map(height, vector<char>(width));

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			map[y][x] = EMPTY;
		}
	}

	map[0][0] = 'P';

	int treeCount = Random(15, 25);  // 나무는 최소 15개, 최대 25개

	while (treeCount > 0) {
		int x = Random(0, width) % width;
		int y = Random(0, height) % height;
		if (map[y][x] == EMPTY) {
			map[y][x] = TREE;
			--treeCount;
		}
	}
	return map;
}

void Game::ToggleMenu()
{
	system("cls");

	bShowMenu = !bShowMenu;

	mainLevel->bIsMainLevel = false;

	if (bShowMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}

	mainLevel->bIsMainLevel = true;
}

void Game::CraftMode()
{
	system("cls");

	mainLevel->bIsMainLevel = false;

	backLevel = mainLevel;
	mainLevel = craftLevel;

	mainLevel->bIsMainLevel = true;
}

void Game::SetMap()
{
	if (mainLevel == nullptr)
	{
		mainLevel = new MainLevel(CreateRandomMap());
	}
	else
	{
		if (auto mainL = mainLevel->As<MainLevel>())
		{
			mainL->SetMap(CreateRandomMap());
		}
	}
}

void Game::IntoBattleScene()
{
	system("cls");

	mainLevel->bIsMainLevel = false;

	backLevel = mainLevel;

	if (auto* bl = battleScene->As<BattleScene>())
	{
		bl->bIsExpired = false;
	}

	mainLevel = battleScene;

	mainLevel->bIsMainLevel = true;
}

void Game::BackToMainLevel()
{
	Engine::Get().SetCursorPosition(0, 0);

	system("cls");
	Engine::Get().ClearInfoUI();
	mainLevel->bIsMainLevel = false;

	if (backLevel->As<MainLevel>())
	{
		mainLevel = backLevel;
	}
	mainLevel->bIsMainLevel = true;
}

void Game::PrintLoseImage()
{
	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	SetColor(Color::White);
	Engine::Get().SetCursorPosition(0, 0);

	for (const auto& line : loseImage)
	{
		wcout << line << L"\n";
	}
	SetConsoleOutputCP(949);
	SetColor(Color::Red);
	cout << "곰과 싸워서 패배했다 (HP -3)\n\n";

	SetColor(Color::White);
	cout << "ESC 눌러서 계속하기\n";
}

void Game::PrintWinImage()
{
	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	SetColor(Color::White);
	Engine::Get().SetCursorPosition(0, 0);

	for (const auto& line : winImage)
	{
		wcout << line << L"\n";
	}
	SetConsoleOutputCP(949);
	SetColor(Color::Green);
	cout << "곰과 싸워서 승리했다 (고기 +1)\n\n";

	SetColor(Color::White);
	cout << "ESC 눌러서 계속하기\n";
}

void Game::PrintRunImage()
{
	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	SetColor(Color::White);
	Engine::Get().SetCursorPosition(0, 0);

	for (const auto& line : runImage)
	{
		wcout << line << L"\n";
	}
	SetConsoleOutputCP(949);
	SetColor(Color::Blue);
	cout << "도망치는데 성공했다.\n\n";

	SetColor(Color::White);
	cout << "ESC 눌러서 계속하기\n";
}

void Game::GameOver()
{
	system("cls");
	mainLevel = gameOverLevel;
	backLevel = mainLevel;

	SetConsoleOutputCP(CP_UTF8);
	wcout << L"⡿⣿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⣻\n";
	wcout << L"⢿⣽⢯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⢽⣷\n";
	wcout << L"⣯⣟⣯⣿⠈⣷⣿⠈⣷⠀⣿⣳⣟⣾⣳⣿⣀⣀⣀⠨⣀⣀⣀⣞⣷⣻⣞⣷⣻⣾⠁⣿⣞⣷⡇⢸⣷⣟⣾⣳⣟⠚⡓⢛⠚⣣⠹⡆⢸⣯⡿⣞\n";
	wcout << L"⣻⣾⣳⠟⣀⠹⣾⠅⣙⠀⣿⣟⣾⡽⣷⡝⠓⣉⣴⢶⣌⡙⠺⣗⣿⣵⣟⡷⡿⠎⣠⡘⠿⣺⡇⢹⣟⣾⡽⣷⣻⡏⢹⡏⢹⣟⠸⡇⢸⡿⣾⣟\n";
	wcout << L"⡿⣾⣥⣴⣿⡷⣴⢃⣿⠀⣿⣟⡾⣯⣟⠛⠛⠛⠛⠐⠛⠛⠛⢻⣵⢿⣞⣿⣦⡾⠛⠛⠆⠛⠣⢾⡿⣽⢾⣯⢿⣇⢸⡇⢸⡿⢠⡄⢸⣟⣷⢯\n";
	wcout << L"⣿⣳⢿⡾⢁⣴⣶⣶⣤⠙⣿⣽⣻⣽⣻⢿⡏⢽⣿⣿⡿⣿⡿⣿⢯⣿⣽⣞⣷⡟⠛⡛⡛⡛⡃⣺⣟⣯⣿⣳⣯⣡⣬⣥⣬⡽⢨⡇⢸⣯⣟⣯\n";
	wcout << L"⡾⣯⣟⣿⣤⣉⣑⣉⣠⣴⣿⢷⣻⢾⣯⣟⣇⣀⣀⣀⣀⣀⣀⣟⡿⡾⣾⡽⣾⣇⣘⣋⣛⣙⣋⣹⣟⣾⢗⣿⣳⣟⣷⣻⣞⣯⣘⣇⣸⣟⣾⢯\n";
	wcout << L"⡿⣿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⢿⢿⡿⡿⣿⣻\n";
	wcout << L"⢿⣽⢯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⣽⣻⣯⣟⣿⢽⣷\n";

	if (auto* gol = dynamic_cast<GameOverLevel*>(gameOverLevel))
	{
		gol->TimerWork();
	}
}

void Game::AliveSuccess()
{
	system("cls");
	mainLevel = gameOverLevel;
	backLevel = mainLevel;

	SetConsoleOutputCP(CP_UTF8);

	wcout << L"⣟⣟⣯⣿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣯⢿⣻⣽\n";
	wcout << L"	⣽⡽⣷⣻⡾⣽⣻⣗⡿⣯⢿⣞⣿⡽⣾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⢾⣻⣽⡾\n";
	wcout << L"	⣯⢿⣽⢾⠻⣽⢷⠛⣽⠫⣟⣷⢯⣿⢽⣻⠞⠟⠯⠻⠻⠝⠯⡿⣯⣟⣿⢽⣯⢿⣯⠻⣻⣽⢯⡟⢫⣟⣿⢽⣯⢿⡯⡟⠟⠽⠫⠟⠯⢟⣿⢽⣷⣻\n";
	wcout << L"	⣾⣻⣽⠯⠈⣿⢯⠅⠿⢈⣿⢾⣻⣽⣻⣽⢿⠽⠋⣠⡙⠯⣯⣿⣳⢿⣺⡿⣞⣿⠾⠈⢿⡚⡛⡃⢺⣻⣾⣻⡽⣯⢿⣽⢯⡟⢽⣯⡇⢺⣽⣟⣾⡽\n";
	wcout << L"	⣯⣷⠋⣡⡷⣌⢻⡀⣾⢐⣯⡿⣽⣾⣻⢾⢴⣲⣿⠉⡿⣖⣦⢾⣽⣻⣽⢯⡿⠙⣡⡷⣌⠙⣟⡇⢼⣟⣾⡽⣯⢿⠫⠻⠹⠃⠜⠗⠧⠛⢗⣯⡷⣟\n";
	wcout << L"	⣻⢾⣻⡯⠟⢋⣋⣒⠛⢴⡷⣟⣿⣺⣽⡵⡦⢦⢶⡴⣦⢶⡴⣦⢷⡿⣾⣻⣻⢿⡽⠛⣙⣙⡙⠓⣾⡽⣾⣻⣽⣟⣯⡿⠛⣙⣙⡙⠻⣻⣽⢷⣟⣿\n";
	wcout << L"⡽⣿⢽⣇⠸⠿⡽⡾⠻⢠⡿⣯⡷⣟⣷⣟⡇⢸⢟⢯⠿⡯⡿⣽⣯⢿⣽⢾⣻⣽⣇⠺⠯⡿⡽⠇⣸⣯⣟⣷⣻⣞⣷⢅⠻⢽⠯⠿⢁⣽⢾⣻⣽⢾\n";
	wcout << L"	⣻⣽⡯⣿⡽⣶⣲⡶⣞⣯⣿⣳⡿⣯⣷⣻⣗⣶⢶⢶⡶⣖⣾⣳⢿⡽⣯⣟⡿⡾⣾⣳⡶⣶⣲⣾⣻⣞⡷⣯⡷⣿⢽⣯⢷⣖⣶⡶⡿⣞⣿⣻⢾⣻\n";
	wcout << L"	⣟⣾⣻⢷⣟⣯⡷⣟⣯⣷⣯⡷⣟⣷⣟⣾⣽⢾⣻⣯⣟⣯⡷⣟⣯⣿⣻⣞⣿⣻⣽⢷⣟⣯⡷⣟⣾⣽⣻⣽⢯⣿⣽⢾⣻⣽⢾⣻⣻⣯⡷⣟⣿⡽\n";
	wcout << L"	⡿⣞⣯⣟⣷⣻⣽⢿⣽⢾⣞⣿⡽⣷⣻⡾⣽⣻⣽⢾⣽⢾⣻⣯⡷⣟⣾⣽⢾⣻⣞⣯⡿⣞⡿⣯⡷⣟⣷⣻⣟⣾⢾⣻⣟⣾⢿⡽⣷⢯⣟⣯⡷⡯\n";

	if (auto* gol = dynamic_cast<GameOverLevel*>(gameOverLevel))
	{
		gol->TimerWork();
	}

}


