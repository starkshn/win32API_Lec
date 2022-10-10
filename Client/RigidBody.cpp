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

	// 순수 힘의 크기
	float force = _force.Length();

	if (0.f != force)
	{
		// 방향
		_force.Normalize();

		// 가속도 : 순수 힘의 크기 / 질량
		float accel = force / _mass;

		// 힘의 방향이 곧 가속도의 방향이다.
		// (현재 방향벡터로 바뀐 _force * 가속도)
		// 가속도
		_accel = _force * accel; // == _accel = _force / _mass;

		 // 속도 (방향 + 속력) 한번 붙은 속도는 초기화 할 필요가 없다.
		_velocity += _accel * DeltaTime_F;
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	_force = Vector2(0.f, 0.f);
}

void RigidBody::Move()
{
	// 이동 속력
	float speed = _velocity.Length();

	if (0.f != speed)
	{
		// 이동 방향
		Vector2 dir = _velocity;
		dir.Normalize();

		Vector2 pos = p_owner->GetPos();
		pos += dir * speed * DeltaTime_F;

		// 사실상 밑에 코드가 _velocity * DeltaTime_F랑 같다
		// pos += _velocity * DeltatTime_F;

		p_owner->SetPos(pos);
	}
}