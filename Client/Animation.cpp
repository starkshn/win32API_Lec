#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CameraManager.h"

Animation::Animation()
	:
	p_animator(nullptr),
	_animationName(),
	_curFrame(0),
	p_texture(nullptr),
	_accTime(0.f),
	_animFinish(false)
{

}

Animation::~Animation()
{

}

void Animation::update()
{
	if (_animFinish)
		return;

	_accTime += DeltaTime_F; // 시간누적

	if (_accTime > _vecAnimFrame[_curFrame]._duration)
	{
		++_curFrame;

		if (_vecAnimFrame.size() <= _curFrame)
		{
			_curFrame = -1;
			_animFinish = true;
			_accTime = 0.f;
			return;
		}

		_accTime = _accTime - _vecAnimFrame[_curFrame]._duration;
	}
}

void Animation::render(HDC dc)
{
	if (_animFinish)
		return;

	CObject* go = p_animator->GetOwnerObject();
	Vector2 pos = go->GetPos();
	pos += _vecAnimFrame[_curFrame]._offset; // Object Position에 Offset만큼 추가 이동위치, 연산자 오버로딩
	
	// 렌더링 좌표로 변환
	pos = CameraManager::GetInstance()->GetRenderPos(pos);

	TransparentBlt
	(
		dc,
		(int)(pos._x - (_vecAnimFrame[_curFrame]._sliceSize._x / 2.f)),
		(int)(pos._y - (_vecAnimFrame[_curFrame]._sliceSize._y / 2.f)),
		(int)(_vecAnimFrame[_curFrame]._sliceSize._x				),
		(int)(_vecAnimFrame[_curFrame]._sliceSize._y				),
		p_texture->GetDC(),
		(int)(_vecAnimFrame[_curFrame]._leftTop._x					),
		(int)(_vecAnimFrame[_curFrame]._leftTop._y					),
		(int)(_vecAnimFrame[_curFrame]._sliceSize._x				),
		(int)(_vecAnimFrame[_curFrame]._sliceSize._y				),
		RGB(255, 0, 255)
	);
}

void Animation::Create
(   
	Texture* texture, 
	Vector2 startPos, Vector2 sliceSize, Vector2 step,
	float duration, UINT frameCount )
{
	p_texture = texture;

	AnimFrame frm = {};
	// frameCount : 만들어내야할 프레임 갯수
	for (UINT i = 0; i < frameCount; ++i)
	{
		frm._duration = duration;
		frm._sliceSize = sliceSize;
		frm._leftTop = startPos + step * (float)i;

		_vecAnimFrame.push_back(frm);
	}
}
