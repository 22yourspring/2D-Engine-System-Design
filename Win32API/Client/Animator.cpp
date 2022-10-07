#include "pch.h"
#include "Animator.h"

#include "Animation.h"

CAnimator::CAnimator()
	: m_pPlayingAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Origin)
	: m_pPlayingAnim(nullptr)
	, m_bRepeat(_Origin.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _Origin.m_mapAnimation.begin();

	for (; iter != _Origin.m_mapAnimation.end(); iter++)
	{
		CAnimation* pAnim = new CAnimation;
		pAnim->SetName(iter->second->GetName());
		pAnim->m_pAnimator = this;
		pAnim->m_pTex = iter->second->m_pTex;
		pAnim->m_vecFrame = iter->second->m_vecFrame;
		pAnim->m_iFrame = iter->second->m_iFrame;
		pAnim->m_fAccTime = iter->second->m_fAccTime;
		pAnim->m_bFinish = iter->second->m_bFinish;

		m_mapAnimation.insert(make_pair(iter->second->GetName(), pAnim));
	}

	m_pPlayingAnim = FindAnimation(_Origin.m_pPlayingAnim->GetName());
}

CAnimator::~CAnimator()
{
	ClearAnimation();
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	assert(!pAnim);		// assert(false) : (조건이 ~ 일리가 없다!) 단언하다.

	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pTex, _vLT, _vCropSize, _vInterval, _fDuration, _iFrameCount);

	m_mapAnimation.insert(make_pair(_strName, pAnim));
}

void CAnimator::AddAnimation(const wstring& _strName, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	assert(pAnim);		// assert(false) : (조건이 ~ 일리가 없다!) 단언하다.

	pAnim->Add(_vLT, _vCropSize, _vInterval, _fDuration, _iFrameCount);
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnimation.find(_strName);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimator::DeleteAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnimation.find(_strName);

	if (iter != m_mapAnimation.end())
	{
		delete iter->second;
		m_mapAnimation.erase(iter);
	}
}

void CAnimator::PlayAnimation(const wstring& _strName, bool _bRepeat)
{
	m_pPlayingAnim = FindAnimation(_strName);

	m_bRepeat = _bRepeat;
}

void CAnimator::ClearAnimation()
{
	Safe_Delete_Map<wstring, CAnimation*>(m_mapAnimation);
}

void CAnimator::Component_update()
{
	if (m_pPlayingAnim)
	{
		m_pPlayingAnim->update();
		
		if (m_bRepeat && m_pPlayingAnim->IsFinish())
		{
			m_pPlayingAnim->SetFrame(0);
		}
	}
}

void CAnimator::Component_render(HDC _DC)
{
	if (m_pPlayingAnim)
		m_pPlayingAnim->render(_DC);
}
