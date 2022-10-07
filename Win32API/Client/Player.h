#pragma once
#include "Destructible.h"

class CPlayer :
    public CDestructible
{
public:
    CPlayer();     
    virtual ~CPlayer() override;

public:
	CLONE(CPlayer);

public:
    virtual void OnCollisionIn(CCollider* _pOther) override;
    virtual void OnCollision(CCollider* _pOther) override;
    virtual void OnCollisionOut(CCollider* _pOther) override;

private:
	void CreateBullet();

public:
    virtual void update() override;
    virtual void render(HDC _DC) override;
};

