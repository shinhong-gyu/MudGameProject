﻿#include "Game.h"

#include "Level/MenuLevel.h"
#include "Level/MainLevel.h"
#include "Level/BattleScene.h"
#include "Level/CraftLevel.h"

#include "Actor/Player.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	SetCursorType(CursorType::NoCursor);

	menuLevel = new MenuLevel();
	mainLevel = new MainLevel(CreateRandomMap());
	craftLevel = new CraftLevel();
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
}

Game::~Game()
{
	if (bShowMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::InitGame()
{
	backLevel = menuLevel;

	Engine::Get().ClearImage(100, 100);

	mainLevel = new MainLevel(CreateRandomMap());
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

	if (bShowMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}

void Game::CraftMode()
{
	system("cls");

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

	backLevel = mainLevel;
	mainLevel = battleScene;

	mainLevel->bIsMainLevel = true;
}

void Game::BackToMainLevel()
{
	system("cls");
	mainLevel->bIsMainLevel = false;

	if (backLevel->As<MainLevel>())
	{
		mainLevel = backLevel;
	}
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
	cout << "ESC 눌러서 계속하기\n";


}


