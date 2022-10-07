#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "Core.h"

#include "KeyManager.h"
#include "TimeManager.h"

CCamera::CCamera()
	: m_pObservedObject(nullptr)
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	SetObservedPosition(vResolution / 2.f);
}

CCamera::~CCamera()
{
}

void CCamera::CalculateShifted()
{
	m_vCurrObservedPos = lerp(m_vCurrObservedPos, m_vObservedPos, 5.f * __DELTATIME);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenterPos = vResolution / 2.f;

	m_vShifted = m_vCurrObservedPos - vCenterPos;
}

void CCamera::update()
{
	if (__KEY_HOLD(KEY::NUMPAD_8))
		m_vObservedPos.y -= 500.f * __DELTATIME;

	if (__KEY_HOLD(KEY::NUMPAD_2))
		m_vObservedPos.y += 500.f * __DELTATIME;

	if (__KEY_HOLD(KEY::NUMPAD_4))
		m_vObservedPos.x -= 500.f * __DELTATIME;

	if (__KEY_HOLD(KEY::NUMPAD_6))
		m_vObservedPos.x += 500.f * __DELTATIME;

	if (__KEY_TAP(KEY::RBTN) && __KEY_HOLD(KEY::SPACE))
	{
		Vec2 vMousePos = __MOUSE_POS;
		Vec2 vObservedPosition = GetLocationPos(vMousePos);
		SetObservedPosition(vObservedPosition);
	}

	if (m_pObservedObject)
	{
		if (!m_pObservedObject->IsEnable())
			m_pObservedObject = nullptr;
		else
			m_vObservedPos = m_pObservedObject->GetPos();
	}

	CalculateShifted();
}
