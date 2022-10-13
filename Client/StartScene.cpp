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

// 물리
#include "RigidBody.h"
#include "SelectGDI.h"

// 땅
#include "Ground.h"

// 중력

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
	// 씬 전부 삭제
	
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
	// Object 추가
	CObject* player = new CPlayer();
	player->SetObjectName(L"Player");
	player->SetPos(Vector2(640.f, 384.f));
	player->SetScale(Vector2(100.f, 100.f));

	AddObject(player, GROUP_TYPE::PLAYER);

	RegisterPlayer(player);

	// 복사생성자 테스트
	//CObject* otherPlayer = obj->Clone();
	//otherPlayer->SetPos(Vector2(740.f, 384.f));
	//AddObject(otherPlayer, GROUP_TYPE::PLAYER);

	// Player 쫒아다니는거 잠시 중단
	// CameraManager::GetInstance()->SetTarget(obj);

	Vector2 resolution = CCore::GetInstance()->GetResolution();

	// 몬스터 배치
#pragma region "AI 이전 버전 몬스터 생성"
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

#pragma region "AI 버젼 몬스터 생성"

	// 몬스터 배치
	CMonster* monster = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, Vector2(resolution / 2.f) - Vector2(0.f, 300.f));
	AddObject(monster, GROUP_TYPE::MONSTER);

	// Ground배치
	CObject* ground = new Ground();
	ground->SetScale(Vector2(400.f, 100.f));
	ground->SetPos(Vector2(640.f, 484.f));
	AddObject(ground, GROUP_TYPE::GROUND);

#pragma endregion

	// 타일 로딩
	// LoadTile(L"Tile\\start.tile");

	// ================================
	// 충돌 지정
	
	// Player 그룹과 Monster그룹 간의 충돌체크 ( Plyaer그룹과 Monster그룹이 충돌할 것이라고 알린다)
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// 땅과 플레이어 충돌 지정
	ColliderManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// =================================


	// =================================
	// Camera Look 지정
	CameraManager::GetInstance()->SetLookAtPos(resolution / 2.f);
	// =================================

	// =================================
	// Camera Effect 지정
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
	// Init 함수 호출
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

	// 힘이 생기는 지점 원 그리기
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

	// 기존의 그룹의 충돌 그룹 해제(씬이 변경될 것이니까)
	ColliderManager::GetInstance()->ResetGroup();
}

void StartScene::CreateForce()
{
	_mouseForcePos = CameraManager::GetInstance()->GetRealPos(MOUSE_POS);



}