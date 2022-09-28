#pragma once
#include "Resources.h"

class Texture : public Resources
{
private :
	HDC _dc; // 커널 오브젝트 id
	HBITMAP _bitMap;
	BITMAP _objectInfo;

private :
	Texture();
	virtual ~Texture() override;
	
public :
	void Load(const wstring& path);

	void SetWidthInfo(LONG width) { _objectInfo.bmWidth = width; }
	void SetHeightInfo(LONG height) { _objectInfo.bmHeight = height; }

	HDC	 GetDC() { return _dc; }
	LONG GetWidth() { return _objectInfo.bmWidth; }
	LONG GetHeight() { return _objectInfo.bmHeight; }
	BITMAP GetInfo() { return _objectInfo; }


	friend class ResourceManager;
};

