#include "pch.h"
#include "UI.h"
#include "CameraManager.h"
#include "CKeyManager.h"
#include "SelectGDI.h"

UI::UI(bool cameraAffected)
	:
	_vecChildUI{},
	p_parentUI(nullptr),
	_finalPos{},
	_cameraAffected(cameraAffected),
	_onMouseCheck(false)
{

}

UI::UI(const UI& origin) 
	:
	p_parentUI(nullptr),
	_cameraAffected(origin._cameraAffected),
	_onMouseCheck(false),
	_lbtnDown(false)
{
	for (size_t i = 0; i < origin._vecChildUI.size(); ++i)
	{
		AddChild(origin._vecChildUI[i]->Clone());
	}
}

UI::~UI()
{
	SafeDeleteVector(_vecChildUI);
}

void UI::update()
{
	// child update
	updateChild();
}

void UI::finalUpdate()
{
	// �θ��� finalUpdateȣ�� �ؾ��Ѵ�.
	// UI�� �ִϸ��̼� ���� ���� �ֱ� ������
	CObject::finalUpdate();

	// UI�� ������ǥ�� ���Ѵ�.
	_finalPos = GetPos(); // �θ� ��ǥ�� finalPos�� �ν�

	if (GetParentUI())
	{
		Vector2 parentPos = GetParentUI()->GetFinalPos();
		_finalPos += parentPos;
	}

	// UI Mouseüũ
	OnMouseCheck();

	finalUpdateChild();
}

void UI::OnMouseCheck()
{
	Vector2 mousePos = MOUSE_POS;
	Vector2 uiScale = GetScale();

	if (_cameraAffected)
	{
		CameraManager::GetInstance()->GetRealPos(mousePos);
	}

	if (_finalPos._x <= mousePos._x && mousePos._x <= _finalPos._x + uiScale._x &&
		_finalPos._y <= mousePos._y && mousePos._y <= _finalPos._y + uiScale._y)
	{
		_onMouseCheck = true;
	}
	else
	{
		_onMouseCheck = false;
	}
}

void UI::render(HDC dc)
{
	Vector2 pos = GetFinalPos();
	Vector2 scale = GetScale();

	if (_cameraAffected)
	{
		pos = CameraManager::GetInstance()->GetRenderPos(pos);
	}

	if (_lbtnDown)
	{
		SelectGDI select(dc, HPEN_TYPE::GREEN);
		Rectangle
		(
			dc,
			int(pos._x),
			int(pos._y),
			int(pos._x + scale._x),
			int(pos._y + scale._y)
		);
	}
	else
	{
		Rectangle
		(
			dc,
			int(pos._x),
			int(pos._y),
			int(pos._x + scale._x),
			int(pos._y + scale._y)
		);
	}

	// child render
	renderChild(dc);
}

void UI::updateChild()
{
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->update();
	}
}

void UI::finalUpdateChild()
{
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->finalUpdate();
	}
}

void UI::renderChild(HDC dc)
{
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->render(dc);
	}
}



void UI::MouseOn()
{

}

void UI::MouseLbtnDown()
{

}

void UI::MouseLbtnUp()
{
	// �ۿ��� ������ �ȿ��� ���� ���� �ν��� �ȴ�.

}

void UI::MouseLbtnClick()
{

}



