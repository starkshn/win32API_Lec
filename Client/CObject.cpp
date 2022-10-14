#include "pch.h"
#include "CObject.h"
#include "CKeyManager.h"
#include "CTimeManager.h"

// component
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Gravity.h"

CObject::CObject() 
	: 
	_pos{},
	_scale{},
	p_collider(nullptr),
	p_animator(nullptr),
	p_rigidBody(nullptr),
	p_gravity(nullptr),
	_alive(true)
{

}

CObject::CObject(const CObject& origin)
	:
	_objectName(origin._objectName),
	_pos(origin._pos),
	_scale(origin._scale),
	p_collider(nullptr),
	p_animator(nullptr),
	p_gravity(nullptr),
	_alive(true)
{
	// Collider있는 경우만 복사를 받는다.
	if (origin.p_collider)
	{
		p_collider = new Collider(*origin.p_collider);
		p_collider->p_owner = this;
	}
	
	// TODO : Animator 깊은복사
	if (origin.p_animator)
	{
		p_animator = new Animator(*origin.p_animator);
		p_animator->p_owner = this;
	}

	if (origin.p_gravity)
	{
		p_gravity = new Gravity(*origin.p_gravity);
		p_gravity->p_owner = this;
	}

	if (origin.p_rigidBody)
	{
		p_rigidBody = new RigidBody(*origin.p_rigidBody);
		p_rigidBody->p_owner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != p_collider)
		delete p_collider;

	if (nullptr != p_animator)
		delete p_animator;

	if (nullptr != p_rigidBody)
		delete p_rigidBody;

	if (nullptr != p_gravity)
		delete p_gravity;
}

void CObject::finalUpdate()
{
	if (p_animator != nullptr)
		p_animator->finalUpdate();

	if (p_gravity != nullptr)
		p_gravity->finalUpdate();

	if (p_rigidBody != nullptr)
		p_rigidBody->finalUpdate();

	if (p_collider != nullptr)
		p_collider->finalUpdate();
}

void CObject::render(HDC dc)
{
	Vector2 renderPos = CameraManager::GetInstance()->GetRenderPos(_pos);

	Rectangle
	(
		dc,
		static_cast<int>(renderPos._x - _scale._x / 2.f),
		static_cast<int>(renderPos._y - _scale._y / 2.f),
		static_cast<int>(renderPos._x + _scale._x / 2.f),
		static_cast<int>(renderPos._y + _scale._y / 2.f)
	);

	ComponentRender(dc);
}

// Collider || Animation을 가지고 있을 경우만
void CObject::ComponentRender(HDC dc)
{
	if (nullptr != p_animator)
		p_animator->render(dc);

	if (nullptr != p_collider)
		p_collider->render(dc);
}

void CObject::CreateCollider()
{
	p_collider = new Collider;
	p_collider->p_owner = this;
}

void CObject::CreateAnimator()
{
	p_animator = new Animator();
	p_animator->p_owner = this;
}


void CObject::CreateRigidBody()
{
	p_rigidBody = new RigidBody();
	p_rigidBody->p_owner = this;
}

void CObject::CreateGravity()
{
	p_gravity = new Gravity();
	p_gravity->p_owner = this;
}

void CObject::CreateAnimation(const wstring& animName, Texture* texture, Vector2 startPos, Vector2 sliceSize, Vector2 step, float duration, UINT frameCount, bool repeat, Vector2 animOffset)
{
	CreateAnimator();
	GetAnimator()->CreateAnimation(animName, texture, startPos, sliceSize, step, duration, frameCount);
	GetAnimator()->PlayAnimation(animName, repeat);

	Animation* anim = GetAnimator()->FindAnimation(animName);

	for (UINT i = 0; i < anim->GetMaxFrame(); ++i)
	{
		anim->GetAnimFrame(i)._offset = animOffset + Vector2(3.f, 0.f);
	}
}