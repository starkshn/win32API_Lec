#include "pch.h"
#include "PanelUI.h"
#include "CKeyManager.h"

PanelUI::PanelUI() : UI(false)
{

}

PanelUI::~PanelUI()
{

}

void PanelUI::update()
{

}

void PanelUI::render(HDC dc)
{
	UI::render(dc);
}

void PanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		// 나를 잡아 끌고있는 중...
		Vector2 diff = MOUSE_POS - _lbtnDownMousePos;

		Vector2 curPos = GetPos();
		curPos += diff;
		SetPos(curPos);

		_lbtnDownMousePos = MOUSE_POS;
	}
}

void PanelUI::MouseLbtnDown()
{
	_lbtnDownMousePos = MOUSE_POS;
}

void PanelUI::MouseLbtnUp()
{

}

