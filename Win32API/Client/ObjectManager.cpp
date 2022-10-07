#include "pch.h"
#include "ObjectManager.h"
#include "EventManager.h"
#include "SceneManager.h"

#include "Scene.h"

CObjectManager::CObjectManager()
	: m_pScene(nullptr)
{
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::CreateObject(CObject* _pObject, GROUP_TYPE _eType)
{
	m_pScene = CSceneManager::GetInst()->GetCurScene();

	m_pScene->AddObject(_pObject, _eType);
}

void CObjectManager::DeleteGroup(GROUP_TYPE _eType)
{
	m_pScene = CSceneManager::GetInst()->GetCurScene();

	m_pScene->DeleteGroup(_eType);
}

void CObjectManager::Reset()
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::COUNT); i++)
	{
		DeleteGroup(static_cast<GROUP_TYPE>(i));
	}
}

void CObjectManager::RequestCreate(CObject* _pObject, GROUP_TYPE _eGroup)
{
	EventInfo tEvent = {};
	tEvent.eEvent = EVENT_TYPE::CREATE_OBJECT;
	tEvent.lParam = reinterpret_cast<DWORD_PTR>(_pObject);
	tEvent.wParam = static_cast<DWORD_PTR>(_eGroup);

	CEventManager::GetInst()->AddEvent(tEvent);
}

void CObjectManager::RequestDelete(CObject* _pObject)
{
	EventInfo tEvent = {};
	tEvent.eEvent = EVENT_TYPE::DELETE_OBJECT;
	tEvent.lParam = reinterpret_cast<DWORD_PTR>(_pObject);

	CEventManager::GetInst()->AddEvent(tEvent);
}