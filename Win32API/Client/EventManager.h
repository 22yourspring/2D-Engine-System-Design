#pragma once

typedef struct __tagEventInfo
{
	EVENT_TYPE	eEvent;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
}EventInfo;

class CObject;
class CEventManager	final
{
	SINGLE(CEventManager)

private:
	vector<EventInfo>	m_vecEvent;
	vector<CObject*>	m_vecDisabled;

private:
	inline void ProcessEvent();
	inline void DisabledEvent();

	void Excute(const EventInfo& _tEvent);

public:
	inline void AddEvent(const EventInfo& _tEvent) { m_vecEvent.push_back(_tEvent); }

public:
	void update();
};

