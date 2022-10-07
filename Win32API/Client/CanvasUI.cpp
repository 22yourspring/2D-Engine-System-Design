#include "pch.h"
#include "CanvasUI.h"

#include "KeyManager.h"

CCanvasUI::CCanvasUI(bool _bRenderAffected)
	: CUI(_bRenderAffected)
{
}

CCanvasUI::~CCanvasUI()
{
}

void CCanvasUI::MouseHovered()
{
	if (IsLPressed())
	{
		Vec2 vShifted = __MOUSE_POS - m_vDragPos;
		Vec2 vPos = GetPos();

		vPos += vShifted;
		SetPos(vPos);

		m_vDragPos = __MOUSE_POS;
	}
}

void CCanvasUI::MouseLPressed()
{
	m_vDragPos = __MOUSE_POS;
}

void CCanvasUI::MouseLReleased()
{
}

void CCanvasUI::MouseLClicked()
{
}

void CCanvasUI::MouseRPressed()
{
}

void CCanvasUI::MouseRReleased()
{
}

void CCanvasUI::MouseRClicked()
{
}
