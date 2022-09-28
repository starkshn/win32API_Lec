#pragma once
#include "CObject.h"
#include "CCharingMissile.h"
#include "Collider.h"

class Texture;

class CPlayer : public CObject
{
private:
	CLONE(CPlayer);
	// Texture*	p_myObject;

public :
	CPlayer();
	virtual ~CPlayer() override;

public:
	virtual void update() final;
	virtual void render(HDC dc) final;

public :
	void CreateMissile();
	void CreateThreeMissile();

};