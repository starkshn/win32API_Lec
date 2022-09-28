#pragma once

class CObject;

class Collider
{
private:
	static UINT g_ID;

	UINT _ID = 0; // 충돌체의 고유한 ID값
	
	CObject* p_owner; // collider를 소유하고 있는 오브젝트

	Vector2 _offsetPos; // 오브젝트로 부터 상대적인 위치
	Vector2 _finalPos; // finalUpdate에서 매 프레임마다 계산
	Vector2 _colliderScale; // 충돌체 크기

	UINT	_colCount;

public:
	Collider();
	Collider(const Collider& origin);
	~Collider();

public:
	void finalUpdate();
	void render(HDC dc);

public :
	// 충돌 시점 함수.
	void OnCollisonStay(Collider* other); // 충돌중인 경우 호출되는 함수.
	void OnCollisionEnter(Collider* other);
	void OnCollisionExit(Collider* other);

	Collider& operator = (const Collider& other) = delete;

public:
	void SetOffsetPos(Vector2 pos) { _offsetPos = pos; }
	void SetColliderScale(Vector2 scale) { _colliderScale = scale; }

public:
	Vector2		GetOffsetPos() { return _offsetPos; }
	Vector2		GetColliderScale() { return _colliderScale; }
	Vector2		GetFinalPos() { return _finalPos ; }
	UINT		GetID() { return _ID; }
	CObject*	GetColliderOwner() { return p_owner; }
	
	friend class CObject;
};

//UINT Collider::g_ID = 0;

