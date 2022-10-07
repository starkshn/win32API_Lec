#pragma once

class CMonster;
class State;

class AI
{
private:
	map<MONSTER_STATE, State*>	_mapState;
	State*						p_curState;
	CMonster*					p_owner;

public:
	AI();
	~AI();

public:
	void update();

public:
	void AddState(State* state);

public:
	void SetCurState(MONSTER_STATE state);

public:
	State* GetState(MONSTER_STATE state);

	friend class CMonster;
};

