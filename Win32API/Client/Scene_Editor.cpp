#include "pch.h"
#include "Scene_Editor.h"

#include "Core.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "UIManager.h"

#include "Camera.h"

#include "Tile.h"
#include "CanvasUI.h"
#include "ButtonUI.h"

CScene_Editor::CScene_Editor()
{
}

CScene_Editor::~CScene_Editor()
{
}

void CScene_Editor::SetTileIdx()
{
	static CTile* pTile = nullptr;

	if (__KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = __MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetLocationPos(vMousePos);

		int iTileX = GetTileMaxCol();
		int iTileY = GetTileMaxRow();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < iTileX 
			&& 0.f <= vMousePos.y && iRow < iTileY)
		{
			int iIdx = iRow * iTileX + iCol;

			const vector<CObject*>& vecTile = GetObjectGroup(GROUP_TYPE::TILE);
			pTile = dynamic_cast<CTile*>(vecTile[iIdx]);
		}
		else
		{
			pTile = nullptr;
		}
	}

	if (__KEY_TAP(KEY::PAGE_DOWN))
	{
		if (pTile)
		{
			pTile->NextImageIdx();
		}
	}

	if (__KEY_TAP(KEY::PAGE_UP))
	{
		if (pTile)
			pTile->PrevImageIdx();
	}

	Vec2 vMousePos = __MOUSE_POS;
}

void CScene_Editor::SceneIn()
{
	// UI Create
	{
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		// Canvas
		CUI* pCanvasUI = new CCanvasUI;
		pCanvasUI->SetName(L"Canvas UI");
		pCanvasUI->SetScale(Vec2(500.f, 300.f));
		pCanvasUI->SetPos(Vec2(vResolution.x - pCanvasUI->GetScale().x, 0.f));

		// Button
		CButtonUI* pButtonUI = new CButtonUI;
		pButtonUI->SetName(L"Button UI");
		pButtonUI->SetScale(Vec2(100.f, 40.f));
		pButtonUI->SetPos(Vec2(0.f, 0.f));
						
		// RelationShip
		pCanvasUI->AddChildUI(pButtonUI);

		// Scene Add
		CObjectManager::GetInst()->CreateObject(pCanvasUI, GROUP_TYPE::UI);

		// Clone Test
		CUI* pCanvasClone = pCanvasUI->Clone();
		pCanvasClone->SetPos(pCanvasClone->GetPos() + Vec2(-500.f, 0.f));
		CObjectManager::GetInst()->CreateObject(pCanvasClone, GROUP_TYPE::UI);

		// Regist Function
		{
			// Origin
			((CButtonUI*)pCanvasClone->GetChildUI()[0])
					->SetCallBack_1Param(std::bind(&CSceneManager::RequestSubstituteScene<DWORD_PTR>, CSceneManager::GetInst(), std::placeholders::_1), FUNCTION_REGISTER_BUTTON::LBUTTON, (DWORD_PTR)SCENE_TYPE::ENTRY);


			// __AddDynamic_MULTICAST_SET_CALLBACK_1PARAM(pButtonUI, std::bind(&CSceneManager::RequestSubstituteScene<DWORD_PTR>, CSceneManager::GetInst(), std::placeholders::_1), (DWORD_PTR)SCENE_TYPE::ENTRY);
			// __AddDynamic_MULTICAST_SET_CALLBACK_1PARAM(pButtonUI, std::bind(&CSceneManager::RequestSubstituteScene<DWORD_PTR>, CSceneManager::GetInst(), std::placeholders::_1), (DWORD_PTR)SCENE_TYPE::ENTRY);
		}

		// Register UI
		RegisterUI(pCanvasClone, UI_TYPE::TILE);
		RegisterUI(pCanvasUI, UI_TYPE::INVENTORY);
	}
}

void CScene_Editor::SceneOut()
{
	CObjectManager::GetInst()->Reset();
}

void CScene_Editor::KeyShortcut()
{
	if (__KEY_TAP(KEY::T))
	{
		bool bRender = m_arrUI[static_cast<UINT>(UI_TYPE::TILE)]->IsRender();
		m_arrUI[static_cast<UINT>(UI_TYPE::TILE)]->SetRender(!bRender);

		CUIManager::GetInst()->SetFocusedUI(m_arrUI[static_cast<UINT>(UI_TYPE::TILE)]);
	}

	if (__KEY_TAP(KEY::I))
	{
		bool bRender = m_arrUI[static_cast<UINT>(UI_TYPE::INVENTORY)]->IsRender();
		m_arrUI[static_cast<UINT>(UI_TYPE::INVENTORY)]->SetRender(!bRender);

		CUIManager::GetInst()->SetFocusedUI(m_arrUI[static_cast<UINT>(UI_TYPE::INVENTORY)]);
	}
}

void CScene_Editor::RegisterUI(CUI* _pUI, UI_TYPE _eType)
{
	m_arrUI[static_cast<UINT>(_eType)] = _pUI;
	_pUI->SetRender(false);
}

void CScene_Editor::update()
{
	__super::update();

	SetTileIdx();
}