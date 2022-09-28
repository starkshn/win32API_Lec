#pragma once
#include "pch.h"

// Singletone
#define SINGLE(type) public : static type* GetInstance() { static type mgr; return &mgr; } private : type(); ~type();

#define DeltaTime_F CTimeManager::GetInstance()->GetfDeltaTime()
#define DeltaTime CTimeManager::GetInstance()->GetDeltaTime()

// 암시적 복사생성자 호출할 경우 부모 복사생성자 호출한다.
#define CLONE(type) type* Clone() { return new type(*this); }

#define KEY_CHECK(key, state) CKeyManager::GetInstance()->GetKeyState(key) == state

#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyManager::GetInstance()->GetCurrentMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 63

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,
	MISSILE,
	CHARGEMISSILE,
	THREEMISSILE,
	MONSTERMISSILE,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class MISSILE_TYPE
{
	DEFAULT,
	CHARINGMISSILE,
	THREEMISSILE,
	MONSTERMISSILE,

	END = 8,
};

enum class HBRUSH_TYPE
{
	HOLLOW,

	END,
};

enum class HPEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

// 지연처리 해야할 부분들
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,


	END,
};

enum class TOOL_SCENE_SERVICE
{
	CHANGE_IMAGE_IDX,



	END,
};
