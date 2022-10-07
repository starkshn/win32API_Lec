#pragma once

class Texture;

class CCore
{
	SINGLE(CCore);

private:
	HWND		h_wnd; // ���� ������ �ڵ�
	POINT		_resolution; // ���� ������  �ػ�
	HDC			h_dc; // ���� �����쿡 Draw�� DC

	// HBITMAP		h_bitmap;
	// HDC			h_memDC;
	// �̷��� �����°� �ƴ϶� �ؽ��ķ� ������ ����.
	Texture*	_bufferTexture; // ����� �ؽ���


	// ���� ����ϴ� GDI Object (Ŀ�ο�����Ʈ)
	HBRUSH	h_brushes[static_cast<UINT>(HBRUSH_TYPE::END)];
	HPEN	h_pens[static_cast<UINT>(HPEN_TYPE::END)];

	// �޴��� ����
	HMENU	h_menu; // ToolScene ������ ���

public:
	int		init(HWND hWnd, POINT resolution);
	void	progress();
	void	Clear();

private:
	void CreateHBRUSH();
	void CreateHPEN();

public:
	void DockMenu();
	void ReleaseMenu();
	void ChangeWindowSize(Vector2 resolution, bool menu);

public:
	HWND	GetMainHwnd() { return h_wnd; }
	POINT	GetResolution() { return _resolution; }
	HDC		GetMainDC() { return h_dc; }

	HBRUSH	GetHBRUSH(HBRUSH_TYPE type) { return h_brushes[static_cast<UINT>(type)]; }
	HPEN	GetHPEN(HPEN_TYPE type) { return h_pens[static_cast<UINT>(type)]; }

};