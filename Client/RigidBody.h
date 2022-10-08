#pragma once

class CObject;

class RigidBody
{
private:
	CObject* p_owner;

	Vector2 _force; // 크기, 방향
	Vector2 _accel;	// 가속도 
	Vector2 _velocity; // 속도 (크기 : 속력, 방향)
	float	_mass;	// 질량

	// F = M * A;
	// 가속도가 누적되서 '속도'가 나옴.
	// V += A * DT; => 현재속도
	


public:
	RigidBody();
	~RigidBody();

public:
	void update();
	void finalUpdate();

public:
	friend class CObject;
};

