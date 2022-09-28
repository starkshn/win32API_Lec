#pragma once
#include "CObject.h"

class Texture;

class Tile : public CObject
{
private:
	CLONE(Tile);

public:
	Tile();
	virtual ~Tile() override;

private:
	Texture*	p_tileTexture;
	int			_tileImageIdx;

private:
	virtual void update() override;
	virtual void render(HDC dc) override;

public:
	void AddImageIdx() { ++_tileImageIdx; };

public:
	void SetTexture(Texture* tileTexture)
	{
		p_tileTexture = tileTexture;
	}


};

