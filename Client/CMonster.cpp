#include "pch.h"
#include "CMonster.h"
#include "CTimeManager.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "MonsterMissile.h"
#include "CCore.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

CMonster::CMonster() 
	: 
	_speed(100.f), 
	_loopDistance(50.f),
	_centerAnchor{0.f, 0.f},
	_dir(1),
	_acc(0.f)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2{0.f, 0.f});
	GetCollider()->SetColliderScale(Vector2(30.f, 30.f));

	SetObjectName(L"gb_monster_1");

	// p_texture = ResourceManager::GetInstance()->LoadTexture(L"MonsterTexture", L"Textures\\gb_monster_1.bmp");
	Texture* texture = ResourceManager::GetInstance()->LoadTexture(L"MonsterAnimationTexture", L"Textures\\Animations2.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", texture, Vector2(0, 320), Vector2(74, 80), Vector2(74, 0), 0.08f, 10);
	GetAnimator()->PlayAnimation(L"WALK_DOWN", true);

	Animation* anim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (int i = 0; i < anim->GetMaxFrame(); ++i)
	{
		anim->GetAnimFrame(i)._offset = Vector2(0.f, 0.f);
	}
}

CMonster::~CMonster()
{

}

void CMonster::update()
{
	Vector2 curPos = GetPos();

	// 진행 방향으로 초당 _speed 만큼 이동
	curPos._x += _speed * _dir * DeltaTime_F;

	// 배회 거리 기준량을 넘어섰는지 확인
	float difDis = abs(_centerAnchor._x - curPos._x) - _loopDistance;

	if (0.f < difDis)
	{
		_dir *= -1;
		curPos._x += difDis * _dir;
	}

	// MissileCoroutine(DeltaTime_F);

	if (GetMonsterId() % 2 == 0)
	{
		if (GetMissileFire())
		{
			CreateMonsterMissile();
		}
	}
	
	_acc += DeltaTime_F;

	if (_acc >= 0.99f)
	{
		SetMissileFire(true);
		_acc = 0.f;
	}
	else
		SetMissileFire(false);

	SetPos(curPos);

	GetAnimator()->update();
}

void CMonster::render(HDC dc)
{
	/*int width = static_cast<int>(p_texture->GetWidth());
	int height = static_cast<int>(p_texture->GetHeight());

	Vector2 pos = GetPos();

	TransparentBlt
	(
		dc,
		static_cast<int>(pos._x - static_cast<float>((width / 2))),
		static_cast<int>(pos._y - static_cast<float>((height / 2))),
		width,
		height,
		p_texture->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);*/

	// Component있는 경우 호출...
	CObject::ComponentRender(dc);
}

void CMonster::CreateMonsterMissile()
{
	Vector2 monsterPos = GetPos();
	Vector2 monsterScale = GetScale();

	// 미사일 생성
	MonsterMissile* missile = new MonsterMissile();

	// 미사일 크기
	missile->SetScale(Vector2(monsterScale._x / 2.f, monsterScale._y / 2.f));

	// 미사일 위치
	monsterPos._y += (GetScale()._y / 2.f) + (missile->GetScale()._y / 2.f);
	missile->SetPos(monsterPos);

	//// 미사일 방향
	//_missile->SetTheta(90.f);
	//_missile->SetTheta(PI / 2.f);
	missile->SetDir(Vector2{ 0.f, 1.f });

	CScene* curScene = CSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(missile, GROUP_TYPE::MONSTERMISSILE);
}

void CMonster::OnCollisionEnter(Collider* other)
{
	CObject* otherPtr = other->GetColliderOwner();

	// 충돌한 물체가 미사일인지 확인후 몬스터를 삭제이벤트에 등록함.
	if (otherPtr->GetObjectName() == L"gb_missile_1")
	{
		_hp -= 1;

		if (_hp <= 0)
			DeleteObjectEvent(this);
	}
}

void CMonster::OnCollisionStay(Collider* other)
{	

}

void CMonster::OnCollisionExit(Collider* other)
{
	
}


