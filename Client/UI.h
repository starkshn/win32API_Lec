#pragma once
#include "CObject.h"

class UI : public CObject
{
private:
	CLONE(UI);

	vector<UI*> _vecUI;
	UI*			p_parentUI;

	Vector2		_finalPos; // ���� ��ġ

	bool		_cameraAffected; // UI�� ī�޶� ������ �޴��� ����
	bool		_onMouseCheck; // UI���� ���콺�� �ִ��� ����
	bool		_lbtnDown; // Lbtn Down����

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

