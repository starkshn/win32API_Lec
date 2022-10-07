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

StartScene::StartScene() : _monsterCount(0)
{
	p_backGroundTexture = ResourceManager::GetInstance()->LoadTexture(L"BackGroundTexture", L"Textures\\gb_gameSceneBackGround_1.bmp");
}

StartScene::~StartScene()
{
	// �� ���� ����
	
}

void StartScene::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vector2 lookAtPos = CameraManager::GetInstance()->GetRealPos(MOUSE_POS);
		CameraManager::GetInstance()->SetLookAtPos(lookAtPos);
	}
}

void StartScene::Enter()
{
	// Object �߰�
	CObject* obj = new CPlayer();
	obj->SetPos(Vector2(640.f, 384.f));
	obj->SetScale(Vector2(100.f, 100.f));

	AddObject(obj, GROUP_TYPE::PLAYER);

	// ��������� �׽�Ʈ
	//CObject* otherPlayer = obj->Clone();
	//otherPlayer->SetPos(Vector2(740.f, 384.f));
	//AddObject(otherPlayer, GROUP_TYPE::PLAYER);

	// Player �i�ƴٴϴ°� ��� �ߴ�
	// CameraManager::GetInstance()->SetTarget(obj);

	// ���� ��ġ
	SetMonsterCount(8);
	float moveDistance = 25.f;
	float monsterScale = 50.f;

	Vector2 resolution = CCore::GetInstance()->GetResolution();
	float term = ( resolution._x - (moveDistance + monsterScale / 2.f) * 2) / static_cast<float>(GetMonsterCount() - 1);

	CMonster* monster = nullptr;

	AI* ai = new AI();
	ai->AddState(new Idle);
	ai->AddState(new Trace);

	for (int i = 0; i < GetMonsterCount(); ++i)
	{
		monster = new CMonster();
		monster->SetObjectName(L"Monster");
		monster->SetScale(Vector2(50.f, 50.f));
		monster->SetPos(Vector2(resolution / 2.f) - Vector2(0.f, 300.f));
		monster->SetMonsterId(_monsterId++);

		monster->SetAI(ai);

		AddObject(monster, GROUP_TYPE::MONSTER);
	}

	// Ÿ�� �ε�
	// LoadTile(L"Tile\\start.tile");

	// �浹 ����
	// Player �׷�� Monster�׷� ���� �浹üũ ( Plyaer�׷�� Monster�׷��� �浹�� ���̶�� �˸���)
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look ����
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);
	
	// Camera Effect ����
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
	CameraManager::GetInstance()->FadeOut(1.5f);
	CameraManager::GetInstance()->FadeIn(1.5f);
}

void StartScene::render(HDC dc)
{
	Vector2 resolution = CCore::GetInstance()->GetResolution();

	// background rendering
	BitBlt
	(
		dc,
		0, 0,
		(int)resolution._x,
		(int)resolution._y,
		p_backGroundTexture->GetDC(),
		0, 0, SRCCOPY
	);

	CScene::render(dc);
}

void StartScene::Exit()
{
	DeleteAllGroups();

	// ������ �׷��� �浹 �׷� ����(���� ����� ���̴ϱ�)
	ColliderManager::GetInstance()->ResetGroup();
}