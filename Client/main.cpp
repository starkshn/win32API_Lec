// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include <iostream>
using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;                                // 메인 윈도우
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// TileCountProc
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// SAL
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Memory Leak 찾기
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(268);
    //_CrtSetBreakAlloc(280);
    //_CrtSetBreakAlloc(279);
    //_CrtSetBreakAlloc(278);

    // {281} {280} {279} {278} {277} {218}
    // _crtBreakAlloc : 나중에 문제 생겼을 때 문제 해당지점을 잡아주는 기능

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    // 윈도우 생성 -> 인터페이스
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInstance()->init(g_hWnd, POINT{ 1280, 768 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"EROOR", MB_OK);

        return FALSE;
    }

    // 단축키 등록
    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //SetTimer(g_hWnd, 0, 0, nullptr);
    
    // GetMessage
    // 메세지 큐에서 확인 될때까지 대기
    // msg.message == WM_QUIT 인경우 false를 반환 -> 프로그램 종료

    // PeekMessage
    // 메세지의 유무와 관계없이 반환
    // 메세지 큐에서 메세지를 확인한 경우 true, 메세지 큐에서 메세지가 없을 경우 false를 반환
    
    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // hAccelTable : 단축키 정보 확인한다.

            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // Game코드 수행
            // 디자인 패턴(설계유형)
            // Single Tone
            CCore::GetInstance()->progress();
        }
       
    }
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

POINT g_gameObjectPos = { 500, 300 }; // 중심좌표라고 가정
POINT g_gameObjectScale = { 100, 100 }; // 크기

POINT g_posLeftTop; // 좌상단 좌표
POINT g_posRightBottom; // 좌상단 좌표

#include <vector>
using std::vector;

struct ObjInfo
{
    POINT _objectPosInfo;
    POINT _objectScaleInfo;
};

vector<ObjInfo> g_objVector;

bool g_lButtonDown = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_MENU_TILE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT: // 무효화 영역(invalidate)  발생한 경우
        {
            PAINTSTRUCT ps;

            // Divice Context 만들어서 => ID반환.
            HDC hdc = BeginPaint(hWnd, &ps); // Device context (그리기)

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // DC의 목적지는 hWn
            // DC의 기본펜 Black
            // DC의 기본 브러쉬 (White)

            // 직접 펜과 브러쉬를 만들어서 DC에 적용
            /*HPEN hRedPen = CreatePen(PS_DASH, 2, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));*/

            // 기존 펜과 브러쉬의 ID값을 받아 둠.
            /*HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);*/

            // hdc
            // 윈도우 핸들
            // 윈도우 좌표

            // 변경된 펜과 브러쉬로 사각형을 그림.
            //Rectangle(hdc, 50, 50, 200, 200);


           /* Rectangle
            (
                hdc,
                _gameObjectPos.x - _gameObjectScale.x / 2,
                _gameObjectPos.y - _gameObjectScale.y / 2,
                _gameObjectPos.x + _gameObjectScale.x / 2,
                _gameObjectPos.y + _gameObjectScale.y / 2
            );*/

            // DE의 펜과 브러쉬를 원래 상태로 되돌린다.
            //SelectObject(hdc, hDefaultPen);
            //SelectObject(hdc, hDefaultBrush);

            //// 따 쓴 펜, 브러쉬 Curnel Object 삭제해달라고 요청한다.
            //DeleteObject(hRedPen);
            //DeleteObject(hBlueBrush);

            //Rectangle(hdc, 1180, 0, 1280, 100);
            //// 그리기 종료
            //EndPaint(hWnd, &ps);
        }
            break;
        case WM_KEYDOWN:
        {
            
        }
            break;
        case WM_LBUTTONDOWN:
        {

        }
            break;
        case WM_MOUSEMOVE:
        {
           
        }
            break;
        case WM_LBUTTONUP:
        {

        }
            break;
        case WM_TIMER:
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

