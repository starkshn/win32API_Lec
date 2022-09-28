#pragma once
#include "CObject.h"

class UI : public CObject
{
private:
	CLONE(UI);

	vector<UI*> _vecUI;
	UI*			p_parentUI;

	Vector2		_finalPos; // 최종 위치

	bool		_cameraAffected; // UI가 카메라에 영향을 받는지 유무
	bool		_onMouseCheck; // UI위에 마우스가 있는지 유무
	bool		_lbtnDown; // Lbtn Down유무

public:
	UI(bool cameraAffected);
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

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

public:
	void AddChild(UI* ui)
	{
		_vecUI.push_back(ui);
		ui->p_parentUI = this;
	}
	
public:
	UI*					GetParentUI() { return p_parentUI; }
	Vector2				GetFinalPos() { return _finalPos; }
	const vector<UI*>	GetChild() { return _vecUI; }


	friend class UIManager;
};

