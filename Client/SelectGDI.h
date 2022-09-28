#pragma once
class SelectGDI
{
private:
	HDC		h_dc;
	HPEN	h_defaultPen;
	HBRUSH	h_defaultBrush;

public:
	SelectGDI(HDC dc, HBRUSH_TYPE type);
	SelectGDI(HDC dc, HPEN_TYPE type);
	~SelectGDI();
};

