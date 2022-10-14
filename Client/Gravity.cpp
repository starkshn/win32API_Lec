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
		// �̺κ��� �������� ���� �ٸ���.

		// 1. x�� �������� �и��� ���� ���
		// p_owner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));

		// 2. ����ŷ ó��
		p_owner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));

		// =====================================
	}
}
