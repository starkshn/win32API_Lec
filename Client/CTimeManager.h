#pragma once
class CTimeManager
{
	SINGLE(CTimeManager);
private :
	LARGE_INTEGER _curCount;
	LARGE_INTEGER _prevCount;
	LARGE_INTEGER _frequency;
	// FPS
	// 1 프레임당 시간 (Delta Time)

	double			_deltaTime; // 프레임 간의 시간값.
	double			_acc; // 1초 체크를 위한 누적시간.
	UINT				_callCount; // update 호출 횟수 체크
	UINT				_fps; // 초당 호출 횟수
	
public :
	void init();
	void update();
	void render();

public :
	double GetDeltaTime() { return _deltaTime; }
	float GetfDeltaTime() { return static_cast<float>(_deltaTime); }
	double GetAccTime() { return _acc; }

};

 