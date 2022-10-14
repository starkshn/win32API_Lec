#pragma once

class CObject;

class Gravity
{
private:

	CObject*	p_owner;
	bool		_ground;

public:
	static bool _onLand;

public:
	Gravity();
	~Gravity();

public:
	void finalUpdate();

public:
	void SetOnGround(bool ground);

public:
	friend class CObject;
};

