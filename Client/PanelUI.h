#pragma once
#include "UI.h"

class Texture;

class PanelUI : public UI
{
public:
	CLONE(PanelUI);

private:
	Vector2		_lbtnDownMousePos;

public:
	PanelUI();
	virtual ~PanelUI() override;

public:
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;

};

