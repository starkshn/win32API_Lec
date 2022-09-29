#include "pch.h"
#include "ResourceManager.h"
#include "Resources.h"
#include "PathManager.h"
#include "Texture.h"
#include <algorithm>

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{
	// 1. �������
	//map<wstring, Texture*>::iterator iter =_mapTexture.begin();
	//for (; iter != _mapTexture.end(); ++iter)
	//{
	//	delete iter->second;
	//}

	// 2. Functor ���
	// for_each(_mapTexture.begin(), _mapTexture.end(), DeleteTexture());

	// 3. ���� ���
	// for_each(_mapTexture.begin(), _mapTexture.end(), [&](std::pair<wstring, Texture*> pair) { if (pair.second != nullptr) delete pair.second; });

	// 4. Func.cpp �� ������ SafeDeleteMap���
	SafeDeleteMap(_mapTexture);
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path)
{
	Texture* loadObject = FindTexture(key);
	if (nullptr != loadObject)
		return loadObject;

	wstring filePath = PathManager::GetInstance()->GetContentsPath();
	filePath += path;

	loadObject = new Texture;
	loadObject->Load(filePath);
	loadObject->SetKey(key);
	loadObject->SetRelativePath(path);

	_mapTexture.insert(make_pair(key, loadObject));
	
	return loadObject;
}

Texture* ResourceManager::FindTexture(const wstring& key)
{
	map<wstring, Resources*>::iterator iter = _mapTexture.find(key);
	// auto iter = _mapTexture.find(key);
	if (iter == _mapTexture.end())
		return nullptr;

	return (Texture*)iter->second;
}