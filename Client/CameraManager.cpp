#include "pch.h"
#include "CameraManager.h"

#include "CKeyManager.h"
#include "CTimeManager.h"

#include "CCore.h"
#include "CObject.h"

#include "ResourceManager.h"
#include "Texture.h"

CameraManager::CameraManager()
	:
	_lookAtPos{},
	_targetObject(),  
	_getTargetTime(1.f),
	_accTime(0.5f),
	p_veilTexture(nullptr),
	_effect(CAMERA_EFFECT::NONE),
	_effectDuration(0.f),
	_curTime(0.f)
{
	//_lookAtPos = (Vector2)CCore::GetInstance()->GetResolution() / 2;
	// ó���� Normalize�ϴ� �κж����� �߰��ߴ� �κ���.

	
}

CameraManager::~CameraManager()
{

}

void CameraManager::init()
{
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	
	p_veilTexture = ResourceManager::GetInstance()->CreateTexture(L"CameraVeil", static_cast<UINT>(resolution._x), static_cast<UINT>(resolution._y));
	// �������� ��� �ȼ� �޸� ������ �ʱⰪ�� �� 0���� �з��ִ�. (�ǵ��ʿ����)

}

void CameraManager::update()
{
	if (_targetObject)
	{
		if (_targetObject->IsDead())
		{
			_targetObject = nullptr;
		}
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

void CameraManager::render(HDC dc)
{
	if (CAMERA_EFFECT::NONE == _effect)
		return;

	float ratio = 0.f; // ����Ʈ ���� ����

	if (CAMERA_EFFECT::FADE_OUT == _effect)
	{
		_curTime += DeltaTime_F;

		if (_curTime > _effectDuration)
		{
			_effect = CAMERA_EFFECT::NONE;
			return;
		}

		// 1����Ʈ�� ���� �ð����� ������ �ش�.
		// => 1�ʴ� ��ο����� �ϴ� ���� ���´�.

		// ������ �̷��� ���Ѵ�.
		ratio = _curTime / _effectDuration;
	}

	int alphaValue = static_cast<int>(255.f * ratio);


	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alphaValue; // ���� ���İ�. (�ϴ� �ִ�ġ ��)
	
	AlphaBlend
	(
		dc,
		0, 0, 
		(int)p_veilTexture->GetWidth(), 
		(int)p_veilTexture->GetHeight(),
		p_veilTexture->GetDC(),
		0, 0,
		(int)p_veilTexture->GetWidth(),
		(int)p_veilTexture->GetHeight(),
		bf
	);
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
		Vector2 lookDir = (_lookAtPos - _prevLookPos);

		if (!lookDir.IsZero())
		{
			_corLookPos = _prevLookPos + lookDir.Normalize() * _getTargetSpeed * DeltaTime_F;
		}
	}

	// �� ������ ���̰��� �� ���� _corLookPos�� �i�ư����� �����̴�.
	
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	Vector2 centerPos = resolution / 2.f;

	_diff = _corLookPos - centerPos;
	_prevLookPos = _corLookPos;
}
