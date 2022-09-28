#pragma once

// 1. 프레임 동기화
// 2. 키 입력 이벤트의 구체적 처리

enum class KEY_STATE
{
	NONE, // 눌리지 않았고, 이전에도 누르지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 땐 시점
};

enum class KEY
{
	LEFT,
	UP,
	DOWN,
	RIGHT,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	LSHIFT,
	SPACE,
	CTRL,
	ENTER,
	ESC,

	LBTN,
	RBTN,
	
	LAST,
};

struct KeyInfo
{
	KEY_STATE	_state; // 키의 상태
	bool			_isPrevInput; // 이전 프레임에 눌렸는지 여부
};

class CKeyManager
{
	SINGLE(CKeyManager);

private :
	vector<KeyInfo> _vecKey;
	Vector2			_curMousePos;

public :
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY key);
	Vector2 GetCurrentMousePos() { return _curMousePos; }


};

