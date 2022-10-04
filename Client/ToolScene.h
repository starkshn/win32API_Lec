#pragma once
#include "CScene.h"

class UI;

class ToolScene : public CScene
{
private :
	UI*			p_ui;

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

	void LoadTileData();

public:

	
};



