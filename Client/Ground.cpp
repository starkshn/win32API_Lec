#include "pch.h"
#include "Ground.h"

#include "Collider.h"
#include "Gravity.h"

Ground::Ground()
{
	CreateCollider();
}

Ground::~Ground()
{

}

void Ground::Init()
{
	GetCollider()->SetColliderScale(Vector2(GetScale()));
}

void Ground::update()
{

}

void Ground::OnCollisionEnter(Collider* other)
{
	CObject* otherObj = other->GetColliderOwner();
	if (otherObj->GetObjectName() == L"Player")
	{
		otherObj->GetGravity()->SetOnGround(true);

		Vector2 objPos = other->GetFinalPos();
		Vector2 objScale = other->GetColliderScale();
		
		Vector2 pos = GetCollider()->GetFinalPos();
		Vector2 scale = GetCollider()->GetColliderScale();

		float len = abs(objPos._y - pos._y);
		float value = (objScale._y / 2.f + scale._y / 2.f) - len;
		
		objPos = otherObj->GetPos();
		objPos._y -= (value - 1.f);

		otherObj->SetPos(objPos);
	}
}

void Ground::OnCollisionStay(Collider* other)
{
	CObject* otherObj = other->GetColliderOwner();

	if (otherObj->GetObjectName() == L"Player")
	{
		otherObj->GetGravity()->SetOnGround(true);

		Vector2 objPos = other->GetFinalPos();
		Vector2 objScale = other->GetColliderScale();

		Vector2 pos = GetCollider()->GetFinalPos();
		Vector2 scale = GetCollider()->GetColliderScale();

		float len = abs(objPos._y - pos._y);
		float value = (objScale._y / 2.f + scale._y / 2.f) - len;

		objPos = otherObj->GetPos();
		objPos._y -= (value - 1.f);

		otherObj->SetPos(objPos);
	}
}

void Ground::OnCollisionExit(Collider* other)
{
	CObject* otherObj = other->GetColliderOwner();

	if (otherObj->GetObjectName() == L"Player")
	{
		otherObj->GetGravity()->SetOnGround(false);
	}
}
