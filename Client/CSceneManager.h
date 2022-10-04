#pragma once

class CScene;

class CSceneManager
{
	SINGLE(CSceneManager);

private :
	CScene* p_scenes[static_cast<unsigned int>(SCENE_TYPE::END)]; // ��� �� ���
	CScene* p_curScene; // ���� ��

		// Tile
	UINT		_maxTileRow;
	UINT		_maxTileCol;

private:
	void ChangeRealScene(SCENE_TYPE sceneType);

public:
	void init();
	void update();
	void render(HDC sceneDC);

public:
	// Tile
	void SetTileMaxRow(UINT row) { _maxTileRow = row; }
	void SetTileMaxCol(UINT col) { _maxTileCol = col; }
	
public:
	CScene* GetCurScene() { return p_curScene; }

	// Tile
	UINT GetTileMaxRow() { return _maxTileRow; }
	UINT GetTileMaxCol() { return _maxTileCol; }


	friend class EventManager;
};

