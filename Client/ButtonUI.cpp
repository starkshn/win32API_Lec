#include "pch.h"
#include "ButtonUI.h"
// #include "ToolScene.h"
// #include "CScene.h"
// #include "CObject.h"
#include "Texture.h"
#include "ResourceManager.h"

#include "Tile.h"

#include "CSceneManager.h"
#include "CScene.h"
#include "ToolScene.h"

UINT ButtonUI::sg_tileImageIndex = 0;

ButtonUI::ButtonUI(int buttonTypeIdx) 
	: 
	UI(false),
	_param1(0),
	_param2(0),
	pf_sceneFunc(nullptr),
	p_sceneInstance(nullptr),
	pf_objectFunc(nullptr),
	p_objectInstance(nullptr),
	p_buttonTexture(nullptr),
	v_toolSceneTileButtons{}
{
	_buttonTypeIdx = buttonTypeIdx;
	p_toolScene = (ToolScene*)CSceneManager::GetInstance()->GetCurScene();

	if (_buttonTypeIdx == 1)
	{
		p_buttonTexture = ResourceManager::GetInstance()->LoadTexture(L"TileTexture", L"Textures\\tiles.bmp");

		_tileImageIndex = sg_tileImageIndex++;

		SetObjectName(L"UI_TileButton");
		SetScale(Vector2(TILE_SIZE, TILE_SIZE));

		_tileIdxInfo = ButtonInfo(_tileImageIndex);
	}
	else
	{
		p_buttonTexture = ResourceManager::GetInstance()->LoadTexture(L"Buttons", L"Textures\\UI\\Buttons.bmp");

		SetObjectName(L"UI_Button");
		SetScale(Vector2(BUTTON_SIZE, BUTTON_SIZE));
	}
}

ButtonUI::~ButtonUI()
{

}

void ButtonUI::update()
{
	
}

void ButtonUI::render(HDC dc)
{
	if (nullptr == p_buttonTexture || -1 == _buttonImageIdx)
		return;

	UINT width = p_buttonTexture->GetWidth();
	UINT height = p_buttonTexture->GetHeight();

	UINT maxCol = 0;
	UINT maxRow = 0;

	UINT curRow = 0;
	UINT curCol = 0;

	// 버튼 갯수가 나온다. 72 x 72
	if (_buttonTypeIdx == 1)
	{
		maxCol = (width / TILE_SIZE); // 22
		maxRow = (height / TILE_SIZE); // 12
	}
	else
	{
		maxCol = (width / BUTTON_SIZE); // 5
		maxRow = (height / BUTTON_SIZE); // 5
	}

	// _buttonImageIdx 0부터 시작 일떄
	// 5 / 5 => 1, 5 % 5 => 0
	if (_buttonTypeIdx == 1)
	{
		curRow = static_cast<UINT>(_tileImageIndex / maxCol);
		curCol = static_cast<UINT>(_tileImageIndex % maxRow);
	}
	else
	{
		curRow = static_cast<UINT>(_buttonTypeIdx / maxCol);
		curCol = static_cast<UINT>(_buttonTypeIdx % maxRow);
	}

	// 현재 행이 최대행을 넘지않게 하기 위한 예외처리
	if (maxRow <= curRow)
		assert(nullptr);

	//UI* parentUI = GetParentUI();
	//Vector2 parentUIScale = parentUI->GetScale();
	//unsigned int tileButtonDiff = parentUIScale._x / TILE_SIZE;

	Vector2 finalPos = GetFinalPos();

	if (_buttonTypeIdx == 1 && (_tileImageIndex <= 35))
	{				
		UINT row = _tileImageIndex / 6;
		UINT col = _tileImageIndex % 7;

		if (row == 0)
		{
			(p_toolScene->GetTileButtonVec(_tileImageIndex))->SetPos(Vector2(static_cast<float>(col * TILE_SIZE), static_cast<float>(row* TILE_SIZE + 100)));
		}
		else
		{
			(p_toolScene->GetTileButtonVec(_tileImageIndex))->SetPos(Vector2(static_cast<float>(col * TILE_SIZE), static_cast<float>(row * TILE_SIZE)));
		}
		
	}

	// checkButton 화면에 띄우는 부분
	if (GetIsMouseOn())
	{
		if (_buttonTypeIdx == 1)
		{

			Rectangle(dc, GetPos()._x, GetPos()._y, 72, 72);

			/*TransparentBlt
			(
				dc,
				int(finalPos._x),
				int(finalPos._y),
				int(TILE_SIZE),
				int(TILE_SIZE),
				p_buttonTexture->GetDC(),
				curCol * TILE_SIZE,
				curRow * TILE_SIZE,
				TILE_SIZE, TILE_SIZE,
				RGB(1, 1, 1)
			);*/
		}
		else
		{
			TransparentBlt
			(
				dc,
				int(finalPos._x),
				int(finalPos._y),
				int(BUTTON_SIZE),
				int(BUTTON_SIZE),
				p_buttonTexture->GetDC(),
				curCol * BUTTON_SIZE,
				curRow * BUTTON_SIZE,
				BUTTON_SIZE, BUTTON_SIZE,
				RGB(0, 0, 0)
			);
		}
	}
	else
	{
		if (_buttonTypeIdx == 1)
		{
			TransparentBlt
			(
				dc,
				int(finalPos._x),
				int(finalPos._y),
				int(TILE_SIZE),
				int(TILE_SIZE),
				p_buttonTexture->GetDC(),
				curCol * TILE_SIZE,
				curRow * TILE_SIZE,
				TILE_SIZE, TILE_SIZE,
				RGB(255, 0, 255)
			);
		}
		else
		{
			TransparentBlt
			(
				dc,
				int(finalPos._x),
				int(finalPos._y),
				int(BUTTON_SIZE),
				int(BUTTON_SIZE),
				p_buttonTexture->GetDC(),
				curCol * BUTTON_SIZE,
				curRow * BUTTON_SIZE,
				BUTTON_SIZE, BUTTON_SIZE,
				RGB(255, 0, 255)
			);
		}
	}
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
	if (nullptr != pf_btnFunc)
	{
		pf_btnFunc(_param1, _param2);
	}

	if (nullptr != p_sceneInstance && nullptr != pf_sceneFunc )
	{
		((*p_sceneInstance).*pf_sceneFunc)();
		// (p_sceneInstance->*pf_sceneFunc)(); 같은 말이다.
	}

	// if (nullptr != p_toolSceneInstance && nullptr != // pf_toolSceneFunc)
	// {
	// 	((*p_toolSceneInstance).*pf_toolSceneFunc)();
	// }

	if (nullptr != pf_objectFunc && nullptr != p_objectInstance)
	{
		((*p_objectInstance).*pf_objectFunc)();
	}
}

void ButtonUI::SetClickedCallBack(CScene* sceneInstance, SCENE_MEMFUNC func)
{
	p_sceneInstance = sceneInstance;
	pf_sceneFunc = func;
}

// void ButtonUI::SetClickedCallBack(ToolScene* // toolSceneInstance, TOOL_SCENE_MEMFUNC func)
// {
// 	p_toolSceneInstance = dynamic_cast<ToolScene*>// (toolSceneInstance);
// 	pf_toolSceneFunc = func;
// }

void ButtonUI::SetClickedCallBack(CObject* objectInstance, OBJECT_MEMFUNC func)
{
	p_objectInstance = objectInstance;
	pf_objectFunc = func;
}

