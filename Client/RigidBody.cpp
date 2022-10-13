#include "pch.h"
#include "RigidBody.h"

#include "CTimeManager.h"

#include "CObject.h"

RigidBody::RigidBody()
	:
	p_owner(nullptr),
	_mass(1.f),
	_maxVelocity(200.f),
	_frictCoeff(100.f)
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
		//
		// ���ӵ� (���� ���� ��쿡�� ���ӵ� ���)
		_accel = _force * accel; // == _accel = _force / _mass;

	}

	// ============================================
	// ���� �ֵ� ����  �߰� ���ӵ��� ����� �ؾ��Ѵ�.
	// ============================================
	_accel += _accelAlpha; // �߰� ���ӵ��� ���Ѵ�.

	 // �ӵ� (���� + �ӷ�) �ѹ� ���� �ӵ��� �ʱ�ȭ �� �ʿ䰡 ����.
	_velocity += _accel * DeltaTime_F;

	// =================
	// ������ ����
	// =================
	
	// �����¿� ���� �ݴ���������� ���ӵ�
	if (!_velocity.IsZero())
	{
		Vector2 vel = _velocity;
		vel.Normalize();
		Vector2 friction = (-vel) * _frictCoeff * DeltaTime_F;

		if (_velocity.Length() <= friction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			_velocity = Vector2(0.f, 0.f);
		}
		else
		{
			_velocity += friction;
		}
	}
	
	// �ִ�ӵ� ����
	if (_velocity.Length() > _maxVelocity)
	{
		_velocity.Normalize();
		_velocity *= _maxVelocity;
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	_force = Vector2(0.f, 0.f);

	// �߰� ���ӵ� ������ �ʱ�ȭ
	_accelAlpha = Vector2(0.f, 0.f);

	// ���ӵ� �ʱ�ȭ
	_accel = Vector2(0.f, 0.f);
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