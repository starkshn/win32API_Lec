#pragma once

class Texture;

class CCore
{
	SINGLE(CCore);

private:
	HWND		h_wnd; // 메인 윈도우 핸들
	POINT		_resolution; // 메인 윈도우  해상도
	HDC			h_dc; // 메인 윈도우에 Draw할 DC

	// HBITMAP		h_bitmap;
	// HDC			h_memDC;
	// 이렇게 가지는게 아니라 텍스쳐로 가지고 있자.
	Texture*	_bufferTexture; // 백버퍼 텍스쳐


	// 자주 사용하는 GDI Object (커널오브젝트)
	HBRUSH	h_brushes[static_cast<UINT>(HBRUSH_TYPE::END)];
	HPEN	h_pens[static_cast<UINT>(HPEN_TYPE::END)];

public:
	int		init(HWND hWnd, POINT resolution);
	void	progress();

private:
	void CreateHBRUSH();
	void CreateHPEN();

public :
	HWND	GetMainHwnd() { return h_wnd; }
	POINT	GetResolution() { return _resolution; }
	HDC		GetMainDC() { return h_dc; }

	HBRUSH	GetHBRUSH(HBRUSH_TYPE type) { return h_brushes[static_cast<UINT>(type)]; }
	HPEN	GetHPEN(HPEN_TYPE type) { return h_pens[static_cast<UINT>(type)]; }
};