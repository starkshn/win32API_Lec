#pragma once
#include "CObject.h"

class UI : public CObject
{
public:
	// ��ü ���� ����
	// virtual UI* Clone() = delete;
	virtual UI* Clone() = 0;

private:
	vector<UI*> _vecChildUI; // ���� ���� ���� �ؾ���.
	UI*			p_parentUI;

	Vector2		_finalPos; // ���� ��ġ

	bool		_cameraAffected; // UI�� ī�޶� ������ �޴��� ����
	bool		_onMouseCheck; // UI���� ���콺�� �ִ��� ����
	bool		_lbtnDown; // Lbtn Down����

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

	bool				GetLbtnDown() { return _lbtnDown; }
	bool				GetIsMouseOn() { return _onMouseCheck; }

	UI* GetFindChild(UI* parentUI, const wstring& childUI)
	{
		for (UINT i = 0; i < parentUI->GetChild().size(); ++i)
		{
			if (parentUI->GetChild()[i]->GetObjectName() == childUI)
			{
				if (parentUI->GetChild()[i] == nullptr)
					assert(nullptr);

				return parentUI->GetChild()[i];
			}
		}
	}

	friend class UIManager;
};

