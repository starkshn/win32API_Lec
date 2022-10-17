#pragma once
#include "Resources.h"
class Sound : public Resources
{
private:
	float	_soundPos;
	float	_soundVolume;
	bool	_playBgm;

public:
	Sound();
	~Sound();

public:
	void Load(const wstring& path);

public:
	void SetPosition(float pos);
	void SetVolume(float volum);

public:
	void PlayBgm(bool play);

};

