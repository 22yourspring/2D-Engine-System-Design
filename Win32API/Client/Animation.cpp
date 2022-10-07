#include "pch.h"
#include "Animation.h"

#include "Camera.h"
#include "TimeManager.h"

#include "Animator.h"
#include "Object.h"
#include "Texture.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetFrame(UINT _iFrame)
{
	m_bFinish = false;
	m_iFrame = _iFrame;
	m_fAccTime = 0.f;
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	__tagAnimFrame tFrame = {};

	for (int i = 0; i < _iFrameCount; i++)
	{
		tFrame.fDuration = _fDuration;
		tFrame.vCropSize = _vCropSize;
		tFrame.vLT = _vLT + _vInterval * i;

		m_vecFrame.push_back(tFrame);
	}
}

void CAnimation::Add(Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount)
{
	__tagAnimFrame tFrame = {};

	for (int i = 0; i < _iFrameCount; i++)
	{
		tFrame.fDuration = _fDuration;
		tFrame.vCropSize = _vCropSize;
		tFrame.vLT = _vLT + _vInterval * i;

		m_vecFrame.push_back(tFrame);
	}
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += __DELTATIME;

	if (m_vecFrame[m_iFrame].fDuration < m_fAccTime)
	{
		m_fAccTime -= m_vecFrame[m_iFrame].fDuration;
		m_iFrame++;

		if (m_vecFrame.size() <= m_iFrame)
		{
			m_iFrame = -1;
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _DC)
{
	if (m_bFinish)
		return;

	CObject* pObject = m_pAnimator->Object();
	Vec2 vPos = pObject->GetPos();
	vPos += m_vecFrame[m_iFrame].vOffset;

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_DC
		, (int)(vPos.x - m_vecFrame[m_iFrame].vCropSize.x / 2.f)
		, (int)(vPos.y - m_vecFrame[m_iFrame].vCropSize.y / 2.f)
		, (int)(m_vecFrame[m_iFrame].vCropSize.x)
		, (int)(m_vecFrame[m_iFrame].vCropSize.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrame[m_iFrame].vLT.x)
		, (int)(m_vecFrame[m_iFrame].vLT.y)
		, (int)(m_vecFrame[m_iFrame].vCropSize.x)
		, (int)(m_vecFrame[m_iFrame].vCropSize.y)
		, RGB(255, 0, 255));
}
