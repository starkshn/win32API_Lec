#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CameraManager.h"

// 경로
#include "PathManager.h"

// 입/출력 관련
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

void Animation::SaveAnim(const wstring& relativePath)
{
	wstring filePath = PathManager::GetInstance()->GetContentsPath();
	filePath += relativePath; // contents 경로 + 상대경로 => 최종 경로

	FILE* file = nullptr;
	_wfopen_s(&file, filePath.c_str(), L"wb");
	assert(file);

	// =================================
	// 데이터 직렬화
	
	// =========================
	// 1. 문자열 저장

	// 1-1 2바이트 단위로 그냥 저장
	//fwprintf(file, L"[Animation Name]\n");
	//SaveWString(_animationName, file);
	//fwprintf(file, L"\n");

	// 1-2 메모장으로 봤을 때 좀더 유의미하게
	fprintf(file, "[Animation Name]\n");
	string strAnimName = string(_animationName.begin(), _animationName.end());
	fprintf(file, strAnimName.c_str());
	fprintf(file, "\n\n");
	// =========================
	

	// =========================
	// 2. 프레임 정보 저장
	//
	// 2-1 이전 방법
	// 프레임 갯수
	//size_t frameCount = _vecAnimFrame.size();
	//fwrite(&frameCount, sizeof(size_t), 1, file);
	//// 프레임 정보
	//fwrite(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);

	// 2-2 유의미 
	// 2-2-1 프레임 갯수
	fprintf(file, "[Texture Name]\n");
	string strKey = string(p_texture->GetKey().begin(), p_texture->GetKey().end());
	fprintf(file, strKey.c_str());
	fprintf(file, "\n\n");

	// 2-2-2 프레임 정보
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
	// 3. Texture 저장
	// 
	// 3-1 그냥 2바이트 단위로 저장
	//SaveWString(p_texture->GetKey(), file);

	//// ResourceManager에 Texture없을 경우 대비
	//wstring textureRelativePath = p_texture->GetRelativePath();
	//SaveWString(textureRelativePath, file);

	// 3-2 유의미
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
	// 1. 직렬화된 문자열 데이터 가져오기
	LoadWString(_animationName, file);
	// ==================================


	// ==================================
	// 2. 프레임 데이터 가져오기
	size_t frameCount = 0;
	fread(&frameCount, sizeof(size_t), 1, file);
	
	_vecAnimFrame.resize(frameCount);
	fread(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);
	// ==================================

	// ==================================
	// 3. 텍스쳐 가져오기
	wstring textureKey;
	wstring textureRelativePath;
	LoadWString(textureKey, file);
	LoadWString(textureRelativePath, file);

	p_texture = ResourceManager::GetInstance()->LoadTexture(textureKey, textureRelativePath);

	// ==================================

	fclose(file);
}
