#pragma once
#include "CObject.h"
#include "CMonster.h"

class Texture;

class MonsterMissile : public CMonster
{
private:
private:
	float		_theta; // πÊ«‚
	Vector2		_dir;   // Vector
	Texture*	p_monsterMissileTexture;

public:
	MonsterMissile();
	~MonsterMissile();
public:
	
private:
	virtual void update() final;
	virtual void render(HDC dc) final;

};

