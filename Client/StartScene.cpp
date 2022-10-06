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

StartScene::StartScene() : _monsterCount(0)
{
	p_backGroundTexture = ResourceManager::GetInstance()->LoadTexture(L"BackGroundTexture", L"Textures\\gb_gameSceneBackGround_1.bmp");
}

StartScene::~StartScene()
{
	// 씬 전부 삭제
	
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
	// Object 추가
	CObject* obj = new CPlayer();
	obj->SetPos(Vector2(640.f, 384.f));
	obj->SetScale(Vector2(100.f, 100.f));

	AddObject(obj, GROUP_TYPE::PLAYER);

	// 복사생성자 테스트
	//CObject* otherPlayer = obj->Clone();
	//otherPlayer->SetPos(Vector2(740.f, 384.f));
	//AddObject(otherPlayer, GROUP_TYPE::PLAYER);

	// Player 쫒아다니는거 잠시 중단
	// CameraManager::GetInstance()->SetTarget(obj);

	// 몬스터 배치
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

	// 타일 로딩
	// LoadTile(L"Tile\\start.tile");


	// 충돌 지정
	// Player 그룹과 Monster그룹 간의 충돌체크 ( Plyaer그룹과 Monster그룹이 충돌할 것이라고 알린다)
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look 지정
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);
	
	// Camera Effect 지정
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

	// 기존의 그룹의 충돌 그룹 해제(씬이 변경될 것이니까)
	ColliderManager::GetInstance()->ResetGroup();
}