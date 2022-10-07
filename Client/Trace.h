#pragma once

#include "State.h"

class Trace : public State
{
private:


public:
	Trace();
	~Trace();

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void update() override;

	
};

