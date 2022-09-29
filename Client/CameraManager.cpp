#include "pch.h"
#include "CameraManager.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyManager.h"
#include "CTimeManager.h"

CameraManager::CameraManager()
	:
	_lookAtPos{},
	_targetObject(),
	_getTargetTime(1.f),
	_accTime(0.5f)
{
	//_lookAtPos = (Vector2)CCore::GetInstance()->GetResolution() / 2;
	// ó���� Normalize�ϴ� �κж����� �߰��ߴ� �κ���.
}

CameraManager::~CameraManager()
{

}

void CameraManager::update()
{
	if (_targetObject)
	{
		if (_targetObject->IsDead())
			_targetObject = nullptr;
		else
		{
			_lookAtPos = _targetObject->GetPos();
		}
	}

	// camera�̵� �׽�Ʈ
	if (KEY_HOLD(KEY::UP))
		_lookAtPos._y -= 500.f * DeltaTime_F;
	if (KEY_HOLD(KEY::DOWN))
		_lookAtPos._y += 500.f * DeltaTime_F;
	if (KEY_HOLD(KEY::LEFT))
		_lookAtPos._x -= 500.f * DeltaTime_F;
	if (KEY_HOLD(KEY::RIGHT))
		_lookAtPos._x += 500.f * DeltaTime_F;

	
	// ȭ�� �߾���ǥ�� LookAt ��ǥ���� ���̰����
	CalDiff();
}

void CameraManager::CalDiff()
{
	// prevLookAt�� ���� LootAt �� ���̰��� �����ؼ� ������ LooAt�� ���Ѵ�.
	
	_accTime += DeltaTime_F;

	if (_accTime >= _getTargetTime)
	{
		_corLookPos = _lookAtPos;
	}
	else
	{
		Vector2 lookDir = (_lookAtPos - _prevLookPos) + Vector2(0.0001f, 0.0001f);
		_corLookPos = _prevLookPos + lookDir.Normalize() * _getTargetSpeed * DeltaTime_F;
	}

	// �� ������ ���̰��� �� ���� _corLookPos�� �i�ư����� �����̴�.
	
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	Vector2 centerPos = resolution / 2.f;

	_diff = _corLookPos - centerPos;
	_prevLookPos = _corLookPos;
}
