#include "pch.h"
#include "KeyManager.h"
#include "Core.h"

int g_arrVK[static_cast<int>(KEY::COUNT)] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_INSERT,
	VK_DELETE,
	VK_HOME,
	VK_END,
	VK_PRIOR,
	VK_NEXT,

	VK_MENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_TAB,
	VK_ESCAPE,
	VK_RETURN,
};

CKeyManager::CKeyManager()
{
}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::init()
{
	for (int i = 0; i < static_cast<int>(KEY::COUNT); i++)
	{
		m_vecKey.push_back(__tagKeyInfo{ KEY_STATE::NONE, false });
	}
}


void CKeyManager::update()
{
	HWND hWnd = GetFocus();	
								
	if (hWnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::COUNT); i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)				
					m_vecKey[i].eState = KEY_STATE::HOLD;				
				else				
					m_vecKey[i].eState = KEY_STATE::TAP;
				
				m_vecKey[i].bPrevPush = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPush)				
					m_vecKey[i].eState = KEY_STATE::AWAY;				
				else				
					m_vecKey[i].eState = KEY_STATE::NONE;
				
				m_vecKey[i].bPrevPush = false;
			}
		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	else
	{
		for (int i = 0; i < static_cast<int>(KEY::COUNT); i++)
		{
			m_vecKey[i].bPrevPush = false;
		
			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)			
				m_vecKey[i].eState = KEY_STATE::AWAY;
			
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
				m_vecKey[i].eState = KEY_STATE::NONE;			
		}
	}
}
