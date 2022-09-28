#pragma once
#include "CScene.h"

class ToolScene : public CScene
{
private :

public :
	ToolScene();
	virtual ~ToolScene() override;

public:
	virtual void update() override;
	virtual void render(HDC dc) override;
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();
	void ToolSceneService(TOOL_SCENE_SERVICE srv);
	
public:

	
};



