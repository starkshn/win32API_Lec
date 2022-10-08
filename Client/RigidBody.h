#pragma once

class CObject;

class RigidBody
{
private:
	CObject* p_owner;

	Vector2 _force; // ũ��, ����
	Vector2 _accel;	// ���ӵ� 
	Vector2 _velocity; // �ӵ� (ũ�� : �ӷ�, ����)
	float	_mass;	// ����

	// F = M * A;
	// ���ӵ��� �����Ǽ� '�ӵ�'�� ����.
	// V += A * DT; => ����ӵ�
	


public:
	RigidBody();
	~RigidBody();

public:
	void update();
	void finalUpdate();

public:
	friend class CObject;
};

