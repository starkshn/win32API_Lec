#include "pch.h"
#include "CTimeManager.h"
#include "CCore.h"

CTimeManager::CTimeManager()
	:
	_curCount {},
	_frequency{},
	_callCount{},
	_deltaTime(0),
	_acc(0),
	_fps(0)
{

}

CTimeManager::~CTimeManager()
{
	
}

void CTimeManager::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&_prevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&_frequency);

}

void CTimeManager::update() 
{
	QueryPerformanceCounter(&_curCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	_deltaTime = static_cast<double>(_curCount.QuadPart - _prevCount.QuadPart) / static_cast<double>(_frequency.QuadPart);

	// 이전 카운트 값을 현재 값으로 갱신(다음번의 계산을 위해서)
	_prevCount = _curCount;

	render();

#ifdef _DEBUG
	if (_deltaTime > (1. / 60.))
	{
		_deltaTime = 1. / 60.;
	}
#endif
}

void CTimeManager::render()
{
	++_callCount; // 1초가 된 순간의 값을 알아야한다.
	_acc += _deltaTime; // DT누적

	if (_acc >= 1.)
	{
		_fps = _callCount;
		_acc = 0;
		_callCount = 0;

		wchar_t buffer[255] = {};
		swprintf_s(buffer, L"FPS : %d, DT : %f", _fps, _deltaTime);
		SetWindowText(CCore::GetInstance()->GetMainHwnd(), buffer);
	}
}
