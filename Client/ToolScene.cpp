#include "pch.h"
#include "ToolScene.h"
#include "CKeyManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "CCore.h"
#include "Tile.h"
#include "Texture.h"
#include "Resource.h"
#include "CSceneManager.h"
#include "CScene.h"

// #include "UI.h"
#include "PanelUI.h"
#include "ButtonUI.h"


ToolScene::ToolScene()
{

}

ToolScene::~ToolScene()
{

}

void ToolScene::update()
{
	CScene::update();

	// TOOL_SCENE_SERVICE service = TOOL_SCENE_SERVICE::CHANGE_IMAGE_IDX;
	// ToolSceneService(service);

	SetTileIdx();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void ToolScene::render(HDC dc)
{
	CScene::render(dc);


};

void ToolScene::Enter()
{
	// 타일 생성
	CreateTile(5, 5);

	// Camera Look 지정
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);


#pragma region "UI (4) UI 생성 테스트 작업부분"

	// UI 하나 테스트 구현 (우측상단에 배치)
	UI* parentUI = new UI(false);
	parentUI->SetObjectName(L"parentUI");
	parentUI->SetScale(Vector2(500.f, 300.f));
	parentUI->SetPos(Vector2(resolution._x - parentUI->GetScale()._x, 0.f));

	// 테스트용 자식 UI
	UI* childUI = new UI(false);
	childUI->SetObjectName(L"childUI");
	childUI->SetScale(Vector2(100.f, 40.f));
	childUI->SetPos(Vector2(0.f, 0.f));

	// parent UI 자식 추가 (테스트 용)
	parentUI->AddChild(childUI);

	// infoUI
	UI* infoParentUI = new UI(false);
	infoParentUI->SetObjectName(L"infoParentUI");
	infoParentUI->SetScale(Vector2(800.f, 200.f));
	infoParentUI->SetPos(Vector2((infoParentUI->GetScale()._x / 800.f) - 1, 0.f));

	// infoUI 자식 : timeInfoUI, bmCountInfoUI, characterInfoUI
	// bulletInfo 자식 : bulletUI, bombUI
	// characterInfo 자식 : scoreUI, slugHpUI, lifeCountUI

	// time UI
	UI* timeInfoUI = new UI(false);
	timeInfoUI->SetObjectName(L"timeInfoUI");
	timeInfoUI->SetScale(Vector2(150.f, 150.f));
	timeInfoUI->SetPos(SetUICenterPos(infoParentUI->GetScale(), timeInfoUI->GetScale()));
	infoParentUI->AddChild(timeInfoUI);

	// bmCountInfoUI
	UI* bmCountInfoUI = new UI(false);
	bmCountInfoUI->SetObjectName(L"bmCountInfoUI");
	bmCountInfoUI->SetScale(Vector2(200.f, 170.f));
	bmCountInfoUI->SetPos(SetUICenterPos(infoParentUI->GetScale(), bmCountInfoUI->GetScale()) - Vector2(250.f, 0.f));
	infoParentUI->AddChild(bmCountInfoUI);

	// characterInfoUI
	UI* characterInfoUI = new UI(false);
	characterInfoUI->SetObjectName(L"characterInfoUI");
	characterInfoUI->SetScale(Vector2(250.f, 180.f));
	characterInfoUI->SetPos(SetUICenterPos(infoParentUI->GetScale(), characterInfoUI->GetScale()) + Vector2(250.f, 0.f));
	infoParentUI->AddChild(characterInfoUI);

	// AddObject : 해주어야 렌더링 됨.
	AddObject(parentUI, GROUP_TYPE::UI);
	AddObject(infoParentUI, GROUP_TYPE::UI);
#pragma endregion


#pragma region "UI (5) 강의 UI 생성부분"
	// PanelUI
	UI* panelUI = new PanelUI();
	panelUI->SetObjectName(L"panelUI");
	panelUI->SetScale(Vector2(400.f, 400.f));
	panelUI->SetPos(Vector2(resolution._x - panelUI->GetScale()._x, resolution._y - panelUI->GetScale()._y));

	// ButtonUI
	UI* buttonUI = new ButtonUI();
	buttonUI->SetObjectName(L"buttonUI");
	buttonUI->SetScale(Vector2(300.f, 300.f));
	buttonUI->SetPos(Vector2(0.f, 0.f));

	panelUI->AddChild(buttonUI);

	AddObject(panelUI, GROUP_TYPE::UI);



	// 복사생성자 구현후 CLONE 테스트
	UI* clonePanel = panelUI->Clone();
	// 위치가 완전히 똑같아지는 것을 피하기 위해 위치조정
	clonePanel->SetPos(panelUI->GetPos() + Vector2(-300.f, 0.f));
	
	AddObject(clonePanel, GROUP_TYPE::UI);

#pragma endregion


	

};

void ToolScene::Exit()
{
	
}

void ToolScene::SetTileIdx()
{
	// 마우스 클릭이 있을 때만 동작하게 하는 부분.
	if (KEY_TAP(KEY::LBTN))
	{
		// 마우스 실제 좌표를 구하는 작업.
		Vector2 mousePos = MOUSE_POS;
		mousePos = CameraManager::GetInstance()->GetRealPos(mousePos);

		int tileXCount = static_cast<int>(GetTileX());
		int tileYCount = static_cast<int>(GetTileY());

		int col = static_cast<int>(mousePos._x / TILE_SIZE);
		int row = static_cast<int>(mousePos._y / TILE_SIZE);
		
		UINT tileIdx = row * tileXCount + col;
		
		if (mousePos._x < 0.f || tileXCount <= col || mousePos._y < 0.f || tileYCount <= row)
			return;
		
		const vector<CObject*>& vecTile = GetGroupObjects(GROUP_TYPE::TILE);
		dynamic_cast<Tile*>(vecTile[tileIdx])->AddImageIdx();
	}
}




void ToolScene::ToolSceneService(TOOL_SCENE_SERVICE srv)
{
	switch (srv)
	{
		case TOOL_SCENE_SERVICE::CHANGE_IMAGE_IDX:
		{
			Vector2 mousePos = MOUSE_POS;


		}
			break;
	}
};


// =======================
// Tile Count window Proc
// =======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// IDC_EDIT1 : x ID
			// IDC_EDIT2 : y ID
			UINT xCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT yCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* curScene = CSceneManager::GetInstance()->GetCurScene();

			// ToolScene확인 
			// 실패하면 nullptr
			ToolScene* toolScene = dynamic_cast<ToolScene*>(curScene);
			assert(toolScene);
			
			toolScene->DeleteGroupObjects(GROUP_TYPE::TILE);
			toolScene->CreateTile(xCount, yCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



