#pragma once
#include "CObject.h"
#include "CTimeManager.h"

class MonsterMissile;
class Texture;
class Collider;

class AI;

struct MonsterInfo
{
	int		_id;
	float	_speed;
	float	_hp;
	float	_searchRange;
	float	_attackRange;
	float	_attackDamage;
};

class CMonster : public CObject
{
	CLONE(CMonster);
private:
	float			_speed;

	int				_id;
	int				_hp = 5;

	Texture*		p_texture;
	Texture*		p_missileTexture;

	// AI
	AI*				p_ai;
	MonsterInfo		_monInfo;

public :
	CMonster();
	virtual ~CMonster() override;

public :
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;

public:
	void CreateMonsterMissile();

private:
	void SetMonInfo(const MonsterInfo& info)
	{
		_monInfo = info;
	}

public:
	void SetSpeed(float speed) { _monInfo._speed = speed; }
	void SetMonsterId(int id) { _monInfo._id = id; }
	void SetAI(AI* ai);
	
public:
	float GetSpeed() { return _monInfo._speed; }

	friend class MonsterFactory;
};

