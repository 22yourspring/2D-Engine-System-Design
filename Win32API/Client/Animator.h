#pragma once
#include "Component.h"

class CTexture;
class CAnimation;
class CAnimator :
    public CComponent
{
public:
    CAnimator();
    CAnimator(const CAnimator& _Origin);
    virtual ~CAnimator() override;

private:
    map<wstring, CAnimation*>   m_mapAnimation;
    CAnimation*                 m_pPlayingAnim;
    bool                        m_bRepeat;

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount);
    void AddAnimation(const wstring& _strName, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount);
    CAnimation* FindAnimation(const wstring& _strName);
    void DeleteAnimation(const wstring& _strName);
    void PlayAnimation(const wstring& _strName, bool _bRepeat);
	void ClearAnimation();

public:
    virtual void Component_update() override;
    virtual void Component_render(HDC _DC) override;
};

