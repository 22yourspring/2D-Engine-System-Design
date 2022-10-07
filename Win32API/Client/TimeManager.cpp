#include "pch.h"
#include "TimeManager.h"
#include "Core.h"

CTimeManager::CTimeManager()
	: m_llCurrCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDt(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_llCurrCount);
	m_dDt = static_cast<double>((m_llCurrCount.QuadPart - m_llPrevCount.QuadPart)) / static_cast<double>(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurrCount;

#ifdef _DEBUG
	if (m_dDt > (1. / 60.))
		m_dDt = (1. / 60.f);
#endif

	m_iCallCount++;
	m_dAcc += m_dDt;	// DT ´©Àû

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		static wchar_t strBuffer[256] = {};

		swprintf_s(strBuffer, L"FPS : %d, Delta Time : %f", m_iFPS, m_dDt);

		SetWindowText(CCore::GetInst()->GetMainHwnd(), strBuffer);
	}
}
