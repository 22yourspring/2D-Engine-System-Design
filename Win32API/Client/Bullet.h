#pragma once
#include "Destructible.h"

class CBullet :
    public CDestructible
{
public:
    CBullet();
    virtual ~CBullet() override;

public:
	CLONE(CBullet);

private:
    float     m_fTheta;
    Vec2      m_vDir;

private:
	class CTexture* m_pTex;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir;
        m_vDir.Normalize(); 
    }

public:
	virtual void OnCollisionIn(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionOut(CCollider* _pOther) override;

public:
    virtual void update() override;
    virtual void render(HDC _DC) override;
};