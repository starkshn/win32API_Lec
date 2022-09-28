#include "pch.h"
#include "MonsterMissile.h"
#include "CMissile.h"
#include "CTimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "CCore.h"


MonsterMissile::MonsterMissile()
{
	p_monsterMissileTexture = ResourceManager::GetInstance()->LoadTexture(L"MonsterMissile", L"Textures\\MonsterMissile.bmp");
	CreateCollider();
}

MonsterMissile::~MonsterMissile()
{
	
}

void MonsterMissile::update()
{
	Vector2 pos = GetPos();

	// pos._x += 600.f * GetTheta() * DeltaTime_F;
	// pos._y += 600.f * GetTheta() * DeltaTime_F;
	// SetDir(Vector2{ 0.f, 1.f });
	pos._x += 600.f * GetVector2Dir()._x * DeltaTime_F;
	pos._y += 600.f * GetVector2Dir()._y * DeltaTime_F;

	SetPos(pos);
}

void MonsterMissile::render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	int width = static_cast<int>(p_monsterMissileTexture->GetWidth());
	int height = static_cast<int>(p_monsterMissileTexture->GetHeight());

	TransparentBlt
	(
		dc,
		static_cast<int>(pos._x - static_cast<float>((width / 2))),
		static_cast<int>(pos._y - static_cast<float>((height / 2))),
		width,
		height,
		p_monsterMissileTexture->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);
}