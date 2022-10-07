#pragma once
#include "Destructible.h"

class CEnemy :
    public CDestructible
{
public:
    CEnemy();
    virtual ~CEnemy() override;

public:
	CLONE(CEnemy);

private:
    Vec2        m_vCenterPos;
    float       m_fDistance;

    float       m_fSpeed;

    int         m_iDir;        

private:
	class CTexture* m_pTex;

public:
    void        SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void		SetDistance(float _fValue) { m_fDistance = _fValue; }
	float       GetSpeed() { return m_fSpeed; }
	void        SetSpeed(float _fValue) { m_fSpeed = _fValue; }

public:
	virtual void OnCollisionIn(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionOut(CCollider* _pOther) override;

public:
    virtual void update() override;
    virtual void render(HDC _DC) override;
};

