#pragma once
#include "UI.h"

// class CScene;
// class ToolScene;
// class CObject;
// ���漱���� �� ������ ������ ��¿�� ���� ��� �����Ѵ�.
#include "CScene.h"
// #include "ToolScene.h"
#include "CObject.h"

#include "ButtonInfo.h"

class Texture;
class Tile;
class ToolScene;

typedef void(*BTN_TYPE) (DWORD_PTR, DWORD_PTR);

// ����Լ� ������
typedef void(CScene::*SCENE_MEMFUNC) (void);
// typedef void(ToolScene::*TOOL_SCENE_MEMFUNC) (void);
typedef void(CObject::*OBJECT_MEMFUNC) (void);


class ButtonUI : public UI
{
public:
	CLONE(ButtonUI);

private:
	BTN_TYPE			pf_btnFunc;
	DWORD_PTR			_param1;
	DWORD_PTR			_param2;

	// ȣ���� ��ü��	�ʿ�
	SCENE_MEMFUNC		pf_sceneFunc;
	CScene*				p_sceneInstance;

	// TOOL_SCENE_MEMFUNC	pf_toolSceneFunc;
	// ToolScene*			p_toolSceneInstance;

	OBJECT_MEMFUNC	pf_objectFunc;
	CObject*		p_objectInstance;

	// Component
	Texture*		p_buttonTexture;
	int				_buttonImageIdx;
	int				_buttonTypeIdx;

	// idx Info
	ButtonInfo			_tileIdxInfo;
	ToolScene*			p_toolScene;
	vector<ButtonUI*>	v_toolSceneTileButtons;

	// tile �̹����� �ε����� ������� ����
	static UINT		sg_tileImageIndex;
	UINT			_tileImageIndex = 0;

public:
	ButtonUI(int buttonType);
	virtual ~ButtonUI() override;

public:
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClick() override;

public:
	void AddButtonImageIdx() { ++_buttonImageIdx; }

public:
	void SetButtonTexture(Texture* buttonTexture)
	{
		p_buttonTexture = buttonTexture;
	}

public:
	void SetClickedCallBack(BTN_TYPE func, DWORD_PTR param1, DWORD_PTR param2)
	{
		pf_btnFunc = func;
		_param1 = param1;
		_param2 = param2;
	}

	void SetClickedCallBack(CScene* sceneInstance, SCENE_MEMFUNC func);
	// void SetClickedCallBack(ToolScene* toolSceneInstance, TOOL_SCENE_MEMFUNC func);

	void SetClickedCallBack(CObject* objectInstance, OBJECT_MEMFUNC func);

public:
	void ClickedTileButton()
	{
		// ButtonTile Ŭ���� TODO
	}

	UINT GetTileImageIdx() { return _tileImageIndex; }

};

