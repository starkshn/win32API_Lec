#pragma once
class PathManager
{
SINGLE(PathManager);

private:
	wchar_t _contentsPath[256]; // 절대경로
	wchar_t _relativePath[256];

public :
	void init();
	const wchar_t* GetContentsPath() { return _contentsPath; }


	// 경로를 던져주면은 상대 경로를 잘라서 반환.
	wstring GetRelativePath(const wchar_t* _filePath);
	
};

