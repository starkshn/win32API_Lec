#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"

SelectGDI::SelectGDI(HDC dc, HBRUSH_TYPE type)
	:
	h_dc(dc),
	h_defaultPen(nullptr),
	h_defaultBrush(nullptr)
{
	HBRUSH brush = CCore::GetInstance()->GetHBRUSH(type);
	h_defaultBrush = static_cast<HBRUSH>(SelectObject(dc, brush));  
}

SelectGDI::SelectGDI(HDC dc, HPEN_TYPE type)
	: 
	h_dc(dc),
	h_defaultPen(nullptr), 
	h_defaultBrush(nullptr)
{
	HPEN pen = CCore::GetInstance()->GetHPEN(type);
	h_defaultPen = static_cast<HPEN>(SelectObject(dc, pen));
}

SelectGDI::~SelectGDI()
{
	SelectObject(h_dc, h_defaultPen);
	SelectObject(h_dc, h_defaultBrush);
}