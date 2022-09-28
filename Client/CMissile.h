#pragma once
#include "CObject.h"

class Texture;

class CMissile : public CObject
{
private :
	CLONE(CMissile);
	Texture* p_cMissileTexture;

public:
	CMissile();
	virtual ~CMissile() override;

public:
	virtual void update() override;
	virtual void render(HDC dc) override;

};

