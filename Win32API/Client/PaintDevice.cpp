#include "pch.h"
#include "PaintDevice.h"
#include "Core.h"

CPaintDevice::CPaintDevice(HDC _DC, BRUSH_TYPE _eType)
	: m_hDC(_DC)
	, m_hDefaultBrush(NULL)
	, m_hDefaultPen(NULL)
{
	HBRUSH hBrush = CCore::GetInst()->GetBrush(_eType);
	m_hDefaultBrush = static_cast<HBRUSH>(SelectObject(_DC, hBrush));
}

CPaintDevice::CPaintDevice(HDC _DC, PEN_TYPE _eType)
	: m_hDC(_DC)
	, m_hDefaultBrush(NULL)
	, m_hDefaultPen(NULL)
{
	HPEN hPen = CCore::GetInst()->GetPen(_eType);
	m_hDefaultPen = static_cast<HPEN>(SelectObject(_DC, hPen));
}

CPaintDevice::~CPaintDevice()
{
	SelectObject(m_hDC, m_hDefaultBrush);
	SelectObject(m_hDC, m_hDefaultPen);
}
