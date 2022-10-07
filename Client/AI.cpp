#include "pch.h"
#include "AI.h"

#include "CMonster.h"
#include "State.h"

AI::AI()
	:
	p_curState(nullptr),
	p_owner(nullptr)
{

}

AI::~AI()
{
	SafeDeleteMap(_mapState);
}

void AI::update()
{
	p_curState->update();
}

void AI::AddState(State* state)
{
	State* _state = GetState(state->GetStateType());

	// state�� ���� ��쿡 �߰��� �ؾ��ϴ� �κ��̴�.
	if (_state != nullptr)
		assert(nullptr);

	_mapState.insert(make_pair(state->GetStateType(), state));
	state->p_ai = this;
}

State* AI::GetState(MONSTER_STATE state)
{
	map<MONSTER_STATE, State*>::iterator iter = _mapState.find(state);

	if (iter == _mapState.end())
		return nullptr;

	return iter->second;
}