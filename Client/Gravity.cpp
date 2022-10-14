#include "pch.h"
#include "Gravity.h"

#include "CObject.h"
#include "RigidBody.h"

bool Gravity::_onLand = false;

Gravity::Gravity() 
	: 
	p_owner(nullptr),
	_ground(false)
{

}

Gravity::~Gravity()
{

}

void Gravity::finalUpdate()
{
	p_owner->GetRigidBody()->SetAccelAlpha(Vector2(0.f, 800.f));
}

void Gravity::SetOnGround(bool ground)
{
	_ground = ground;

	/*if (_onLand)
	{
		Vector2 v = p_owner->GetRigidBody()->GetVelocity();
		p_owner->GetRigidBody()->SetVelocity(Vector2(0.f, 0.f));
	}*/
	if (_ground)
	{
		Vector2 v = p_owner->GetRigidBody()->GetVelocity();

		// =====================================
		// 이부분은 컨텐츠에 따라 다르다.

		// 1. x축 방향으로 밀리고 싶을 경우
		// p_owner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));

		// 2. 점프킹 처럼
		p_owner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));

		// =====================================
	}
}
