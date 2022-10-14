#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CameraManager.h"

// ���
#include "PathManager.h"

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

	_accTime += DeltaTime_F; // �ð�����

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
	pos += _vecAnimFrame[_curFrame]._offset; // Object Position�� Offset��ŭ �߰� �̵���ġ, ������ �����ε�
	
	// ������ ��ǥ�� ��ȯ
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
	// frameCount : �������� ������ ����
	for (UINT i = 0; i < frameCount; ++i)
	{
		frm._duration = duration;
		frm._sliceSize = sliceSize;
		frm._leftTop = startPos + step * (float)i;

		_vecAnimFrame.push_back(frm);
	}
}

void Animation::SaveAnim(const wstring& relativePath)
{
	wstring filePath = PathManager::GetInstance()->GetContentsPath();
	filePath += relativePath; // contents ��� + ����� => ���� ���

	FILE* file = nullptr;
	_wfopen_s(&file, filePath.c_str(), L"wb");
	assert(file);

	// =================================
	// ������ ����ȭ
	
	// =========================
	// 1. ���ڿ� ����
	SaveWString(_animationName, file);
	// =========================

	p_texture; // �ִϸ��̼��� ����ϴ� �ؽ��� (����)

	
	_vecAnimFrame; // ��� ������

	// =========================
	// 2. ������ ���� ����
	
	// ������ ����
	size_t frameCount = _vecAnimFrame.size();
	fwrite(&frameCount, sizeof(size_t), 1, file);

	// ������ ����
	fwrite(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);
	// =========================


	// =========================
	// 3. Texture ����
	


	// =========================

	// =================================

	fclose(file);
}

void Animation::LoadAnim(const wstring& relativePath)
{
	wstring filePath = PathManager::GetInstance()->GetContentsPath();
	filePath += relativePath;

	FILE* file = nullptr;
	_wfopen_s(&file, filePath.c_str(), L"rb");
	assert(file);

	// ==================================
	// 1. ����ȭ�� ���ڿ� ������ ��������
	LoadWString(_animationName, file);
	// ==================================


	// ==================================
	// 2. ������ ������ ��������
	size_t frameCount = 0;
	fread(&frameCount, sizeof(size_t), 1, file);
	
	_vecAnimFrame.resize(frameCount);
	fread(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);
	// ===========================================

	fclose(file);
}
