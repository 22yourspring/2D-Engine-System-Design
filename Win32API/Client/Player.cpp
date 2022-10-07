#include "pch.h"
#include "Player.h"

#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"

#include "Scene.h"
#include "Bullet.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

CPlayer::CPlayer()
{
	// CTexture* pTex = CResourceManager::GetInst()->LoadTexture(L"Player", L"Texture\\Zelda_Link.bmp");
	CTexture* pTex = CResourceManager::GetInst()->LoadTexture(L"Player", L"Texture\\Link_Sprites.bmp");
	SetScale(Vec2((float)(pTex->GetWidth()), (float)(pTex->GetHeight())));

	AddComponent(COMPONENT_TYPE::COLLIDER);
	// dynamic_cast<CCollider*>(GetComponent(COMPONENT_TYPE::COLLIDER))->SetOffset(Vec2(1.f, 5.f));
	GetCollider()->SetOffset(Vec2(1.f, 5.f));
	// dynamic_cast<CCollider*>(GetComponent(COMPONENT_TYPE::COLLIDER))->SetScale(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(15.f, 15.f));

	AddComponent(COMPONENT_TYPE::ANIMATOR);
	//GetAnimator()->CreateAnimation(L"Walk_Down", pTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"walk_up", pTex, Vec2(123.f, 82.f), Vec2(18.f, 29.f), Vec2(18.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"walk_down", pTex, Vec2(52.f, 125.f), Vec2(18.f, 30.f), Vec2(18.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"walk_left", pTex, Vec2(387.f, 82.f), Vec2(26.f, 25.f), Vec2(26.f, 0.f), 0.1f, 4);
	GetAnimator()->AddAnimation(L"walk_left", Vec2(0.f, 125.f), Vec2(26.f, 25.f), Vec2(26.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"walk_right", pTex, Vec2(231.f, 82.f), Vec2(26.f, 26.f), Vec2(26.f, 0.f), 0.1f, 6);
	
	// GetAnimator()->PlayAnimation(L"Walk_Down", true);
	GetAnimator()->PlayAnimation(L"walk_left", true);

	GetAnimator()->DeleteAnimation(L"Test");

	/*CAnimation* pAnim = GetAnimator()->FindAnimation(L"Walk_Down");
	
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetAnimFrame(i).vOffset = Vec2(0.f, -20.f);
	}*/
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (CKeyManager::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		vPos.y -= 200.f * __DELTATIME;
		GetAnimator()->PlayAnimation(L"walk_up", true);
	}

	if (CKeyManager::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		vPos.y += 200.f * __DELTATIME;
		GetAnimator()->PlayAnimation(L"walk_down", true);
	}

	if (CKeyManager::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * __DELTATIME;
		GetAnimator()->PlayAnimation(L"walk_left", true);
	}

	if (CKeyManager::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * __DELTATIME;
		GetAnimator()->PlayAnimation(L"walk_right", true);
	}

	if (__KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _DC)
{
	
}

void CPlayer::OnCollisionIn(CCollider* _pOther)
{
}

void CPlayer::OnCollision(CCollider* _pOther)
{
}

void CPlayer::OnCollisionOut(CCollider* _pOther)
{
}

void CPlayer::CreateBullet()
{
	CBullet* pBullet = new CBullet;
	
	// Bullet Position
	Vec2 vPos = GetPos();
	vPos.y -= GetScale().y / 2;
	pBullet->SetPos(vPos);

	// Bullet Direction
	pBullet->SetDir(Vec2(0, -1));

	CObjectManager::GetInst()->RequestCreate(pBullet, GROUP_TYPE::PROJECTILE_PLAYER);
}
