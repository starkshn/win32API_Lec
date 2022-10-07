#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "PathManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "ColliderManager.h"
#include "EventManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SelectGDI.h"
#include "resource.h"

CCore::CCore()
	:
	h_wnd(0),
	_resolution{},
	h_dc(0),
	h_brushes{},
	h_pens{}
{
	CreateHBRUSH();
	CreateHPEN();
}

CCore::~CCore()
{
	ReleaseDC(h_wnd, h_dc);

	//DeleteDC(h_memDC);
	//DeleteObject(h_bitmap);

	for (UINT i = 0; i < static_cast<UINT>(HPEN_TYPE::END); ++i)
	{
		DeleteObject(h_pens[i]);
	}

	DestroyMenu(h_menu);
}

int CCore::init(HWND hWnd, POINT resolution)
{
	h_wnd = hWnd;
	_resolution = resolution;

	// 해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vector2(static_cast<float>(_resolution.x), static_cast<float>(_resolution.y)), false);

	// 메뉴바 생성
	h_menu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	h_dc = GetDC(h_wnd);

	// =========================================================
	//  
	// 이중 버퍼링 만드는 방법 1, 2

	// 1. 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	// h_bitmap = CreateCompatibleBitmap(h_dc, _resolution.x, _resolution.y);
	// h_memDC = CreateCompatibleDC(h_dc);
	   
	// HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(h_memDC, h_bitmap));
	// DeleteObject(hPrevBit);


	// 2. 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	_bufferTexture = ResourceManager::GetInstance()->CreateTexture(L"BackBuffer", (UINT)_resolution.x, (UINT)_resolution.y);

	// =========================================================


	// Manager 초기화
	PathManager::GetInstance()->init();
	CTimeManager::GetInstance()->init();
	CKeyManager::GetInstance()->init();
	CameraManager::GetInstance()->init();
	CSceneManager::GetInstance()->init();

	return S_OK;
}

void CCore::progress()
{
	// ===============
	// Managers update
	// ===============
	CTimeManager::GetInstance()->update(); // DT계산
	CKeyManager::GetInstance()->update(); // Key상태값 체크
	CameraManager::GetInstance()->update();

	// ============
	// Scene Update
	// ============
	CSceneManager::GetInstance()->update();

	// ===============
	// Collider Update
	// ===============
	ColliderManager::GetInstance()->update(); // 충돌체크

	// ================
	// UIManager update
	// ================
	UIManager::GetInstance()->update();

	// =============
	// Randering...
	// =============
	
	// 화면 Clear
	Clear();

	CSceneManager::GetInstance()->render(_bufferTexture->GetDC()); // 씬에서 update한 부분 그리기

	CameraManager::GetInstance()->render(_bufferTexture->GetDC());

	BitBlt(h_dc, 0, 0, _resolution.x, _resolution.y, _bufferTexture->GetDC(), 0, 0, SRCCOPY);

	// ===============
	// 이벤트 지연 처리
	// ===============
	EventManager::GetInstance()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(_bufferTexture->GetDC(), HBRUSH_TYPE::BLACK);
	Rectangle(_bufferTexture->GetDC(), -1, -1, _resolution.x + 1, _resolution.y + 1); // 화면 clear
}

void CCore::CreateHBRUSH()
{
	// hollow brush
	h_brushes[static_cast<UINT>(HBRUSH_TYPE::HOLLOW)] = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));

	h_brushes[static_cast<UINT>(HBRUSH_TYPE::BLACK)] = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

}

void CCore::CreateHPEN()
{
	// red, blue, green
	h_pens[static_cast<UINT>(HPEN_TYPE::RED)] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	h_pens[static_cast<UINT>(HPEN_TYPE::GREEN)] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	h_pens[static_cast<UINT>(HPEN_TYPE::BLUE)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	// 메뉴바 부착
	SetMenu(h_wnd, h_menu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::ReleaseMenu()
{
	// 메뉴바 해제
	SetMenu(h_wnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vector2 resolution, bool menu)
{
	RECT rt = { 0, 0, resolution._x, resolution._y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, menu);
	SetWindowPos(h_wnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // window의 윈도우 위치와 크기를 변경해주는 함수
}
