#include "pch.h"
#include "StartScene.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CMissile.h"
#include "PathManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "ColliderManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CameraManager.h"

// AI
#include "AI.h"
#include "Idle.h"
#include "Trace.h"

// ����
#include "RigidBody.h"
#include "SelectGDI.h"

// ��
#include "Ground.h"

// �߷�

StartScene::StartScene() 
	: 
	_monsterCount(0),
	_useForce(false),
	_forceRadius(500.f),
	_forceCurRadius(0.f),
	_force(500.f)
{
	p_backGroundTexture = ResourceManager::GetInstance()->LoadTexture(L"BackGroundTexture", L"Textures\\gb_gameSceneBackGround_1.bmp");
}

StartScene::~StartScene()
{
	// �� ���� ����
	
}

void StartScene::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		_useForce = true;

		CreateForce();
	}
	else
	{
		_useForce = false;
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(GROUP_TYPE::END); ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObjects((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (_useForce && nullptr != vecObj[j]->GetRigidBody())
			{
				Vector2 diff = vecObj[j]->GetPos() - _mouseForcePos;
				float len = diff.Length();
				Vector2 tempDiff = diff;
			
				if (len < _forceRadius)
				{
					float ratio = 1.f - (len / _forceRadius);
					float force = _force * ratio;
					
					vecObj[j]->GetRigidBody()->AddForce(tempDiff.Normalize() * force);
				}
			}

			vecObj[j]->update();

		}
	}
	
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	/*if (KEY_TAP(KEY::LBTN))
	{
		Vector2 lookAtPos = CameraManager::GetInstance()->GetRealPos(MOUSE_POS);
		CameraManager::GetInstance()->SetLookAtPos(lookAtPos);
	}*/
}

void StartScene::Enter()
{
	// Object �߰�
	CObject* player = new CPlayer();
	player->SetObjectName(L"Player");
	player->SetPos(Vector2(640.f, 384.f));
	player->SetScale(Vector2(100.f, 100.f));

	AddObject(player, GROUP_TYPE::PLAYER);

	RegisterPlayer(player);

	// ��������� �׽�Ʈ
	//CObject* otherPlayer = obj->Clone();
	//otherPlayer->SetPos(Vector2(740.f, 384.f));
	//AddObject(otherPlayer, GROUP_TYPE::PLAYER);

	// Player �i�ƴٴϴ°� ��� �ߴ�
	// CameraManager::GetInstance()->SetTarget(obj);

	Vector2 resolution = CCore::GetInstance()->GetResolution();

	// ���� ��ġ
#pragma region "AI ���� ���� ���� ����"
	//SetMonsterCount(8);
	//float moveDistance = 25.f;
	//float monsterScale = 50.f;
	//float term = ( resolution._x - (moveDistance + monsterScale / 2.f) * 2) / static_cast<float>(GetMonsterCount() - 1);

	//CMonster* monster = nullptr;

	//AI* ai = new AI();
	//ai->AddState(new Idle);
	//ai->AddState(new Trace);

	//for (int i = 0; i < GetMonsterCount(); ++i)
	//{
	//	monster = new CMonster();
	//	monster->SetObjectName(L"Monster");
	//	monster->SetScale(Vector2(50.f, 50.f));
	//	monster->SetPos(Vector2(resolution / 2.f) - Vector2(0.f, 300.f));
	//	monster->SetMonsterId(_monsterId++);

	//	monster->SetAI(ai);

	//	AddObject(monster, GROUP_TYPE::MONSTER);
	//}
#pragma endregion

#pragma region "AI ���� ���� ����"

	// ���� ��ġ
	CMonster* monster = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, Vector2(resolution / 2.f) - Vector2(0.f, 300.f));
	AddObject(monster, GROUP_TYPE::MONSTER);

	// Ground��ġ
	CObject* ground = new Ground();
	ground->SetScale(Vector2(400.f, 100.f));
	ground->SetPos(Vector2(640.f, 484.f));
	AddObject(ground, GROUP_TYPE::GROUND);

#pragma endregion

	// Ÿ�� �ε�
	// LoadTile(L"Tile\\start.tile");

	// ================================
	// �浹 ����
	
	// Player �׷�� Monster�׷� ���� �浹üũ ( Plyaer�׷�� Monster�׷��� �浹�� ���̶�� �˸���)
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// ���� �÷��̾� �浹 ����
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// =================================


	// =================================
	// Camera Look ����
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);
	// =================================

	// =================================
	// Camera Effect ����
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
	//CameraManager::GetInstance()->FadeOut(1.5f);
	//CameraManager::GetInstance()->FadeIn(1.5f);
	//CameraManager::GetInstance()->FadeOut(1.5f);
	//CameraManager::GetInstance()->FadeIn(1.5f);
	//CameraManager::GetInstance()->FadeOut(1.5f);
	//CameraManager::GetInstance()->FadeIn(1.5f);
	//CameraManager::GetInstance()->FadeOut(1.5f);
	//CameraManager::GetInstance()->FadeIn(1.5f);
	// =================================

	// =======================================
	// Init �Լ� ȣ��
	Init();
	// =======================================

}

void StartScene::render(HDC dc)
{
	//  Background rendering
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	BitBlt
	(
		dc,
		0, 0,
		(int)resolution._x,
		(int)resolution._y,
		p_backGroundTexture->GetDC(),
		0, 0, SRCCOPY
	);

	// ���� ����� ���� �� �׸���
	if (_useForce)
	{
		SelectGDI gdi(dc, HBRUSH_TYPE::HOLLOW);
		SelectGDI gdi2(dc, HPEN_TYPE::GREEN);

		_forceCurRadius += _forceRadius * 5.f * DeltaTime_F;
		if (_forceCurRadius > _forceRadius)
		{
			_forceCurRadius = 0.f;
		}

		Vector2 _renderPos = CameraManager::GetInstance()->GetRenderPos(_mouseForcePos);

		Ellipse
		(
			dc,
			static_cast<int>(_renderPos._x - _forceCurRadius),
			static_cast<int>(_renderPos._y - _forceCurRadius),
			static_cast<int>(_renderPos._x + _forceCurRadius),
			static_cast<int>(_renderPos._y + _forceCurRadius)
		);
	}

	CScene::render(dc);
}

void StartScene::Exit()
{
	DeleteAllGroups();

	// ������ �׷��� �浹 �׷� ����(���� ����� ���̴ϱ�)
	ColliderManager::GetInstance()->ResetGroup();
}

void StartScene::CreateForce()
{
	_mouseForcePos = CameraManager::GetInstance()->GetRealPos(MOUSE_POS);



}