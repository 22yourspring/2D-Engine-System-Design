#include "pch.h"
#include "Core.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "UIManager.h"

#include "Camera.h"

CCore::CCore()
	: m_hWnd(NULL)
	, m_ptResolution{}
	, m_hDC(NULL)
	, m_hBit(NULL)
	, m_memDC(NULL)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (size_t i = 0; i < static_cast<UINT>(PEN_TYPE::COUNT); i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::CreatePaintDevice()
{
	// Brush
	m_arrBrush[static_cast<UINT>(BRUSH_TYPE::HOLLOW)] = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
	
	// pen
	m_arrPen[static_cast<UINT>(PEN_TYPE::RED)] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[static_cast<UINT>(PEN_TYPE::GREEN)] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[static_cast<UINT>(PEN_TYPE::BLUE)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	// Member Setting
	{
		m_hWnd = _hWnd;
		m_ptResolution = _ptResolution;
		m_hDC = GetDC(m_hWnd);
	}

	// Resolution
	{
		RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
		SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, NULL);
	}

	// Double Buffering Setting
	{
		m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
		m_memDC = CreateCompatibleDC(m_hDC);
		HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_memDC, m_hBit));
		DeleteObject(hPrevBit);
	}

	// Create Paint Device
	{
		CreatePaintDevice();
	}

	// Manager Class Initialize
	{
		CPathManager::GetInst()->init();
		CTimeManager::GetInst()->init();
		CKeyManager::GetInst()->init();
		CSceneManager::GetInst()->init();
	}

	return S_OK;
}

void CCore::progress()
{
	update();
	render();
}

void CCore::update()
{
	CTimeManager::GetInst()->update();
	CKeyManager::GetInst()->update();
	CCamera::GetInst()->update();
	CEventManager::GetInst()->update();
	CSceneManager::GetInst()->update();
	CCollisionManager::GetInst()->update();
	CUIManager::GetInst()->update();
}

void CCore::render()
{
	// Clear Window
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Rendering
	CSceneManager::GetInst()->render(m_memDC);

	// Double Buffering
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
