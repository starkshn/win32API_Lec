#pragma once
#include "CObject.h"
class CCharingMissile : public CObject
{
private:
	float _dir;
	float _accSize;
	bool _shootMissile;

public:
	CCharingMissile();
	~CCharingMissile();

public:
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	void SetDir(bool up) { if (up) _dir = -1.f; else _dir = 1.f; }
	bool SetShoot(bool shoot) { return _shootMissile = shoot;  }

	float GetDir() { return _dir; }
	float GetAccSize() { return _accSize; }

};


