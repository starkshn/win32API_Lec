#pragma once

class CObject;

class RigidBody
{
private:
	CObject* p_owner;

	Vector2 _force;			// ũ��, ����
	Vector2 _accel;			// ���ӵ� 
	Vector2 _accelAlpha;	// �߰� ���ӵ�
	Vector2 _velocity;		// �ӵ� (ũ�� : �ӷ�, ����)

	float	_mass;			// ����
	float	_frictCoeff;	// ���� ���
	float	_maxVelocity;	// �ִ� �ӷ�

	// F = M * A;
	// ���ӵ��� �����Ǽ� '�ӵ�'�� ����.
	// V += A * DT; => ����ӵ�
	
public:
	RigidBody();
	~RigidBody();

public:
	void update();
	void finalUpdate();

private:
	void Move();

public:
	void AddForce(Vector2 force)
	{
		_force += force;
	}
	
	// ������ �� ��� �ӷ��� ���� �Լ�
	void AddVelocity(Vector2 velocity) { _velocity += velocity; }

public:
	void SetMess(float mass) { _mass = mass; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
	void SetMaxVelocity(float maxVelocity) { _maxVelocity = maxVelocity; }
	void SetAccelAlpha(Vector2 accelAlpha) { _accelAlpha = accelAlpha; }

public:
	float	GetMass() { return _mass; }
	Vector2 GetVelocity() { return _velocity; }
	float	GetMaxVelocity() { return _maxVelocity; }
	float	GetSpeed() { return _velocity.Length(); }

	friend class CObject;
};

