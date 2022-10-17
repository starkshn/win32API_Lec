#include "pch.h"
#include "Func.h"
#include "EventManager.h"

void CreateObjectEvent(CObject* objectPtr, GROUP_TYPE groupType)
{
	Event evt = {};
	evt._eventType = EVENT_TYPE::CREATE_OBJECT;
	evt._lParam = (DWORD_PTR)objectPtr;
	evt._rParam = (DWORD_PTR)groupType;
	// DWORD_PTR이지만 안에 데이터의 정체를 알고있다.

	EventManager::GetInstance()->AddEvent(evt);
}

void DeleteObjectEvent(CObject* objectPtr)
{
	Event evt = {};
	evt._eventType = EVENT_TYPE::DELETE_OBJECT;
	evt._lParam = (DWORD_PTR)objectPtr;

	EventManager::GetInstance()->AddEvent(evt);
}

void ChangeScene(SCENE_TYPE changeSceneType)
{
	// 이번프레임에서는 이벤트 등록을 하고 다음 프레임에 씬을 변경을 할 것이다.
	Event evt = {};
	evt._eventType = EVENT_TYPE::SCENE_CHANGE;
	evt._lParam = (DWORD_PTR)changeSceneType;

 	EventManager::GetInstance()->AddEvent(evt);
}

void ChangeAIState(AI* ai, MONSTER_STATE nextState)
{
	Event evt = {};
	evt._eventType = EVENT_TYPE::CHANGE_AI_STATE;
	evt._lParam = (DWORD_PTR)ai;
	evt._rParam = (DWORD_PTR)nextState;

	EventManager::GetInstance()->AddEvent(evt);
}

void SaveWString(const wstring& str, FILE* file)
{
	const wchar_t* filePtr = str.c_str();
	size_t len = str.length();

	// 문자 길이 저장
	fwrite(&len, sizeof(size_t), 1, file);

	// 문자열 저장
	fwrite(filePtr, sizeof(wchar_t), len, file);
}

void LoadWString(wstring& str, FILE* file)
{
	// 길이
	size_t len = 0;
	fread(&len, sizeof(size_t), 1, file);

	// 버퍼
	wchar_t buffer[256] = {};
	fread(buffer, sizeof(wchar_t), len, file);

	str = buffer;
}

void FScanf(char* buffer, FILE* file)
{
	int i = 0;
	while (true)
	{
		char c = static_cast<char>(getc(file));
		if (c == '\n')
		{
			buffer[i++] = '\0';
			break;
		}
		buffer[i++] = c;
	}
}
