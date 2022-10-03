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
	virtual void SaveTileInfo(FILE* file);
	virtual void LoadTileInfo(FILE* file);
	
public:
	void AddImageIdx() { ++_tileImageIdx; };

public:
	void SetTileTexture(Texture* tileTexture)
	{
		p_tileTexture = tileTexture;
	}

};

