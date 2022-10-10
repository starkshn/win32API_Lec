#include "pch.h"
#include "RigidBody.h"

#include "CTimeManager.h"

#include "CObject.h"

RigidBody::RigidBody()
	:
	p_owner(nullptr),
	_mass(1.f)
{
	
}

RigidBody::~RigidBody()
{

}

void RigidBody::update()
{

}

void RigidBody::finalUpdate()
{
	_force;

	// ���� ���� ũ��
	float force = _force.Length();

	if (0.f != force)
	{
		// ����
		_force.Normalize();

		// ���ӵ� : ���� ���� ũ�� / ����
		float accel = force / _mass;

		// ���� ������ �� ���ӵ��� �����̴�.
		// (���� ���⺤�ͷ� �ٲ� _force * ���ӵ�)
		// ���ӵ�
		_accel = _force * accel; // == _accel = _force / _mass;

		 // �ӵ� (���� + �ӷ�) �ѹ� ���� �ӵ��� �ʱ�ȭ �� �ʿ䰡 ����.
		_velocity += _accel * DeltaTime_F;
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	_force = Vector2(0.f, 0.f);
}

void RigidBody::Move()
{
	// �̵� �ӷ�
	float speed = _velocity.Length();

	if (0.f != speed)
	{
		// �̵� ����
		Vector2 dir = _velocity;
		dir.Normalize();

		Vector2 pos = p_owner->GetPos();
		pos += dir * speed * DeltaTime_F;

		// ��ǻ� �ؿ� �ڵ尡 _velocity * DeltaTime_F�� ����
		// pos += _velocity * DeltatTime_F;

		p_owner->SetPos(pos);
	}
}