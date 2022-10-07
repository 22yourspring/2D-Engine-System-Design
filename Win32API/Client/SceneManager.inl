#include "SceneManager.h"
#include "EventManager.h"

template <typename T>
inline void CSceneManager::RequestSubstituteScene(T _eType)
{
	EventInfo tEvent = {};
	tEvent.eEvent = EVENT_TYPE::SCENE_SUBSTITUTE;
	tEvent.lParam = static_cast<DWORD_PTR>(_eType);

	CEventManager::GetInst()->AddEvent(tEvent);
}