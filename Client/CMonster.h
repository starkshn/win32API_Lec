#pragma once
#include "CObject.h"
#include "CTimeManager.h"

class MonsterMissile;
class Texture;
class Collider;

class CMonster : public CObject
{
private :
	CLONE(CMonster);
	float			_speed;
	float			_loopDistance;
	float			_acc;
	int				_dir; // 1, -1
	int				_id;
	int				_hp = 5;
	bool			_missileFire = true;
	Vector2			_centerAnchor;

	Texture* p_texture;
	Texture* p_missileTexture;

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

	void MissileCoroutine(float deltaTime_f)
	{
		SetAcc(deltaTime_f);
		
		if (GetAcc() > 1.f)
		{
			SetMissileFire(true);
			SetAcc(0.f);
		}
		else
		{
			SetMissileFire(false);
		}
	}

public:
	void SetSpeed(float speed) { _speed = speed; }
	void SetCenterAnchor(Vector2 anchor) { _centerAnchor = anchor; }
	void SetLoopDistance(float loopDis) { _loopDistance = loopDis; }
	void SetMoveDistance(float dis) { _loopDistance = dis; }
	void SetMonsterId(int id) { _id = id; }
	void SetMissileFire(bool fire) { _missileFire = fire; }
	void SetAcc(float deltaTime) { _acc += deltaTime; }
	
public:
	float GetSpeed() { return _speed; }
	Vector2 GetCenterAnchor() { return _centerAnchor; }
	float GetLoopDistance() { return _loopDistance; }
	int GetMonsterId() { return _id; }
	bool GetMissileFire() { return _missileFire; }
	float GetAcc() { return _acc; }
};

