#include "pch.h"
#include "CScene.h"
#include "ResourceManager.h"
#include "CObject.h"
#include "CCore.h"
#include "Tile.h"
#include "Texture.h"

#include "PathManager.h"

CScene::CScene()
	:
	_tileXCount(),
	_tileYCount()
{
	
}

CScene::~CScene()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(GROUP_TYPE::END); ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			if (nullptr != _objects[i][j])
				delete _objects[i][j];
		}
	}
}

void CScene::update()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(GROUP_TYPE::END); ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			if (!_objects[i][j]->IsDead())
			{
				_objects[i][j]->update();
			}
		}
	}
}

void CScene::finalUpdate()
{
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			_objects[i][j]->finalUpdate();
		}
	} 
}

void CScene::render(HDC dc)
{	
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = _objects[i].begin();
		// auto iter = _objects[i].begin();

		for (iter = _objects[i].begin(); iter != _objects[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(dc);
				++iter;
			}
			else
			{
 				iter = _objects[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroupObjects(GROUP_TYPE groupType)
{
	// SafeDeleteVector(_objects[static_cast<UINT>(groupType)]);

	// 밑에처럼 명시적으로 호출하는 것이 원래는 정석이다.
	SafeDeleteVector<CObject*>(_objects[static_cast<UINT>(groupType)]);
}

void CScene::DeleteAllGroups()
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::END); ++i)
	{
		// 모든 오브젝트 싹다 삭제.
		DeleteGroupObjects(static_cast<GROUP_TYPE>(i));
	}
}

void CScene::CreateTile(UINT xCount, UINT yCount)
{
	DeleteGroupObjects(GROUP_TYPE::TILE);

	_tileXCount = xCount;
	_tileYCount = yCount;

	Texture* tileTexture = ResourceManager::GetInstance()->LoadTexture(L"Tile", L"Textures\\tiles.bmp");

	for (UINT y = 0; y < yCount; ++y)
	{
		for (UINT x = 0; x < xCount; ++x)
		{
			Tile* tile = new Tile();

			tile->SetPos(Vector2(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)));

			tile->SetTexture(tileTexture);

			AddObject(tile, GROUP_TYPE::TILE);

		}
	}
}

Vector2 CScene::SetUICenterPos(Vector2 parent, Vector2 child)
{
	float x = (parent._x / 2.f) - (child._x / 2.f);
	float y = (parent._y / 2.f) - (child._y / 2.f);
	return Vector2(x, y);
}

void CScene::LoadTile(const wstring& relativePath)
{
	wstring filePath = PathManager::GetInstance()->GetContentsPath();
	filePath += relativePath;

	// 커널오브젝트 : FILE
	FILE* file = nullptr;

	_wfopen_s(&file, filePath.c_str(), L"rb");
	// 파일 열기 실패
	assert(file);

	// 타일의 가로 세로 갯수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, file);
	fread(&yCount, sizeof(UINT), 1, file);

	// 불러온 타일 갯수에 맞게 타일 생성
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 한다.
	const vector<CObject*>& vecTile = GetGroupObjects(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		dynamic_cast<Tile*>(vecTile[i])->LoadTileInfo(file);
	}
	
	fclose(file);
}



