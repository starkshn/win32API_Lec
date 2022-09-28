#pragma once
class PathManager
{
SINGLE(PathManager);

private:
	wchar_t _contentsPath[255];

public :
	void init();
	const wchar_t* GetContentsPath() { return _contentsPath; }

};

