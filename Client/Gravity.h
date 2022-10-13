#pragma once

class CObject;

class Gravity
{
private:
	CObject*	p_owner;
	bool		_ground;

public:
	Gravity();
	~Gravity();

public:
	void finalUpdate();

public:
	void SetOnGround(bool ground) { _ground = ground; }

public:
	friend class CObject;
};

