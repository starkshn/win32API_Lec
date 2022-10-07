#include "pch.h"
#include "Func.h"
#include "EventManager.h"

void CreateObjectEvent(CObject* objectPtr, GROUP_TYPE groupType)
{
	Event evt = {};
	evt._eventType = EVENT_TYPE::CREATE_OBJECT;
	evt._objectPtr = (DWORD_PTR)objectPtr;
	evt._groupType = (DWORD_PTR)groupType;
	// DWORD_PTR이지만 안에 데이터의 정체를 알고있다.

	EventManager::GetInstance()->AddEvent(evt);
}

void DeleteObjectEvent(CObject* objectPtr)
{
	Event evt = {};
	evt._eventType = EVENT_TYPE::DELETE_OBJECT;
	evt._objectPtr = (DWORD_PTR)objectPtr;

	EventManager::GetInstance()->AddEvent(evt);
}

void ChangeScene(SCENE_TYPE changeSceneType)
{
	// 이번프레임에서는 이벤트 등록을 하고 다음 프레임에 씬을 변경을 할 것이다.
	Event evt = {};
	evt._eventType = EVENT_TYPE::SCENE_CHANGE;
	evt._objectPtr = (DWORD_PTR)changeSceneType;

 	EventManager::GetInstance()->AddEvent(evt);
}