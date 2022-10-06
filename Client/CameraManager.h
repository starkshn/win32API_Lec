#pragma once

class CObject;
class Texture;

enum class CAMERA_EFFECT
{
	NONE,
	FADE_IN,
	FADE_OUT,
};

class CameraManager
{
	SINGLE(CameraManager);

private:
	Vector2			_lookAtPos; // ���� ī�޶�� ���� ��ġ
	Vector2			_corLookPos; // ������ġ�� ������ġ�� ������ġ
	Vector2			_prevLookPos; // ī�޶� ���� ���� ������ ��ġ

	CObject*		_targetObject; // ī�޶� Ÿ�� ������Ʈ
	Vector2			_diff; // �ػ� �߽���ġ��, ī�޶� LookAt���� ���̰�.

	float			_getTargetTime = 2.f; // Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float			_getTargetSpeed; // Ÿ���� ���󰡴� �ӵ�
	float			_accTime;	// �����ð�
	
	// Cam Effect
	Texture*		p_veilTexture;		// ī�޶� ������ �ؽ��� 
	CAMERA_EFFECT	_effect;			// ī�޶� ȿ��
	float			_effectDuration;	// ȿ�� ���� �ð�
	float			_curTime;			// ī�޶� ȿ�� ���� ����� �ð�
	
public:
	void init();
	void update();
	void render(HDC dc);

public:
	void CalDiff(); // ȭ�� �߾���ǥ�� LookAt ��ǥ���� ���̰����

public:
	void SetLookAtPos(Vector2 pos) 
	{ 
		_lookAtPos = pos;
		float moveDis = (_lookAtPos - _prevLookPos).Length();

		_getTargetSpeed = moveDis / _getTargetTime;
		_accTime = 0.f;
	}
	void SetTarget(CObject* target) { _targetObject = target; };

public:
	Vector2		GetLookPos() { return _corLookPos; } // ���� �����ִ� ��ġ
	CObject*	GetTarget() { return _targetObject; }
	Vector2		GetRenderPos(Vector2 objPos) { return (objPos - _diff); }
	Vector2		GetRealPos(Vector2 renderPos) { return (renderPos + _diff); }

public:
	void FadeIn(float duration)
	{

	}

	void FadeOut(float duration) 
	{ 
		_effect = CAMERA_EFFECT::FADE_OUT;
		_effectDuration = duration;

		if (0.f == _effectDuration)
			assert(nullptr);
	}
	
};

