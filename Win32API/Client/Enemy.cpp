#include "pch.h"
#include "Enemy.h"

#include "TimeManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Camera.h"

CEnemy::CEnemy()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fDistance(50.f)
	, m_iDir(1)
{
	m_pTex = CResourceManager::GetInst()->LoadTexture(L"Enemy", L"Texture\\Enemy.bmp");

	SetScale(Vec2((float)(m_pTex->GetWidth()), (float)(m_pTex->GetHeight())));

	AddComponent(COMPONENT_TYPE::COLLIDER);

	dynamic_cast<CCollider*>(GetComponent(COMPONENT_TYPE::COLLIDER))->SetScale(Vec2(15.f, 15.f));
}

CEnemy::~CEnemy()
{
}

void CEnemy::OnCollisionIn(CCollider* _pOther)
{
	CObject* pCollisionObject = _pOther->Object();

	if (pCollisionObject->GetCollisionChannelInfo() == GROUP_TYPE::PROJECTILE_PLAYER)
	{
		CObjectManager::GetInst()->RequestDelete(this);
	}
}

void CEnemy::OnCollision(CCollider* _pOther)
{
}

void CEnemy::OnCollisionOut(CCollider* _pOther)
{
}

void CEnemy::update()
{
	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * m_iDir * __DELTATIME;

	float fDist = abs(m_vCenterPos.x - vPos.x) - m_fDistance;
	if (0 < fDist)
	{
		m_iDir *= -1;
		vPos.x += fDist * m_iDir;
	}

	SetPos(vPos);
}

void CEnemy::render(HDC _DC)
{
	Vec2 vPos = GetPos();

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	int iWidth = m_pTex->GetWidth();
	int iHeight = m_pTex->GetHeight();

	TransparentBlt(_DC
		, static_cast<int>(vPos.x - (iWidth / 2.f))
		, static_cast<int>(vPos.y - (iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(248, 0, 248));
}
