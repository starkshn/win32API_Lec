#pragma once
class PathManager
{
SINGLE(PathManager);

private:
	wchar_t _contentsPath[256]; // ������
	wchar_t _relativePath[256];

public :
	void init();
	const wchar_t* GetContentsPath() { return _contentsPath; }


	// ��θ� �����ָ��� ��� ��θ� �߶� ��ȯ.
	wstring GetRelativePath(const wchar_t* _filePath);
	
};

