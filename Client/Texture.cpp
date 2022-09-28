#include "pch.h"
#include "Texture.h"
#include "CCore.h"

Texture::Texture() : _dc(0), _bitMap{ 0 }, _objectInfo{}
{
	
}

Texture::~Texture()
{
	DeleteDC(_dc);
	DeleteObject(_bitMap);
}

void Texture::Load(const wstring& path)
{
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	_bitMap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 비트맵과 연결할 DC
	_dc = CreateCompatibleDC(CCore::GetInstance()->GetMainDC());

	// 비트맵과 DC연결
	HBITMAP prevBit = (HBITMAP)SelectObject(_dc, _bitMap);
	DeleteObject(prevBit);

	// 비트맵 정보
	GetObject(_bitMap, sizeof(BITMAP), &_objectInfo);

	if (_bitMap == nullptr)
		assert(_bitMap);

}

