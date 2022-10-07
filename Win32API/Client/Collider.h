#pragma once
#include "Component.h"
class CCollider final :
    public CComponent
{
public:
    CCollider();
    CCollider(CObject* _pOwner);
    CCollider(const CCollider& _Origin);
    virtual ~CCollider() override;

private:
    Vec2        m_vPos;
    Vec2        m_vOffset;
    Vec2        m_vScale;

    UINT        m_iCollisionCount;

    UINT        m_iID;
    static UINT g_iDistributeID;

public:
    void SetOffset(Vec2 _vPos) { m_vOffset = _vPos; }
    Vec2 GetOffset() { return m_vOffset; }

    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    Vec2 GetScale() { return m_vScale; }

    Vec2 GetPos() { return m_vPos; }

    UINT GetID() { return m_iID; }

public:
    void OnCollisionIn(CCollider* _pOther);
    void OnCollision(CCollider* _pOther);
    void OnCollisionOut(CCollider* _pOther);

public:
    virtual void Component_update() override;
    virtual void Component_render(HDC _DC) override;

    CCollider& operator = (CCollider& _Origin) = delete;
};

