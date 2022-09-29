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

StartScene::StartScene()
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

	for (int i = 0; i < GetMonsterCount(); ++i)
	{
		monster = new CMonster();
		monster->SetPos(Vector2( (moveDistance + monsterScale / 2.f ) + static_cast<float>(i) * term, 50.f));
		monster->SetScale(Vector2(50.f, 50.f));
		monster->SetMoveDistance(moveDistance);
		monster->SetCenterAnchor(monster->GetPos());
		monster->SetMonsterId(_monsterId++);
		AddObject(monster, GROUP_TYPE::MONSTER);
	}

	// �浹 ����
	// Player �׷�� Monster�׷� ���� �浹üũ ( Plyaer�׷�� Monster�׷��� �浹�� ���̶�� �˸���)
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look ����
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);
	
}

void StartScene::render(HDC dc)
{
	Vector2 resolution = CCore::GetInstance()->GetResolution();

	// background rendering
	BitBlt
	(
		dc,
		0, 0,
		resolution._x,
		resolution._y,
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