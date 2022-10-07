#pragma once

class CMonster;

enum class MONSTER_TYPE
{
	NONE,
	NORMAL,
	SLIME,
	ORC,
	SKELTON,

	END = 20,
};

class MonsterFactory
{
private:
	MonsterFactory();
	~MonsterFactory();

public:
	static CMonster* CreateMonster(MONSTER_TYPE type, Vector2 pos);

};

