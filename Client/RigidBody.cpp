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
		//
		// 가속도 (힘이 있을 경우에만 가속도 계산)
		_accel = _force * accel; // == _accel = _force / _mass;

	}

	// ============================================
	// 힘이 있든 없든  추가 가속도를 계산을 해야한다.
	// ============================================
	_accel += _accelAlpha; // 추가 가속도를 더한다.

	 // 속도 (방향 + 속력) 한번 붙은 속도는 초기화 할 필요가 없다.
	_velocity += _accel * DeltaTime_F;

	// =================
	// 마찰력 적용
	// =================
	
	// 마찰력에 의한 반대방향으로의 가속도
	if (!_velocity.IsZero())
	{
		Vector2 vel = _velocity;
		vel.Normalize();
		Vector2 friction = (-vel) * _frictCoeff * DeltaTime_F;

		if (_velocity.Length() <= friction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			_velocity = Vector2(0.f, 0.f);
		}
		else
		{
			_velocity += friction;
		}
	}
	
	// 최대속도 제한
	if (_velocity.Length() > _maxVelocity)
	{
		_velocity.Normalize();
		_velocity *= _maxVelocity;
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	_force = Vector2(0.f, 0.f);

	// 추가 가속도 누적량 초기화
	_accelAlpha = Vector2(0.f, 0.f);

	// 가속도 초기화
	_accel = Vector2(0.f, 0.f);
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