#pragma once
#include "CObject.h"
#include "CMissile.h"

class CPlayer;
class Texture;
class Coliider;

class ThreeMissile : public CObject
{
private:
	CLONE(ThreeMissile);
	int			_id = 0;
	Texture*	p_missileTexture;

public:
	ThreeMissile();
	virtual ~ThreeMissile() override;

public:
	void SetId(int id) { _id = id; }
	int GetId() { return _id; }

public:
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	virtual void OnCollisionEnter(Collider* other) final;
	virtual void OnCollisionStay(Collider* other) final;
	virtual void OnCollisionExit(Collider* other) final;
};

