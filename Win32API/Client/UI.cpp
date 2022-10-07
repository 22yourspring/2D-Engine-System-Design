#include "pch.h"
#include "UI.h"

#include "KeyManager.h"

#include "Camera.h"

#include "PaintDevice.h"

CUI::CUI(bool _bRenderAffected)
	: m_pParentUI(nullptr)
	, m_bRenderAffected(_bRenderAffected)
	, m_bMouseHovered(false)
	, m_bLPressed(false)
	, m_bRPressed(false)
{
}

CUI::CUI(const CUI& _Origin)
	: CObject(_Origin)
	, m_pParentUI(nullptr)
	, m_bRenderAffected(_Origin.m_bRenderAffected)
	, m_bMouseHovered(false)
	, m_bLPressed(false)
	, m_bRPressed(false)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); i++)
	{
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec<CUI*>(m_vecChildUI);
}

inline void CUI::AddChildUI(CUI* _pUI)
{
	m_vecChildUI.push_back(_pUI);
	_pUI->m_pParentUI = this;
}

inline void CUI::SetAppliedPos()
{
	m_vAppliedPos = GetPos();

	if (m_pParentUI)
	{
		Vec2 vParentPos = GetParent()->GetAppliedPos();
		m_vAppliedPos += vParentPos;
	}
}

void CUI::HoveredConfirm()
{
	Vec2 vMousePos = __MOUSE_POS;
	Vec2 vUIScale = GetScale();

	if (m_bRenderAffected)
		vMousePos = CCamera::GetInst()->GetLocationPos(vMousePos);

	if (m_vAppliedPos.x <= vMousePos.x && vMousePos.x <= m_vAppliedPos.x + vUIScale.x
		&& m_vAppliedPos.y <= vMousePos.y && vMousePos.y <= m_vAppliedPos.y + vUIScale.y)
	{
		m_bMouseHovered = true;
	}
	else
	{
		m_bMouseHovered = false;
	}
}

void CUI::update_UI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render_UI(HDC _DC)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_DC);
	}
}

void CUI::Component_update_UI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Component_update();
	}
}

void CUI::update()
{
	update_UI();
}

void CUI::render(HDC _DC)
{
	Vec2 vPos = GetAppliedPos();
	Vec2 vScale = GetScale();

	if (m_bRenderAffected)
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	if (m_bLPressed || m_bRPressed)
	{
		if (m_bLPressed)
		{
			CPaintDevice PickingColor(_DC, PEN_TYPE::RED);

			Rectangle(_DC
				, static_cast<int>(vPos.x)
				, static_cast<int>(vPos.y)
				, static_cast<int>(vPos.x + vScale.x)
				, static_cast<int>(vPos.y + vScale.y));
		}
		else if (m_bRPressed)
		{
			CPaintDevice PickingColor(_DC, PEN_TYPE::BLUE);

			Rectangle(_DC
				, static_cast<int>(vPos.x)
				, static_cast<int>(vPos.y)
				, static_cast<int>(vPos.x + vScale.x)
				, static_cast<int>(vPos.y + vScale.y));
		}
	}
	else
	{
		Rectangle(_DC
			, static_cast<int>(vPos.x)
			, static_cast<int>(vPos.y)
			, static_cast<int>(vPos.x + vScale.x)
			, static_cast<int>(vPos.y + vScale.y));
	}

	// Render Child 
	render_UI(_DC);
}

void CUI::Component_update()
{
	__super::Component_update();


	SetAppliedPos();
	HoveredConfirm();

	Component_update_UI();
}
