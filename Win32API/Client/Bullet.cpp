#include "pch.h"
#include "Bullet.h"

#include "TimeManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Camera.h"

CBullet::CBullet()
	: m_fTheta(PI / 2.f * 3.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();

	m_pTex = CResourceManager::GetInst()->LoadTexture(L"Bullet", L"Texture\\Bullet.bmp");

	SetScale(Vec2((float)(m_pTex->GetWidth()), (float)(m_pTex->GetHeight())));

	AddComponent(COMPONENT_TYPE::COLLIDER);

	dynamic_cast<CCollider*>(GetComponent(COMPONENT_TYPE::COLLIDER))->SetOffset(Vec2(0.f, 0.f));
	dynamic_cast<CCollider*>(GetComponent(COMPONENT_TYPE::COLLIDER))->SetScale(Vec2(6.f, 6.f));
}

CBullet::~CBullet()
{
}

void CBullet::OnCollisionIn(CCollider* _pOther)
{
	CObject* pCollisionObject = _pOther->Object();

	if (pCollisionObject->GetCollisionChannelInfo() == GROUP_TYPE::ENEMY)
	{
		CObjectManager::GetInst()->RequestDelete(this);
	}
}

void CBullet::OnCollision(CCollider* _pOther)
{
}

void CBullet::OnCollisionOut(CCollider* _pOther)
{
}

void CBullet::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 500.f * m_vDir.x * __DELTATIME;
	vPos.y += 500.f * m_vDir.y * __DELTATIME;

	SetPos(vPos);
}

void CBullet::render(HDC _DC)
{
	Vec2 vPos = GetPos();

	int iWidth = m_pTex->GetWidth();
	int iHeight = m_pTex->GetHeight();

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_DC
		, static_cast<int>(vPos.x - (iWidth / 2.f))
		, static_cast<int>(vPos.y - (iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(248, 0, 248));
}
