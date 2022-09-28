#pragma once

class Animator;
class Texture;

struct AnimFrame
{
	Vector2		_leftTop;
	Vector2		_sliceSize;
	Vector2		_offset; // offset위치
	float		_duration;
};

class Animation
{
private:
	Animator*			p_animator;
	wstring				_animationName;
	Texture*			p_texture = nullptr; //애니매이션이 사용하는 texture
	vector<AnimFrame>	_vecAnimFrame = {}; // 애니매이션의 모든 프레임 정보
	int					_curFrame; // 현재 프레임
	float				_accTime; // 시간 누적 변수

	bool				_animFinish; // 애니매이션 끝 알림.

public:
	Animation();
	~Animation();

public:
	void update();
	void render(HDC dc);

public:
	void Create(Texture* texture, Vector2 startPos, Vector2 sliceSize, Vector2 step, float duration, UINT frameCount);
	bool IsFinish() { return _animFinish; }

private:
	// 같은 이름 중복 방지를 위해 private
	void SetAnimName(const wstring& animationName) { _animationName = animationName; }
	void SetAnimFrame(int frame) 
	{
		_animFinish = false;
		_curFrame = frame;
		_accTime = 0.f;
	}

public:
	void SetAnimator(Animator* animator) { p_animator = animator; }

public:
	const wstring& GetAnimName() { return _animationName; }
	Animator* GetAnimator() { return p_animator; }
	AnimFrame& GetAnimFrame(int idx) { return _vecAnimFrame[idx]; }
	UINT GetMaxFrame() { return (UINT)_vecAnimFrame.size(); }

	friend class Animator;
};

