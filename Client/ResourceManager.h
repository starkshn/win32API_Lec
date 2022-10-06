#pragma once

class Texture;
class Resources;

class ResourceManager
{
	SINGLE(ResourceManager);

private:
	map<wstring, Resources*> _mapTexture;

public:
	Texture* LoadTexture(const wstring& key, const wstring& path);
	Texture* CreateTexture(const wstring& key, UINT width, UINT height);

	Texture* FindTexture(const wstring& key);

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




