#include "pch.h"
#include "CSceneManager.h"
#include "StartScene.h"
#include "ToolScene.h"

CSceneManager::CSceneManager() : p_scenes{}, p_curScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(SCENE_TYPE::END); ++i)
	{	
		if (p_scenes[i] != nullptr)
		{
			delete p_scenes[i];
		}
	}
}

void CSceneManager::init()
{
	// Scene 생성
	p_scenes[static_cast<unsigned int>(SCENE_TYPE::START)] = new StartScene;
	p_scenes[static_cast<unsigned int>(SCENE_TYPE::START)]->SetName(L"StartScene");
	p_scenes[static_cast<unsigned int>(SCENE_TYPE::TOOL)] = new ToolScene;
	p_scenes[static_cast<unsigned int>(SCENE_TYPE::TOOL)]->SetName(L"ToolScene");
	
	//_scenes[static_cast<unsigned int>(SCENE_TYPE::STAGE_01)] = new Stage01Scene;
	//_scenes[static_cast<unsigned int>(SCENE_TYPE::STAGE_02)] = new Stage02Scene;

	// 현재 씬 지정
	p_curScene = p_scenes[static_cast<unsigned int>(SCENE_TYPE::TOOL)];
	p_curScene->Enter();
}

void CSceneManager::update()
{
	p_curScene->update();
	p_curScene->finalUpdate();
}

void CSceneManager::render(HDC sceneDC)
{
	p_curScene->render(sceneDC);
}

void CSceneManager::ChangeRealScene(SCENE_TYPE sceneType)
{
	p_curScene->Exit();

	p_curScene = p_scenes[static_cast<UINT>(sceneType)];

	p_curScene->Enter();
}
