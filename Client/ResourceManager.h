#pragma once

class Texture;
class Resources;
class Sound;

class ResourceManager
{
	SINGLE(ResourceManager);

private:
	map<wstring, Resources*> _mapTexture;
	map<wstring, Resources*> _mapSound;

public:
	Texture* CreateTexture(const wstring& key, UINT width, UINT height);

public:
	Texture* LoadTexture(const wstring& key, const wstring& path);
	Sound* LoadSound(const wstring& key, const wstring& path);

public:
	Texture*	FindTexture(const wstring& key);
	Sound*		FindSound(const wstring& key);





	/*
	struct DeleteTexture
	{
		void operator () (std::pair<wstring, Texture*> pair)
		{
			if (pair.second != nullptr)
				delete  pair.second;
		}
	};*/
}; 




