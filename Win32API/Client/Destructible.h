#pragma once
#include "Object.h"
class CDestructible :
    public CObject
{
public:
    CDestructible();
    virtual ~CDestructible() override;

private:
    UINT    m_iHP;

public:
    const UINT  GetHP() const { return m_iHP; }
    void        SetHP(UINT _iHP) { m_iHP= _iHP; }

public:
    virtual void Component_update() override final;
};

