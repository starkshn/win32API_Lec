#pragma once
#include "CScene.h"

class UI;
class ButtonUI;

class ToolScene : public CScene
{
private:
	UI*					p_ui;
	vector<CObject*>	v_tileButtons;

	// Right/Left 클릭시 변경되는 PanelUI의 페이지수 표시
	UINT _prevPanelTileMaxIndex;
	UINT _curPanelTileMaxIndex;

public :
	ToolScene();
	virtual ~ToolScene() override;

public:
	virtual void update() override;
	virtual void render(HDC dc) override;
	virtual void Enter();
	virtual void Exit();

public:
	void SaveTileData();
	void SaveTile(const wstring& _filePath);
	void SetTileIdx();

public:
	void LoadTileData();

public:
	CObject* GetTileButtonVec(int idx) { return v_tileButtons[idx]; }
	UINT GetPrevPageIndex() { return _prevPanelTileMaxIndex;  };
	UINT GetCurPageIndex() { return _curPanelTileMaxIndex; };

public:
	void ClickRightButton();
	void ClickLeftButton();
};



