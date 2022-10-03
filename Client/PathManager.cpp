#include "pch.h"
#include "PathManager.h"
#include "CCore.h"

PathManager::PathManager() : _contentsPath()
{

}
PathManager::~PathManager()
{

}

void PathManager::init() // 경로 찾아내야한다.
{
	GetCurrentDirectory(255, _contentsPath);

	int len = static_cast<int>(wcslen(_contentsPath));

	for (int i = len - 1; i >= 0; --i)
	{
		if ('\\' == _contentsPath[i])
		{
			_contentsPath[i] = '\0';
			break;
		}
	}

	wcscat_s(_contentsPath, 255, L"\\bin\\Contents\\");
	
	// SetWindowText(CCore::GetInstance()->GetMainHwnd(), _contentsPath);
}

wstring PathManager::GetRelativePath(const wchar_t* _filePath)
{
	// 전체 경로 : filePath
	wstring filePath = _filePath;
	// filePath.find();

	size_t absLen = wcslen(_contentsPath);
	size_t fullLen = filePath.length();
	
	wstring relativePath = filePath.substr(absLen, fullLen - absLen);

	return relativePath;
}