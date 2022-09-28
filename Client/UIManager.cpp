#include "pch.h"
#include "UIManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CScene.h"
#include "UI.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::update()
{
	CScene* curScene = CSceneManager::GetInstance()->GetCurScene();
	// 여기에는 모든 부모 UI가 들어있다.
	const vector<CObject*> vecUI = curScene->GetGroupObjects(GROUP_TYPE::UI);

	bool tapLbtn = KEY_TAP(KEY::LBTN);
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		UI* ui = dynamic_cast<UI*>(vecUI[i]);

		// 부모 포함, 자식 UI들 중 실제 타겟팅된 UI를 가져온다.
		ui = GetTargetUI(ui);

		if (nullptr != ui)
		{
			// UI위에있다고 얼려준다.
			ui->MouseOn();

			// 경우는 두가지로 나뉨.
			if (tapLbtn)
			{
				ui->MouseLbtnDown();
				ui->_lbtnDown = true;
			}
			else if (awayLbtn)
			{
				ui->MouseLbtnUp();

				if (ui->_lbtnDown)
				{
					// 마우스 올라가있는 상태에서 때진것이라면은 클릭이다.
					ui->MouseLbtnClick();
				}

				// 왼쪽버튼 때면, 눌렀던 체크를 다시 해제한다.
				ui->_lbtnDown = false;
			}
		}
	}
}

// 부모 UI 내에서 실제로 타겟팅된 UI를 찾아서 반환한다.
UI* UIManager::GetTargetUI(UI* parentUI)
{
	bool awayLbtn = KEY_AWAY(KEY::LBTN);
	
	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	UI* targetUI = nullptr;

	static list<UI*> queue; 
	static vector<UI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(parentUI);

	while (!queue.empty())
	{
		// queue 데이터 하나 꺼낸다.
		UI* ui = queue.front();
		queue.pop_front();

		// queue에서 꺼내온 UI가 targetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (ui->IsMouseOn())
		{
			if (nullptr != targetUI)
			{
				vecNoneTargetUI.push_back(targetUI);
			}

			targetUI = ui;
		}
		else
		{
			vecNoneTargetUI.push_back(ui);
		}

		const vector<UI*>& vecChild = ui->GetChild();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (awayLbtn)
	{
		for (size_t i = 0; i < vecNoneTargetUI.size(); ++i)
		{
			// 왼쪽버튼 때면, 눌렸던 체크를 다시 해제한다.
			vecNoneTargetUI[i]->_lbtnDown = false;
		}
	}
	
	return targetUI;
}
