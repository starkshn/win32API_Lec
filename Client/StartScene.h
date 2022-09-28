#pragma once
#include "CScene.h"
#include "CMonster.h"

class Texture;
class CMonster;

class StartScene : public CScene
{
private:
	int			_monsterId = 1;
	int			_monsterCount;
	Texture*	p_backGroundTexture;

public:
	StartScene();
	virtual ~StartScene() override;

private:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	void SetMonsterCount(int count) { _monsterCount = count; }

	int GetMonsterCount() { return _monsterCount; }

	void CreateMonster(int value)
	{
		float v = static_cast<float>(value);
		/*srand((unsigned)time(nullptr));
		float value = rand() % 3854 + 0.1f;*/

		CMonster* monster = new CMonster();
		monster->SetPos(Vector2(v*100.f, 50.f));
		monster->SetCenterAnchor(monster->GetPos());
		monster->SetScale(Vector2(50.f, 50.f));

		AddObject(monster, GROUP_TYPE::MONSTER);
	}
};