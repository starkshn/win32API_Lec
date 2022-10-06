#pragma once

class CObject;
class Texture;

enum class CAMERA_EFFECT
{
	NONE,
	FADE_IN,
	FADE_OUT,
};

struct CameraEffect
{
	CAMERA_EFFECT	_effectType;	// ī�޶� ȿ��
	float			_duration;		// ȿ�� ���� �ð�
	float			_curTime;		// ī�޶� ȿ�� ���� ����� �ð�
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
	//CAMERA_EFFECT	_effect;			// ī�޶� ȿ��
	//float			_effectDuration;	// ȿ�� ���� �ð�
	//float			_curTime;			// ī�޶� ȿ�� ���� ����� �ð�
	
	// ���������� ȿ���� ó���ϱ� ���� vector x -> list
	list<CameraEffect> _listCameraEffect;
	
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
		CameraEffect cf = {};
		cf._effectType = CAMERA_EFFECT::FADE_IN;
		cf._duration = duration;
		cf._curTime = 0.f;

		_listCameraEffect.push_back(cf);

		if (0.f == duration)
			assert(nullptr);
	}

	void FadeOut(float duration) 
	{ 
		CameraEffect cf = {};
		cf._effectType = CAMERA_EFFECT::FADE_OUT;
		cf._duration = duration;
		cf._curTime = 0.f;

		_listCameraEffect.push_back(cf);

		if (0.f == duration)
			assert(nullptr);
	}
	
};

