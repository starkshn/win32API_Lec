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
	void ChangeState(MONSTER_STATE nextSTate);

public:
	void SetCurState(MONSTER_STATE state);

public:
	State* GetState(MONSTER_STATE state);
	CMonster* GetOwner() { return p_owner; }

	friend class CMonster;
};

