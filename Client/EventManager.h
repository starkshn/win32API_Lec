#pragma once

struct Event
{
	EVENT_TYPE	_eventType;
	DWORD_PTR	_lParam;
	DWORD_PTR	_rParam;
};

class EventManager
{
	SINGLE(EventManager)

private:
	vector<Event> _vecEvents;
	vector<CObject*> _vecDead;

public:
	void update();

private:
	void ExcuteEvent(const Event& event); // �̺�Ʈ ó���Լ�

public:
	void AddEvent(const Event& event)
	{
		_vecEvents.push_back(event);
	}
};

