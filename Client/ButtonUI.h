#pragma once
#include "UI.h"

typedef void(*BTN_TYPE) (DWORD_PTR, DWORD_PTR);

class ButtonUI : public UI
{
public:
	CLONE(ButtonUI);

private:
	BTN_TYPE	f_btnFunc;
	DWORD_PTR	_param1;
	DWORD_PTR	_param2;

public:
	ButtonUI();
	virtual ~ButtonUI() override;

public:
	virtual void update() override;

public:
	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClick() override;

public:
	void SetClickedCallBack(BTN_TYPE func, DWORD_PTR param1, DWORD_PTR param2)
	{
		f_btnFunc = func;
		_param1 = param1;
		_param2 = param2;
	}

};

