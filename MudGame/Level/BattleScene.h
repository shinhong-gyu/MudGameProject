#pragma once
#include "Level/Level.h"
#include <vector>
#include <string>

using namespace std;

class BattleScene : public Level
{
	RTTI_DECLARATIONS(BattleScene, Level)

public:
	BattleScene();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	vector<vector<wstring>> images;
};