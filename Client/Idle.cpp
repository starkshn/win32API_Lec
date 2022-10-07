#include "pch.h"
#include "Idle.h"

Idle::Idle() : State(MONSTER_STATE::IDLE)
{

}

Idle::~Idle()
{

}

void Idle::EnterState()
{

}

void Idle::ExitState()
{

}

void Idle::update()
{
	// Player의 위치 체크 

	// 범위 안에 들어오면 추적 상태로 전환

}

