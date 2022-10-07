#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "PaintDevice.h"

#include "Camera.h"

UINT CCollider::g_iDistributeID = 0;

CCollider::CCollider()
	: m_iID(g_iDistributeID++)
	, m_iCollisionCount(0)
{	
}

CCollider::CCollider(CObject* _pOwner)
	: m_iID(g_iDistributeID++)
	, m_iCollisionCount(0)
{
	m_vScale = _pOwner->GetScale();
}

CCollider::CCollider(const CCollider& _Origin)
	: m_vOffset(_Origin.m_vOffset)
	, m_vScale(_Origin.m_vScale)
	, m_iID(g_iDistributeID++)
	, m_iCollisionCount(0)
{
	SetOwner(nullptr);
}

CCollider::~CCollider()
{
}

void CCollider::OnCollisionIn(CCollider* _pOther)
{
	m_iCollisionCount++;

	Object()->OnCollisionIn(_pOther);
}

void CCollider::OnCollision(CCollider* _pOther)
{
	Object()->OnCollision(_pOther);
}

void CCollider::OnCollisionOut(CCollider* _pOther)
{
	m_iCollisionCount--;

	Object()->OnCollisionOut(_pOther);
}

void CCollider::Component_update()
{
	Vec2 vObjectPos = Object()->GetPos();
	m_vPos = vObjectPos + m_vOffset;

	assert(0 <= m_iCollisionCount);	
}

void CCollider::Component_render(HDC _DC)
{
	PEN_TYPE CollisionPen = PEN_TYPE::GREEN;
	
	if (m_iCollisionCount)
		CollisionPen = PEN_TYPE::RED;

	CPaintDevice Pen(_DC, CollisionPen);
	CPaintDevice Brush(_DC, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_DC
		, static_cast<int>(vRenderPos.x - m_vScale.x / 2.f)
		, static_cast<int>(vRenderPos.y - m_vScale.y / 2.f)
		, static_cast<int>(vRenderPos.x + m_vScale.x / 2.f)
		, static_cast<int>(vRenderPos.y + m_vScale.y / 2.f));
}
