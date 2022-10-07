#pragma once

#include "State.h"

class Idle : public State
{
private:

	
public:
	Idle();
	~Idle();

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void update() override;

};
