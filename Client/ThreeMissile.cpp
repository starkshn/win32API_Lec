#include "pch.h"
#include "ThreeMissile.h"
#include "CTimeManager.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"

ThreeMissile::ThreeMissile()
{
	p_missileTexture = ResourceManager::GetInstance()->LoadTexture(L"MissileTexture", L"Textures\\gb_missile_1.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2{ 0.f, 0.f });
	GetCollider()->SetColliderScale(Vector2{ 20.f, 20.f });
}

ThreeMissile::~ThreeMissile()
{

}

void ThreeMissile::update()
{
	Vector2 myPos = GetPos();

	if ((GetId() % 3) == 0) 
	{
		//SetTheta(PI / 2.f);
		//myPos._y -= 600.f * sinf(GetTheta()) * DeltaTime_F;
		//myPos._x += 600.f * cosf(GetTheta()) * DeltaTime_F;

		SetDir(Vector2{ 0.f, 1.f });
		Vector2 dir = GetVector2Dir();
		myPos._x += 600.f * dir._x * DeltaTime_F;
		myPos._y -= 600.f * dir._y * DeltaTime_F;
	}
	else if ((GetId() % 3) == 1)
	{
		//SetTheta(PI / 4.f * 3);
		//myPos._y -= 600.f * sinf(GetTheta()) * DeltaTime_F;
		//myPos._x += 600.f * cosf(GetTheta()) * DeltaTime_F;
		
		SetDir(Vector2{ -1.f, 1.f });
		Vector2 dir = GetVector2Dir();
		myPos._x += 600.f * dir._x * DeltaTime_F;
		myPos._y -= 600.f * dir._y * DeltaTime_F;
	}
	else if ((GetId() % 3) == 2)
	{
		//SetTheta(PI / 4.f);
		//myPos._y -= 600.f * sinf(GetTheta()) * DeltaTime_F;
		//myPos._x += 600.f * cosf(GetTheta()) * DeltaTime_F;

		SetDir(Vector2{ 1.f, 1.f });
		Vector2 dir = GetVector2Dir();
		myPos._x += 600.f * dir._x * DeltaTime_F;
		myPos._y -= 600.f * dir._y * DeltaTime_F;
	}

	SetPos(myPos);
}

void ThreeMissile::render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	int width = static_cast<int>(p_missileTexture->GetWidth());
	int height = static_cast<int>(p_missileTexture->GetHeight());

	//Ellipse
	//(	dc,
	//	static_cast<int>(pos._x - scale._x / 2.f),
	//	static_cast<int>(pos._y - scale._y / 2.f),
	//	static_cast<int>(pos._x + scale._x / 2.f),
	//	static_cast<int>(pos._y + scale._y / 2.f)
	//);

	TransparentBlt
	(
		dc,
		static_cast<int>(pos._x - static_cast<float>((width / 2))),
		static_cast<int>(pos._y - static_cast<float>((height / 2))),
		width,
		height,
		p_missileTexture->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	// Component있는 경우 호출...
	CObject::ComponentRender(dc);
}

void ThreeMissile::OnCollisionEnter(Collider* other)
{
	CObject* otherObject = other->GetColliderOwner();

	if (otherObject->GetObjectName() == L"gb_monster_1")
	{
		DeleteObjectEvent(this);
	}
}

void ThreeMissile::OnCollisionStay(Collider* other)
{

}

void ThreeMissile::OnCollisionExit(Collider* other)
{

}