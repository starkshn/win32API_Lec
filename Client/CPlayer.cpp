#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CMissile.h"
#include "ThreeMissile.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "Texture.h"
#include "PathManager.h"
#include "ResourceManager.h"

// Component
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Gravity.h"

CPlayer::CPlayer()
	:
	_curState(OBJECT_STATE::IDLE),
	_prevState(OBJECT_STATE::IDLE),
	_dir(1),
	_prevDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2{0.f, 5.f});
	GetCollider()->SetColliderScale(Vector2{ 30.f, 30.f });

	SetObjectName(L"player");

	// IDLE 가로 : 32, 세로 39.2: 
	Texture* p_textureRight = GetAnim(L"md_R.bmp");
	Texture* p_textureLeft = GetAnim(L"md_L.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", p_textureRight, Vector2(307, 35), Vector2(30, 35), Vector2(30, 0), 0.09f, 7);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", p_textureLeft, Vector2(10, 35), Vector2(30, 35), Vector2(30, 0), 0.1f, 7);

	// MOVE 가로 23, 세로 35
	GetAnimator()->CreateAnimation(L"MOVE_RIGHT", p_textureRight, Vector2(356, 0), Vector2(23, 35), Vector2(23, 0), 0.09f, 7);
	GetAnimator()->CreateAnimation(L"MOVE_LEFT", p_textureLeft, Vector2(17, 0), Vector2(23, 35), Vector2(23, 0), 0.1f, 7);

	// MOVE 가로 23, 세로 35
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", p_textureRight, Vector2(116, 0), Vector2(25, 35), Vector2(25, 0), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", p_textureLeft, Vector2(337, 0), Vector2(25, 35), Vector2(25, 0), 0.1f, 3);

	GetAnimator()->CreateAnimation(L"ATTACK_RIGHT", p_textureRight, Vector2(25, 248), Vector2(75, 75), Vector2(75, 0), 0.09f, 7);
	GetAnimator()->CreateAnimation(L"TURN_LEFT", p_textureLeft, Vector2(353, 518), Vector2(32, 37), Vector2(-32, 0), 0.1f, 7);

	GetAnimator()->PlayAnimation(L"IDLE_RIGHT", true);

	CreateRigidBody();

	CreateGravity();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	UpdateState();
	UpdateMove();
	UpdateAnimation();

	_prevState = _curState;
	_prevDir = _dir;

	// 중력 최대 가속도 테스트를 위한 재배치
	if (KEY_TAP(KEY::R))
	{
		SetPos(Vector2(640.f, 500.f));
	}
}

void CPlayer::UpdateState()
{
	if (KEY_TAP(KEY::A))
	{
		_dir = -1;
		_curState = OBJECT_STATE::MOVE;
	}
	if (KEY_TAP(KEY::D))
	{
		_dir = 1;
		_curState = OBJECT_STATE::MOVE;
	}

	// Missile
	if (KEY_TAP(KEY::Z))
	{
		// CreateMissile();
		_curState = OBJECT_STATE::ATTACK;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		// CreateThreeMissile();
		_curState = OBJECT_STATE::JUMP;

		if (GetRigidBody())
		{
   			GetRigidBody()->AddVelocity(Vector2(0.f, -200.f));
		}
	}

	if (0.f == GetRigidBody()->GetSpeed())
	{
		if (KEY_NONE(KEY::A) && KEY_NONE(KEY::D) && KEY_NONE(KEY::SPACE))
		{
			_curState = OBJECT_STATE::IDLE;
		}
	}
}

void CPlayer::UpdateAnimation()
{
	if (_prevState == _curState && _prevDir == _dir)
		return;

	switch (_curState)
	{
	case OBJECT_STATE::IDLE:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"IDLE_RIGHT", true);
		else
			GetAnimator()->PlayAnimation(L"IDLE_LEFT", true);
	}
	break;
	case OBJECT_STATE::MOVE:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"MOVE_RIGHT", true);
		else
			GetAnimator()->PlayAnimation(L"MOVE_LEFT", true);
	}
	break;
	case OBJECT_STATE::JUMP:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"JUMP_RIGHT", false);
		else
			GetAnimator()->PlayAnimation(L"JUMP_LEFT", false);
	}
	break;
	case OBJECT_STATE::ATTACK:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"ATTACK_RIGHT", true);
		else
			GetAnimator()->PlayAnimation(L"ATTACK_LEFT", true);
	}
	break;
	case OBJECT_STATE::GETHIT:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"GETHIT_RIGHT", true);
		else
			GetAnimator()->PlayAnimation(L"GETHIT_LEFT", true);
	}
	break;
	case OBJECT_STATE::DIE:
	{
		if (_dir == 1)
			GetAnimator()->PlayAnimation(L"DIE_RIGHT", true);
		else
			GetAnimator()->PlayAnimation(L"DIE_LEFT", true);
	}
	break;
	case OBJECT_STATE::END:
	{

	}
	break;
	default:
		break;
	}
}

