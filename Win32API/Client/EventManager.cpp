#include "pch.h"

#include "EventManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "UIManager.h"

#include "Scene.h"
#include "Object.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

inline void CEventManager::ProcessEvent()
{
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

inline void CEventManager::DisabledEvent()
{
	for (size_t i = 0; i < m_vecDisabled.size(); i++)
	{
		delete m_vecDisabled[i];
	}

	m_vecDisabled.clear();
}

void CEventManager::Excute(const EventInfo& _tEvent)
{
	switch (_tEvent.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lParam : Object Address
		// wParam : Object Group
		{
			CObject*	pObject = reinterpret_cast<CObject*>(_tEvent.lParam);
			GROUP_TYPE	eType = static_cast<GROUP_TYPE>(_tEvent.wParam);

			CObjectManager::GetInst()->CreateObject(pObject, eType);
		}

		break;
	case EVENT_TYPE::DELETE_OBJECT:
		{
			// Object Set Disabled
			// Collection Disabled Object
			CObject* pObject = reinterpret_cast<CObject*>(_tEvent.lParam);
			if (pObject->IsEnable())
			{
				pObject->SetEnable(false);
				m_vecDisabled.push_back(pObject);
			}
		}
		break;
	case EVENT_TYPE::SCENE_SUBSTITUTE:
		// lParam : Next Scene Type
		CSceneManager::GetInst()->SubstituteScene(static_cast<SCENE_TYPE>(_tEvent.lParam));
		
		// Release Focus
		CUIManager::GetInst()->SetFocusedUI(nullptr);
		break;
	}
}

void CEventManager::update()
{
	DisabledEvent();
	ProcessEvent();
}
