#pragma once

class Collider;

union COLLIDER_ID
{
	struct
	{
		UINT _leftID;
		UINT _rightID;
	};

	ULONGLONG ID;
};

class ColliderManager
{
private:
	SINGLE(ColliderManager)

	// 충돌체간의 이전 프레임의 충돌 정보
	map<ULONGLONG, bool> _mapCollisionInfo;

	UINT _arrCheck[static_cast<UINT>(GROUP_TYPE::END)]; // 그룹간의 충돌 메트릭스

private:
	void CollisionGroupUpdate(GROUP_TYPE left, GROUP_TYPE right);
	bool IsCollision(Collider* leftCol, Collider* rightCol);
	
public:
	void update();
	void CheckGroup(GROUP_TYPE left, GROUP_TYPE right);
	void ResetGroup()
	{
		memset(_arrCheck, 0, sizeof(UINT) * static_cast<UINT>(GROUP_TYPE::END));
	}

};

