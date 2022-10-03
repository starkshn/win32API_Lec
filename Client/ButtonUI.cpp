#include "pch.h"
#include "ButtonUI.h"
// #include "ToolScene.h"
// #include "CScene.h"
// #include "CObject.h"

ButtonUI::ButtonUI() 
	: 
	UI(false),
	_param1(0),
	_param2(0),
	pf_sceneFunc(nullptr),
	p_sceneInstance(nullptr),
	pf_objectFunc(nullptr),
	p_objectInstance(nullptr)
{

}

ButtonUI::~ButtonUI()
{

}

void ButtonUI::update()
{
	
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

