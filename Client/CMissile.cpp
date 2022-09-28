#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"

CMissile::CMissile()
{
	SetTheta(PI / 4.f);
	SetDir(Vector2{0.f, 1.f});
	CreateCollider();

	p_cMissileTexture = ResourceManager::GetInstance()->LoadTexture(L"CMissile", L"Textures\\gb_missile_1.bmp");
}
CMissile::~CMissile()
{

}

void CMissile::update()
{
	Vector2 pos = GetPos();

	/*pos._x += 600.f * cosf(_theta) * DeltaTime_F;
	pos._y -= 600.f * sinf(_theta) * DeltaTime_F;*/

	pos._x += 600.f * GetVector2Dir()._x * DeltaTime_F;
	pos._y -= 600.f * GetVector2Dir()._y * DeltaTime_F;

	SetPos(pos);
}

void CMissile::render(HDC dc)
{
	//ector2 pos = GetPos();
	//ector2 scale = GetScale();
	//llipse
	//	dc,
	//	static_cast<int>(pos._x - scale._x / 2.f),
	//	static_cast<int>(pos._y - scale._y / 2.f),
	//	static_cast<int>(pos._x + scale._x / 2.f),
	//	static_cast<int>(pos._y + scale._y / 2.f)
	//;

	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	int width = static_cast<int>(p_cMissileTexture->GetWidth());
	int height = static_cast<int>(p_cMissileTexture->GetHeight());

	TransparentBlt
	(
		dc,
		static_cast<int>(pos._x - static_cast<float>((width / 2))),
		static_cast<int>(pos._y - static_cast<float>((height / 2))),
		width,
		height,
		p_cMissileTexture->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);
}



