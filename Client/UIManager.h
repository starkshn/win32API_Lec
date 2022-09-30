#pragma once

class UI;

class UIManager
{
	SINGLE(UIManager);
	
private:
	UI* _focusedUI;

public:
	void update();
	
public:
	void SetFocusUI(UI* ui);

public:
	UI* GetTargetUI(UI* parentUI);
	UI* GetFocusUI();
};

