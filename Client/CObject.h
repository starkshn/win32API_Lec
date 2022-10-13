#pragma once


class Collider;
class Animator;
class RigidBody;
class Texture;
class Gravity;

#include "CameraManager.h"
#include "ResourceManager.h"

class CObject
{
private :
	wstring		_objectName;

	float		_theta; // 방향

	Vector2		_dir;
	Vector2		_pos;
	Vector2		_scale;

	// Component
	Collider*	p_collider;
	Animator*	p_animator;
	RigidBody*	p_rigidBody;
	Gravity*	p_gravity;

	bool		_alive;

public:
	CObject();
	CObject(const CObject& origin);
	virtual ~CObject();

public:
	virtual void Init() {}; // Scene이 시작되기 직전에 호출되는 함수
	virtual void update() abstract;
	virtual void finalUpdate();
	virtual void render(HDC dc);

	virtual void OnCollisionEnter(Collider* other) {}
	virtual void OnCollisionStay(Collider* other) {}
	virtual void OnCollisionExit(Collider* other) {}

	virtual CObject* Clone() abstract;

public:
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	Texture* GetAnim(const wstring& name)
	{
		Texture* texture = ResourceManager::GetInstance()->LoadTexture(name, L"Textures\\Sprite\\" + name);
		return texture;
	}

public:
	Collider*	GetCollider() { return p_collider; }
	Animator*	GetAnimator() { return p_animator; }
	RigidBody*	GetRigidBody() { return p_rigidBody; }
	Gravity*	GetGravity() { return p_gravity; }

public:
	void CreateAnimation(const wstring& animName, Texture* texture, Vector2 startPos, Vector2 sliceSize, Vector2 step, float duration, UINT frameCount, bool repeat, Vector2 animOffset);

public:
	void ComponentRender(HDC dc);
	
	// 이벤트 처리를 위해서만 사용할 함수
	void SetDead() { _alive = false; }
	bool IsDead() { return !_alive; }

public :
	void SetPos(Vector2 pos) { _pos = pos; }
	void SetScale(Vector2 scale) { _scale = scale; }
	void SetTheta(float theta) { _theta = theta; }
	void SetDir(Vector2 dir) { _dir = dir; _dir.Normalize(); }
	void SetObjectName(const wstring& name) { _objectName = name; }

public:
	Vector2 GetPos() { return _pos; }
	Vector2 GetScale() { return _scale; }
	Vector2 GetVector2Dir() { return _dir; }
	float	GetTheta() { return _theta; }
	const wstring& GetObjectName() { return _objectName; }

	friend class EventManager;
};

