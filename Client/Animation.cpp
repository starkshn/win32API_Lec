#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CameraManager.h"

// ���
#include "PathManager.h"

// ��/��� ����
#include "ResourceManager.h"

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

	// 1-1 2����Ʈ ������ �׳� ����
	//fwprintf(file, L"[Animation Name]\n");
	//SaveWString(_animationName, file);
	//fwprintf(file, L"\n");

	// 1-2 �޸������� ���� �� ���� ���ǹ��ϰ�
	fprintf(file, "[Animation Name]\n");
	string strAnimName = string(_animationName.begin(), _animationName.end());
	fprintf(file, strAnimName.c_str());
	fprintf(file, "\n\n");
	// =========================
	

	// =========================
	// 2. ������ ���� ����
	//
	// 2-1 ���� ���
	// ������ ����
	//size_t frameCount = _vecAnimFrame.size();
	//fwrite(&frameCount, sizeof(size_t), 1, file);
	//// ������ ����
	//fwrite(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);

	// 2-2 ���ǹ� 
	// 2-2-1 ������ ����
	fprintf(file, "[Texture Name]\n");
	string strKey = string(p_texture->GetKey().begin(), p_texture->GetKey().end());
	fprintf(file, strKey.c_str());
	fprintf(file, "\n\n");

	// 2-2-2 ������ ����
	fprintf(file, "[FrameCount Data]\n");
	fprintf(file, "%d\n", _vecAnimFrame.size());

	for (size_t i = 0; i < _vecAnimFrame.size(); ++i)
	{
		fprintf(file, "[Frame Index %d]\n", i); 
		fprintf(file, "- Index %d LeftTopPos(Vector2) : ", i);
		fprintf(file, "X : %d, Y : %d \n", static_cast<int>(_vecAnimFrame[i]._leftTop._x), static_cast<int>(_vecAnimFrame[i]._leftTop._y));

		_vecAnimFrame[i]._offset;

		fprintf(file, "- Index %d SliceSize(Vector2) : ", i);
		fprintf(file, "X : %d, Y : %d \n", static_cast<int>(_vecAnimFrame[i]._sliceSize._x), static_cast<int>(_vecAnimFrame[i]._sliceSize._y));

		fprintf(file, "- Index %d Offset(Vector2) : ", i);
		fprintf(file, "X : %d, Y : %d \n", static_cast<int>(_vecAnimFrame[i]._offset._x), static_cast<int>(_vecAnimFrame[i]._offset._y));

		fprintf(file, "- Index %d Duration(float) : ", i);
		fprintf(file, "%d\n", static_cast<int>(_vecAnimFrame[i]._duration));
	}
	
	fprintf(file, "\n\n");

	// =========================


	// =========================
	// 3. Texture ����
	// 
	// 3-1 �׳� 2����Ʈ ������ ����
	//SaveWString(p_texture->GetKey(), file);

	//// ResourceManager�� Texture���� ��� ���
	//wstring textureRelativePath = p_texture->GetRelativePath();
	//SaveWString(textureRelativePath, file);

	// 3-2 ���ǹ�
	fprintf(file, "[Texture Path]\n");
	string strTexturePath = string(p_texture->GetRelativePath().begin(), p_texture->GetRelativePath().end());
	fprintf(file, strTexturePath.c_str());
	fprintf(file, "\n");

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
	// ==================================

	// ==================================
	// 3. �ؽ��� ��������
	wstring textureKey;
	wstring textureRelativePath;
	LoadWString(textureKey, file);
	LoadWString(textureRelativePath, file);

	p_texture = ResourceManager::GetInstance()->LoadTexture(textureKey, textureRelativePath);

	// ==================================

	fclose(file);
}