void CPlayer::UpdateMove()
{
	RigidBody* rd = GetRigidBody();

	/*if (KEY_HOLD(KEY::W))
	{
		rd->AddForce(Vector2(0.f, -200.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		rd->AddForce(Vector2(0.f, 200.f));
	}*/
	if (KEY_HOLD(KEY::A))
	{
		rd->AddForce(Vector2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		rd->AddForce(Vector2(200.f, 0.f));
	}

	//if (KEY_TAP(KEY::W))
	//{
	//	rd->AddVelocity(Vector2(0.f, -200.f));
	//}
	//if (KEY_TAP(KEY::S))
	//{
	//	rd->AddVelocity(Vector2(0.f, 200.f));
	//}

	if (KEY_TAP(KEY::A))
	{
		rd->AddVelocity(Vector2(-200.f, 0.f));

	}
	if (KEY_TAP(KEY::D))
	{
		rd->AddVelocity(Vector2(200.f, 0.f));
	}
}



void CPlayer::UpdateGravity()
{
	GetRigidBody()->AddForce(Vector2(0.f, 500.f));

}

void CPlayer::render(HDC dc)
{
#pragma region "애니매이션 있는 경우"
	//int width = static_cast<int>(p_myObject->GetWidth());
	//int height = static_cast<int>(p_myObject->GetHeight());
	//
	//Vector2 pos = GetPos();

	//BitBlt
	//(
	//	dc,
	//	static_cast<int>(pos._x - static_cast<float>//((width / 2))),
	//	static_cast<int>(pos._y - static_cast<float>//((height / 2))),
	//	width,
	//	height,
	//	_myObject->GetDC(),
	//	0, 0, SRCCOPY
	//);

	//TransparentBlt
	//(
	//	dc,
	//	static_cast<int>(pos._x - static_cast<float>//((width / 2))),
	//	static_cast<int>(pos._y - static_cast<float>//((height / 2))),
	//	width,
	//	height,
	//	p_myObject->GetDC(),
	//	0, 0, width, height,
	//	RGB(255, 0, 255)
	//);

	// Component있는 경우 호출...
	CObject::ComponentRender(dc);
#pragma endregion

#pragma region "Alpha Blend"

	// 현재 아래코드는 텍스체어 알파 채널 있을 경우 사용이 가능하다.
	//Texture* texture = ResourceManager::GetInstance()->LoadTexture(L"PlayerTexture", L"Textures\\gb_player_1.bmp");

	//Vector2 pos = GetPos();
	//pos = CameraManager::GetInstance()->GetRenderPos(pos);

	//float width = static_cast<float>(texture->GetWidth());
	//float height = static_cast<float>(texture->GetHeight());

	//BLENDFUNCTION bf = {};

	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 255; // 고정 알파값. (일단 최대치 줌)
	//
	//AlphaBlend
	//(
	//	dc,
	//	(int)(width / 2.f), (int)(height / 2.f),
	//	(int)width, (int)height,
	//	texture->GetDC(),
	//	0, 0, (int)width, (int)height,
	//	bf
	//);

#pragma endregion

}

void CPlayer::CreateMissile()
{
	Vector2 playerPos = GetPos();
	
	// 미사일 생성
	CMissile* missile = new CMissile();

	// 미사일 방향
	missile->SetTheta(PI / 2.f);
	/*missile->SetDir(Vector2{-1.f, -7.f});*/

	// 미사일 크기
	missile->SetScale(Vector2(25.f, 25.f));

	// 미사일 위치
	playerPos._y -= (GetScale()._y / 2.f) + (missile->GetScale()._y / 2.f);
	missile->SetPos(playerPos);

	// 미사일 이름
	SetObjectName(L"gb_missile_1");
	
	CreateObjectEvent(missile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::CreateThreeMissile()
{
	Vector2 playerPos = GetPos();

	// 미사일 생성 1, 2, 3
	ThreeMissile* missile1 = new ThreeMissile();
	ThreeMissile* missile2 = new ThreeMissile();
	ThreeMissile* missile3 = new ThreeMissile();

	// 미사일 크기 1, 2, 3
	missile1->SetScale(Vector2(25.f, 25.f));
	missile2->SetScale(Vector2(25.f, 25.f));
	missile3->SetScale(Vector2(25.f, 25.f));

	// 미사일 위치 1, 2, 3
	playerPos._y -= (GetScale()._y / 2.f) + (missile1->GetScale()._y / 2.f);
	missile1->SetPos(playerPos);

	playerPos._x -= (missile2->GetScale()._x);
	missile2->SetPos(playerPos);

	playerPos._x += (missile2->GetScale()._x) + (missile3->GetScale()._x);
	missile3->SetPos(playerPos);
	
	// ID 부여 1, 2, 3
	int id = 0;
	missile1->SetId(id);
	missile2->SetId(++id);
	missile3->SetId(++id);

	// 이름 설정 1, 2, 3
	missile1->SetObjectName(L"gb_missile_1");
	missile2->SetObjectName(L"gb_missile_1");
	missile3->SetObjectName(L"gb_missile_1");

	CreateObjectEvent(missile1, GROUP_TYPE::PROJ_PLAYER);
	CreateObjectEvent(missile2, GROUP_TYPE::PROJ_PLAYER);
	CreateObjectEvent(missile3, GROUP_TYPE::PROJ_PLAYER);

	//CScene* curScene = CSceneManager::GetInstance()->GetCurScene();
	//curScene->AddObject(missile1, GROUP_TYPE::THREEMISSILE);
	//curScene->AddObject(missile2, GROUP_TYPE::THREEMISSILE);
 	//curScene->AddObject(missile3, GROUP_TYPE::THREEMISSILE);
}

