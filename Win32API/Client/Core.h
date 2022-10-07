#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;			// Main Window Handle
	POINT	m_ptResolution; // Main Window Resolution
	HDC		m_hDC;			// DC for Draw to Main Window

	HBITMAP	m_hBit;
	HDC		m_memDC;

	// GDI Object
	HBRUSH	m_arrBrush[static_cast<UINT>(BRUSH_TYPE::COUNT)];
	HPEN	m_arrPen[static_cast<UINT>(PEN_TYPE::COUNT)];

public:
	HDC		GetMainDC() { return m_hDC; }
	HWND	GetMainHwnd() { return m_hWnd; }
	POINT	GetResolution() { return m_ptResolution; }

	HBRUSH	GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[static_cast<UINT>(_eType)]; }
	HPEN	GetPen(PEN_TYPE _eType) { return m_arrPen[static_cast<UINT>(_eType)]; }

private:
	void	CreatePaintDevice();

public:
	int		init(HWND _hWnd, POINT	_ptResolution);
	void	progress();

private:
	void	update();
	void	render();
};