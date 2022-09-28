#include "pch.h"
#include "CCharingMissile.h"
#include "CTimeManager.h"

CCharingMissile::CCharingMissile() : _dir(1.f), _accSize(1.f), _shootMissile(false)
{

}
CCharingMissile::~CCharingMissile()
{

}

void CCharingMissile::update()
{
	Vector2 pos = GetPos();

	if (_shootMissile)
	{
		pos._y += 600.f * DeltaTime_F * _dir;
	}

	SetPos(pos);
}
void CCharingMissile::render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	Ellipse
	(	dc,
		static_cast<int>(pos._x - scale._x / 2.f),
		static_cast<int>(pos._y - scale._y / 2.f),
		static_cast<int>(pos._x + scale._x / 2.f),
		static_cast<int>(pos._y + scale._y / 2.f)
	);
}
