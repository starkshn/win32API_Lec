#include "pch.h"
#include "Tile.h"
#include "Texture.h"
#include "CameraManager.h"

Tile::Tile() : p_tileTexture(nullptr), _tileImageIdx(0)
{
	SetScale(Vector2(TILE_SIZE, TILE_SIZE));
}

Tile::~Tile()
{

}

void Tile::update()
{

}

void Tile::render(HDC dc)
{
	if (nullptr == p_tileTexture || -1 == _tileImageIdx)
		return;

	UINT width = p_tileTexture->GetWidth();
	UINT height = p_tileTexture->GetHeight();
	
	// Ÿ�� ������ ���´�.
	UINT maxCol = (width / TILE_SIZE);
	// Ÿ�� �� ������ ���´�. (-1 ���־���Ѵ�. 768px�̿��� �ϴµ� 767px�̶�
	UINT maxRow = (height / TILE_SIZE);

	UINT curRow = static_cast<UINT>(_tileImageIdx / maxCol);
	UINT curCol = static_cast<UINT>(_tileImageIdx % maxRow);

	// ���� ���� �ִ����� �����ʰ� �ϱ� ���� ����ó��
	if (maxRow <= curRow)
		assert(nullptr);

	Vector2 renderPos = CameraManager::GetInstance()->GetRenderPos(GetPos());
	Vector2 scale = GetScale();

	BitBlt
	(
		dc,
		int(renderPos._x), 
		int(renderPos._y),
		int(scale._x),
		int(scale._y),
		p_tileTexture->GetDC(),
		curCol * TILE_SIZE,
		curRow * TILE_SIZE,
		SRCCOPY
	);
}



