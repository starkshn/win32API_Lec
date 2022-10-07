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
	// ���� �����ӿ��� ����ص� Dead Object ���� �����Ѵ�.
	// ================================================
	for (size_t i = 0; i < _vecDead.size(); ++i)
	{
		delete _vecDead[i];
	}

	_vecDead.clear();

	// =============
	// Event ó��
	// =============
	for (size_t i = 0; i < _vecEvents.size(); ++i)
	{
		ExcuteEvent(_vecEvents[i]); // ó���� �̺�Ʈ ���� �־���Ѵ�!!!
	}

	_vecEvents.clear(); // �� ó���� ���־�� �Ѵ�!!!
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
			// Object�� Dead���·� ����
			// ���� ���� ������Ʈ���� ��Ƶд�.
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

			// ��Ŀ��  UI ���� (���� Scene�� FocusUI�� ��� �ֱ� ������)
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