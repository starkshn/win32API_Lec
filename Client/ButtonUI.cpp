#include "pch.h"
#include "ButtonUI.h"
// #include "ToolScene.h"
// #include "CScene.h"
// #include "CObject.h"
#include "Texture.h"
#include "ResourceManager.h"

ButtonUI::ButtonUI(int buttonTypeIdx) 
	: 
	UI(false),
	_param1(0),
	_param2(0),
	pf_sceneFunc(nullptr),
	p_sceneInstance(nullptr),
	pf_objectFunc(nullptr),
	p_objectInstance(nullptr),
	p_buttonTexture(nullptr)
{
	p_buttonTexture = ResourceManager::GetInstance()->LoadTexture(L"Buttons", L"Textures\\UI\\Buttons.bmp");

	SetObjectName(L"UI_Button");

	SetScale(Vector2(BUTTON_SIZE, BUTTON_SIZE));

	_buttonTypeIdx = buttonTypeIdx;
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

	// ��ư ������ ���´�. 72 x 72
	UINT maxCol = (width / BUTTON_SIZE); // 5
	// Ÿ�� �� ������ ���´�. (-1 ���־���Ѵ�. 768px�̿��� �ϴµ� 767px�̶�
	UINT maxRow = (height / BUTTON_SIZE); // 5

	// _buttonImageIdx 0���� ���� �ϋ�
	// 5 / 5 => 1, 5 % 5 => 0
	UINT curRow = static_cast<UINT>(_buttonTypeIdx / maxCol);
	UINT curCol = static_cast<UINT>(_buttonTypeIdx % maxRow);

	// ���� ���� �ִ����� �����ʰ� �ϱ� ���� ����ó��
	if (maxRow <= curRow)
		assert(nullptr);

	Vector2 finalPos = GetFinalPos();
	Vector2 scale = GetScale();

	// checkButton ȭ�鿡 ���� �κ�

	if (GetIsMouseOn())
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
		// (p_sceneInstance->*pf_sceneFunc)(); ���� ���̴�.
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

