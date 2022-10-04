#pragma once
#include "CObject.h"

class Texture;

class Tile : public CObject
{
private:
	CLONE(Tile);

private:
	Texture*	p_tileTexture;
	int			_tileImageIdx;
	UINT		_tileRow;
	UINT		_tileCol;

	int			_tileIdxForFunctor;



public:
	Tile();
	virtual ~Tile() override;

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


public:
	int GetTileIdxForFuctor() { return _tileIdxForFunctor; }


};

