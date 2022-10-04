#pragma once
class ButtonInfo
{
private:
	int _buttonTildIdx;

public:
	void operator () (int tileIdx)
	{
		// TODO
		_buttonTildIdx = tileIdx;
	}
};

