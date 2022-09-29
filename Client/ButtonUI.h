#pragma once
#include "UI.h"
class ButtonUI : public UI
{
public:
	CLONE(ButtonUI);

public:
	ButtonUI();
	virtual ~ButtonUI() override;

public:
	virtual void update() override;

public:
	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;

};

