#pragma once

class AI;
class Cmonster;

#include "AI.h"

class State
{
private:
	AI*				p_ai;
	MONSTER_STATE	_state;
	
public:
	State(MONSTER_STATE);
	virtual ~State();

public:
	virtual void EnterState() abstract;
	virtual void ExitState() abstract;
	virtual void update() abstract;

public:
	AI* GetAI() { return p_ai; }
	MONSTER_STATE GetStateType() { return _state; }
	CMonster* GetOwnerMonter() { return p_ai->GetOwner(); }

	friend class AI;
};

