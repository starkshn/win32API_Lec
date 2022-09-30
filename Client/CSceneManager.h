#pragma once

class CScene;

class CSceneManager
{
	SINGLE(CSceneManager);

private :
	CScene* p_scenes[static_cast<unsigned int>(SCENE_TYPE::END)]; // ��� �� ���
	CScene* p_curScene; // ���� ��

private:
	void ChangeRealScene(SCENE_TYPE sceneType);

	

public:
	void init();
	void update();
	void render(HDC sceneDC);
	
public:
	CScene* GetCurScene() { return p_curScene; }


	friend class EventManager;
};

