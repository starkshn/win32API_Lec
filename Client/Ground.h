#pragma once
#include "CObject.h"

class Collider;

class Ground : public CObject
{
private:
	CLONE(Ground);
	bool _onGround;

public:
	Ground();
	virtual ~Ground() override;

public:
	virtual void Init() override;
	virtual void update();

public:
	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionStay(Collider* other);
	virtual void OnCollisionExit(Collider* other);

public:
	void SetOnGround(bool onGround) { _onGround = onGround; }

};

