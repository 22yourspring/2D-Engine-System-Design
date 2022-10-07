#pragma once
class CPaintDevice
{
public:
	CPaintDevice(HDC _DC, BRUSH_TYPE _eType);
	CPaintDevice(HDC _DC, PEN_TYPE _eType);
	~CPaintDevice();

private:
	HDC		m_hDC;

	HBRUSH	m_hDefaultBrush;
	HPEN	m_hDefaultPen;

};

