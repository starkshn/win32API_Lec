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

#pragma region 바이너리형태
	// 1-1 2바이트 단위로 그냥 저장
	//fwprintf(file, L"[Animation Name]\n");
	//SaveWString(_animationName, file);
	//fwprintf(file, L"\n");
#pragma endregion

	// 1-2 메모장으로 봤을 때 좀더 유의미하게
	fprintf(file, "[Animation Name]\n");
	string strAnimName = string(_animationName.begin(), _animationName.end());
	fprintf(file, strAnimName.c_str());
	fprintf(file, "\n");
	// =========================
	

	// =========================
	// 2. 프레임 정보 저장
	
#pragma region 바이너리형태
	// 2-1 이전 방법
	// 프레임 갯수
	//	size_t frameCount = _vecAnimFrame.size();
	//	fwrite(&frameCount, sizeof(size_t), 1, file);
	//	프레임 정보
	//	fwrite(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);
#pragma endregion
	// 2-2 유의미 
	// 2-2-1 텍스쳐 KEY
	fprintf(file, "[Texture Name(Key)]\n");
	string strKey = string(p_texture->GetKey().begin(), p_texture->GetKey().end());
	fprintf(file, strKey.c_str());
	fprintf(file, "\n");

	// =========================
	// 3. Texture 저장
	// 
	// 3-1 그냥 2바이트 단위로 저장
	//SaveWString(p_texture->GetKey(), file);
	
	//// ResourceManager에 Texture없을 경우 대비
	//wstring textureRelativePath = p_texture->GetRelativePath();
	//SaveWString(textureRelativePath, file);
	
	// 3-2 유의미
	fprintf(file, "[Texture Relative Path]\n");
	string strTexturePath = string(p_texture->GetRelativePath().begin(), p_texture->GetRelativePath().end());
	fprintf(file, strTexturePath.c_str());
	fprintf(file, "\n");
	// =========================

	// 2-2-2 프레임 갯수
	fprintf(file, "[Anim FrameCount Data]\n");
	fprintf(file, "%d\n", static_cast<int>(_vecAnimFrame.size()));

	// 2-2-3 프레임 정보
	for (size_t i = 0; i < _vecAnimFrame.size(); ++i)
	{
		fprintf(file, "[Frame Index]\n");
		fprintf(file, "%d\n", static_cast<int>(i));
		fprintf(file, "LeftTopPos(Vector2)\n");
		fprintf(file, "%d %d \n", static_cast<int>(_vecAnimFrame[i]._leftTop._x), static_cast<int>(_vecAnimFrame[i]._leftTop._y));

		_vecAnimFrame[i]._offset;

		fprintf(file, "SliceSize(Vector2)\n");
		fprintf(file, "%d %d \n", static_cast<int>(_vecAnimFrame[i]._sliceSize._x), static_cast<int>(_vecAnimFrame[i]._sliceSize._y));

		fprintf(file, "Offset(Vector2)\n");
		fprintf(file, "%d %d \n", static_cast<int>(_vecAnimFrame[i]._offset._x), static_cast<int>(_vecAnimFrame[i]._offset._y));

		fprintf(file, "Duration(float)\n");
		fprintf(file, "%f", static_cast<float>(_vecAnimFrame[i]._duration));

		fprintf(file, "\n");
	}

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
	// [1. [바이너리 데이터] 직렬화된 문자열 데이터 가져오기]
	// LoadWString(_animationName, file);
	// 
	// [1. [문자 데이터] 데이터 읽어오기]
	char buffer[256] = {};

	// fscanf_s(file, "%s", buffer, 256);
	// [Animation Name]
	string str;
	FScanf(buffer, file); // 필드 읽어옴
	FScanf(buffer, file); // 이름 읽어옴
	str = buffer;
	_animationName = wstring(str.begin(), str.end());
	
	// ==================================


	// ==================================
	// [2. 바이너리 데이터 프레임 데이터 가져오기]
	// 프레임 갯수
	
	// size_t frameCount = 0;
	// fread(&frameCount, sizeof(size_t), 1, file);
	// 
	
	// [2. 문자열로 읽고 변환 해서 데이터 가져오기]
	// [Texture Name]
	FScanf(buffer, file); // 필드 읽어옴 Texture 필드
	FScanf(buffer, file); // 이름 읽어옴
	str = buffer;
	wstring strTexKey = wstring(str.begin(), str.end());
	// ==================================

	// ==================================
	// [3. 텍스쳐 상대 경로]
	// [FrameCount Data]
	FScanf(buffer, file); // 필드 읽어옴 Texture 필드
	FScanf(buffer, file); // 상대경로 읽어옴
	str = buffer;
	wstring strTexRelativePath = wstring(str.begin(), str.end());
	
	// 있으면 찾아서 반환하고 없다면 로딩한다.
	p_texture = ResourceManager::GetInstance()->LoadTexture(strTexKey, strTexRelativePath);

	// ==================================
	
	// ==================================
	// [4. 프레임 갯수]

	// 애니매이션 
	// _vecAnimFrame.resize(frameCount);
	// fread(_vecAnimFrame.data(), sizeof(AnimFrame), frameCount, file);
	FScanf(buffer, file); // [Anim FrameCount Data]
	int frameCount = 0;
	fscanf_s(file, "%d", &frameCount);

	// ==================================


	// ==================================
	// [5. 프레임 정보 가져오기]
	AnimFrame frm = {};
	for (int i = 0; i < frameCount; ++i)
	{	
		POINT pt = {};

		while (true)
		{
			FScanf(buffer, file);
			
			if (!strcmp("[Frame Index]", buffer))
			{
				fscanf_s(file, "%d", &pt.x);
			}
			else if (!strcmp("LeftTopPos(Vector2)", buffer))
			{
				fscanf_s(file, "%d", &pt.x);
				fscanf_s(file, "%d", &pt.y);

				frm._leftTop = Vector2(pt);
			}
			else if (!strcmp("SliceSize(Vector2)", buffer))
			{
				fscanf_s(file, "%d", &pt.x);
				fscanf_s(file, "%d", &pt.y);

				frm._sliceSize = Vector2(pt);
			}
			else if (!strcmp("Offset(Vector2)", buffer))
			{
				fscanf_s(file, "%d", &pt.x);
				fscanf_s(file, "%d", &pt.y);

				frm._offset = Vector2(pt);
			}
			else if (!strcmp("Duration(float)", buffer))
			{
				fscanf_s(file, "%f", &frm._duration);
				break;
			}
		}

		_vecAnimFrame.push_back(frm);
	}

	// ==================================
	


	// ==================================

	fclose(file);
}
