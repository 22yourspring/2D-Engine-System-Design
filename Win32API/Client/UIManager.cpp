#include "pch.h"
#include "UIManager.h"

#include "SceneManager.h"
#include "KeyManager.h"

#include "Scene.h"
#include "UI.h"

CUIManager::CUIManager()
	: m_pFocusedUI(nullptr)
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::SetFocusedUI(CUI* _pUI)
{
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;


	CScene* pScene = CSceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pScene->GetUIGroup();


	// Focus Release
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusedUI == *iter)
			break;
	}	

	// Move Last
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pScene = CSceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pScene->GetUIGroup();


	bool bLPressed = __KEY_TAP(KEY::LBTN);
	bool bRPressed = __KEY_TAP(KEY::RBTN);


	// Default Setting
	CUI* pFocusedUI = m_pFocusedUI;
	
	if (!bLPressed && !bRPressed)
		return pFocusedUI;

	// Priority to Rendering
	vector<CObject*>::iterator pickedUIiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); iter++)
	{
		if (((CUI*)*iter)->IsHovered())
		{
			pickedUIiter = iter;
		}
	}

	// Nothing Picking
	if (pickedUIiter == vecUI.end())
		return nullptr;

	pFocusedUI = (CUI*)*pickedUIiter;

	// Move Last
	vecUI.erase(pickedUIiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIManager::GetPickedUI(CUI* _pParentUI)
{
	bool bLAway = __KEY_AWAY(KEY::LBTN);
	bool bRAway = __KEY_AWAY(KEY::RBTN);

	CUI* pPickedUI = nullptr;

	static list<CUI*>	listQueueUI;
	static vector<CUI*>	vecUnPickedUI;

	listQueueUI.clear();
	vecUnPickedUI.clear();

	listQueueUI.push_back(_pParentUI);

	while (!listQueueUI.empty())
	{
		CUI* pUI = listQueueUI.front();
		listQueueUI.pop_front();

		// Mouse Confirm
		if (pUI->IsHovered())
		{
			if (pPickedUI)
			{
				vecUnPickedUI.push_back(pPickedUI);
			}

			pPickedUI = pUI;
		}
		else
		{
			vecUnPickedUI.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			listQueueUI.push_back(vecChild[i]);
		}
	}

	if (bLAway)
	{
		for (size_t i = 0; i < vecUnPickedUI.size(); i++)
		{
			vecUnPickedUI[i]->m_bLPressed = false;
		}
	}

	if (bRAway)
	{
		for (size_t i = 0; i < vecUnPickedUI.size(); i++)
		{
			vecUnPickedUI[i]->m_bRPressed = false;
		}
	}

	return pPickedUI;
}

void CUIManager::ProcessPickedUI()
{
	bool bLPressed = __KEY_TAP(KEY::LBTN);
	bool bLAway = __KEY_AWAY(KEY::LBTN);

	bool bRPressed = __KEY_TAP(KEY::RBTN);
	bool bRAway = __KEY_AWAY(KEY::RBTN);

	if (!m_pFocusedUI || m_pFocusedUI->IsRender() == false)
		return;

	CUI* pPickedUI = GetPickedUI(m_pFocusedUI);

	if (pPickedUI)
	{
		pPickedUI->MouseHovered();

		// Left Button
		if (bLPressed)
		{
			pPickedUI->MouseLPressed();
			pPickedUI->m_bLPressed = true;
		}
		else if (bLAway)
		{
			pPickedUI->MouseLReleased();

			if (pPickedUI->m_bLPressed)
			{
				pPickedUI->MouseLClicked();
			}
			pPickedUI->m_bLPressed = false;
		}

		// Right Button
		if (bRPressed)
		{
			pPickedUI->MouseRPressed();
			pPickedUI->m_bRPressed = true;
		}
		else if (bRAway)
		{
			pPickedUI->MouseRReleased();

			if (pPickedUI->m_bRPressed)
			{
				pPickedUI->MouseRClicked();
			}
			pPickedUI->m_bRPressed = false;
		}
	}
}

void CUIManager::update()
{
	// Focus UI (ex-Canvas)	
	m_pFocusedUI = GetFocusedUI();	

	// Picked Event Process
	ProcessPickedUI();
}
