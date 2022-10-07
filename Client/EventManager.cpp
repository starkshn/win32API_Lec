#include "pch.h"
#include "EventManager.h"
#include "CObject.h"
#include "CSceneManager.h"
#include "CScene.h"

#include "UIManager.h"

#include "AI.h"
#include "State.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::update()
{
	// ================================================
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
	// ================================================
	for (size_t i = 0; i < _vecDead.size(); ++i)
	{
		delete _vecDead[i];
	}

	_vecDead.clear();

	// =============
	// Event 처리
	// =============
	for (size_t i = 0; i < _vecEvents.size(); ++i)
	{
		ExcuteEvent(_vecEvents[i]); // 처리한 이벤트 없애 주어야한다!!!
	}

	_vecEvents.clear(); // 꼭 처리를 해주어야 한다!!!
}

void EventManager::ExcuteEvent(const Event& event)
{
	switch (event._eventType)
	{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			// lParam : Object Ptr
			// wParam : Object Type

			CObject* newObjPtr = (CObject*)event._lParam;
			GROUP_TYPE newObjGroupType = (GROUP_TYPE)event._rParam;

			CSceneManager::GetInstance()->GetCurScene()->AddObject(newObjPtr, newObjGroupType);

		}
			break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			// Object를 Dead상태로 변경
			// 삭제 예정 오브젝트들을 모아둔다.
			CObject* deadObjPtr = (CObject*)event._lParam;

			if (!deadObjPtr->IsDead())
			{
				deadObjPtr->SetDead();
				_vecDead.push_back(deadObjPtr);
			}
		}
			break;
		case EVENT_TYPE::SCENE_CHANGE:
		{
			// _objectPtr : nextScene
			CSceneManager::GetInstance()->ChangeRealScene((SCENE_TYPE)event._lParam);

			// 포커스  UI 해제 (이전 Scene의 FocusUI를 들고 있기 때문에)
			UIManager::GetInstance()->SetFocusUI(nullptr);
		}
			break;
		case EVENT_TYPE::CHANGE_AI_STATE:
		{
			// lParam : AI Ptr
			// rParam : Next State Type
			AI* ai = (AI*)(event._lParam);
			MONSTER_STATE nextState = (MONSTER_STATE)(event._rParam);

			ai->ChangeState(nextState);
		}
			break;

		
	}
}