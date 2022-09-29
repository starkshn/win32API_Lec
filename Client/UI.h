#pragma once
#include "CObject.h"

class UI : public CObject
{
private:
	vector<UI*> _vecChildUI; // 깊은 복사 진행 해야함.
	UI*			p_parentUI;

	Vector2		_finalPos; // 최종 위치

	bool		_cameraAffected; // UI가 카메라에 영향을 받는지 유무
	bool		_onMouseCheck; // UI위에 마우스가 있는지 유무
	bool		_lbtnDown; // Lbtn Down유무

public:
	UI(bool cameraAffected);
	UI(const UI& origin);
	virtual ~UI() override;

public:
	virtual void update() override;
	virtual void finalUpdate() override;
	virtual void render(HDC dc) override;

	void updateChild();
	void finalUpdateChild();
	void renderChild(HDC dc);

public:
	void OnMouseCheck();
	bool IsMouseOn() { return _onMouseCheck; };
	bool IsLbtnDown() { return _lbtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

public:
	void AddChild(UI* ui)
	{
		_vecChildUI.push_back(ui);
		ui->p_parentUI = this;
	}
	
public:
	UI*					GetParentUI() { return p_parentUI; }
	Vector2				GetFinalPos() { return _finalPos; }
	const vector<UI*>	GetChild() { return _vecChildUI; }


	friend class UIManager;
};

