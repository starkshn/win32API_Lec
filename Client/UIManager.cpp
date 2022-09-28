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
	// ���⿡�� ��� �θ� UI�� ����ִ�.
	const vector<CObject*> vecUI = curScene->GetGroupObjects(GROUP_TYPE::UI);

	bool tapLbtn = KEY_TAP(KEY::LBTN);
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		UI* ui = dynamic_cast<UI*>(vecUI[i]);

		// �θ� ����, �ڽ� UI�� �� ���� Ÿ���õ� UI�� �����´�.
		ui = GetTargetUI(ui);

		if (nullptr != ui)
		{
			// UI�����ִٰ� ����ش�.
			ui->MouseOn();

			// ���� �ΰ����� ����.
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
					// ���콺 �ö��ִ� ���¿��� �������̶���� Ŭ���̴�.
					ui->MouseLbtnClick();
				}

				// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
				ui->_lbtnDown = false;
			}
		}
	}
}

// �θ� UI ������ ������ Ÿ���õ� UI�� ã�Ƽ� ��ȯ�Ѵ�.
UI* UIManager::GetTargetUI(UI* parentUI)
{
	bool awayLbtn = KEY_AWAY(KEY::LBTN);
	
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	UI* targetUI = nullptr;

	static list<UI*> queue; 
	static vector<UI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(parentUI);

	while (!queue.empty())
	{
		// queue ������ �ϳ� ������.
		UI* ui = queue.front();
		queue.pop_front();

		// queue���� ������ UI�� targetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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
			// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
			vecNoneTargetUI[i]->_lbtnDown = false;
		}
	}
	
	return targetUI;
}
