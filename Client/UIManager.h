#pragma once

class UI;

class UIManager
{
	SINGLE(UIManager);

private:

public:
	void update();

public:
	UI* GetTargetUI(UI* parentUI);

};

