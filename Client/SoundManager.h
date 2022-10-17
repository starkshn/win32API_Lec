#pragma once

// sound �뵵 - ��� ���� �߿�
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class Sound;

class SoundManager
{
	SINGLE(SoundManager);

private:
	LPDIRECTSOUND8	_sound;	// ����ī�� ��ǥ ��ü
	Sound*			p_BGM;	// ���� ������ BGM Sound

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return _sound; }
	void RegisterToBGM(Sound* _pSound);
};

