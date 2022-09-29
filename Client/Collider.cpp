#include "pch.h"
#include "Collider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"
#include "CameraManager.h"

UINT Collider::g_ID = 0;

Collider::Collider() : _ID(g_ID++), p_owner(nullptr), _colCount(0)
{

}

Collider::Collider(const Collider& origin) 
	: 
	_ID(g_ID++),
	p_owner(nullptr),
	_offsetPos(origin._offsetPos),
	_colliderScale(origin._colliderScale)
{

}

Collider::~Collider()
{

}

void Collider::finalUpdate()
{
	// Object�� ��ġ�� ���󰣴�.
	// ���󰣴ٱ� ���� �ٷ� ��ġ�� �����Ѵ�.
	Vector2 objectPos = p_owner->GetPos();
	_finalPos = objectPos + _offsetPos;

	assert(0 <= _colCount);
}

void Collider::render(HDC dc)
{
	HPEN_TYPE pen = HPEN_TYPE::GREEN;

	if (_colCount)
	{
		pen = HPEN_TYPE::RED;
	}

	SelectGDI b(dc, HBRUSH_TYPE::HOLLOW);
	SelectGDI p(dc, pen);

	Vector2 renderPos = CameraManager::GetInstance()->GetRenderPos(_finalPos);

	Rectangle
	(
		dc,
		static_cast<int>(renderPos._x - _colliderScale._x / 2.f),
		static_cast<int>(renderPos._y - _colliderScale._y / 2.f),
		static_cast<int>(renderPos._x + _colliderScale._x / 2.f),
		static_cast<int>(renderPos._y + _colliderScale._y / 2.f)
	);
}

void Collider::OnCollisionEnter(Collider* other)
{
	p_owner->OnCollisionEnter(other);

	++_colCount;
}

void Collider::OnCollisonStay(Collider* other)
{
	p_owner->OnCollisionStay(other);
}

void Collider::OnCollisionExit(Collider* other)
{
	p_owner->OnCollisionExit(other);

	--_colCount;
}