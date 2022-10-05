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
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

CPlayer::CPlayer()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2{0.f, 5.f});
	GetCollider()->SetColliderScale(Vector2{ 30.f, 30.f });

	SetObjectName(L"player");

	// Animator 추가
	// 애니매이션 가로 74pixel, 세로 80pixel
	Texture* texture = ResourceManager::GetInstance()->LoadTexture(L"PlayerAnimationTexture", L"Textures\\Animations2.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", texture, Vector2(0, 320), Vector2(74, 80), Vector2(74, 0), 0.08f, 10);
	GetAnimator()->PlayAnimation(L"WALK_DOWN", true);

	Animation* anim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (UINT i = 0; i < anim->GetMaxFrame(); ++i)
	{
		anim->GetAnimFrame(i)._offset = Vector2(0.f, -50.f);
	}

}
CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	Vector2 pos = GetPos();

	if ( KEY_HOLD(KEY::W) )
	{
		pos._y -= 200.f * DeltaTime_F;
	}
	if (KEY_HOLD(KEY::S))
	{
		pos._y += 200.f * DeltaTime_F;
	}
	if (KEY_HOLD(KEY::A))
	{
		pos._x -= 200.f * DeltaTime_F;
	}
	if (KEY_HOLD(KEY::D))
	{
		pos._x += 200.f * DeltaTime_F;
	}

	// Missile
	if (KEY_TAP(KEY::Z))
	{
		CreateMissile();
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateThreeMissile();
	}

	SetPos(pos);

	GetAnimator()->update();
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

	Texture* texture = ResourceManager::GetInstance()->LoadTexture(L"PlayerTexture", L"texture\\gb_player_1.bmp");

	Vector2 pos = GetPos();
	pos = CameraManager::GetInstance()->GetRenderPos(pos);

	float width = static_cast<float>(texture->GetWidth());
	float height = static_cast<float>(texture->GetHeight());

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255; // 고정 알파값. (일단 최대치 줌)
	
	AlphaBlend
	(
		dc,
		width / 2.f, height / 2.f,
		width, height,
		texture->GetDC(),
		0, 0, width, height,
		bf
	);


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

