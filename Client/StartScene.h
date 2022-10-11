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

	// Force Èû ±×¸®±â
	bool		_useForce;
	Vector2		_mouseForcePos;
	float		_forceCurRadius;
	float		_forceRadius;
	float		_force;

public:
	StartScene();
	virtual ~StartScene() override;

private:
	virtual void Enter() override;
	virtual void update() override;
	virtual void render(HDC dc) override;
	virtual void Exit() override;

public:
	void CreateForce();

public:
	void SetMonsterCount(int count) { _monsterCount = count; }

	int GetMonsterCount() { return _monsterCount; }
};
