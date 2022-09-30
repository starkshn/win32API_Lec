#include "pch.h"
#include "ButtonUI.h"

ButtonUI::ButtonUI() : UI(false)
{

}

ButtonUI::~ButtonUI()
{

}

void ButtonUI::update()
{
	
}

void ButtonUI::MouseOn()
{

}

void ButtonUI::MouseLbtnDown()
{

}

void ButtonUI::MouseLbtnUp()
{

}

void ButtonUI::MouseLbtnClick()
{
	if (nullptr != f_btnFunc)
	{
		f_btnFunc(_param1, _param2);
	}
}

