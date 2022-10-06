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
	// 1. 옛날방식
	//map<wstring, Texture*>::iterator iter =_mapTexture.begin();
	//for (; iter != _mapTexture.end(); ++iter)
	//{
	//	delete iter->second;
	//}

	// 2. Functor 사용
	// for_each(_mapTexture.begin(), _mapTexture.end(), DeleteTexture());

	// 3. 람다 사용
	// for_each(_mapTexture.begin(), _mapTexture.end(), [&](std::pair<wstring, Texture*> pair) { if (pair.second != nullptr) delete pair.second; });

	// 4. Func.cpp 에 구현한 SafeDeleteMap사용
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

Texture* ResourceManager::CreateTexture(const wstring& key, UINT width, UINT height)
{
	Texture* tex = FindTexture(key);

	if (nullptr != tex)
		return tex;

	tex = new Texture;
	tex->SetKey(key);
	tex->Create(width, height);

	_mapTexture.insert(make_pair(key, tex));

	return tex;
}




Texture* ResourceManager::FindTexture(const wstring& key)
{
	map<wstring, Resources*>::iterator iter = _mapTexture.find(key);
	// auto iter = _mapTexture.find(key);
	if (iter == _mapTexture.end())
		return nullptr;

	return (Texture*)iter->second;
}
