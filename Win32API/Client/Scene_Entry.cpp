#include "pch.h"
#include "Scene_Entry.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Core.h"

#include "Texture.h"

#include "PathManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"

#include "Camera.h"

CScene_Entry::CScene_Entry()
{
}

CScene_Entry::~CScene_Entry()
{
}

void CScene_Entry::SceneIn()
{
	// Player 추가
	CObject* pPlayer1 = new CPlayer;
	pPlayer1->SetPos(Vec2(1920.f * 0.5f, 1080.f * 0.5f));
	CObjectManager::GetInst()->CreateObject(pPlayer1, GROUP_TYPE::PLAYER);


	/*
		// ======================= Clone
		CObject* pPlayer2 = new CPlayer(*(CPlayer*)pPlayer1);
		CObjectManager::GetInst()->CreateObject(pPlayer2, GROUP_TYPE::PLAYER);

		CPlayer* pPlayerCasting = dynamic_cast<CPlayer*>(pPlayer1);
		if (pPlayerCasting)
		{
			CObject* pPlayer2 = new CPlayer(*pPlayerCasting);
			pPlayer2->SetPos(Vec2(1920.f * 0.2f, 1080.f * 0.2f));
			CObjectManager::GetInst()->CreateObject(pPlayer2, GROUP_TYPE::PLAYER);
		}

		// CObject* pPlayerClone = pPlayer1->Clone();
		CObject* pPlayerClone = __OBJECT_CLONE(pPlayer1);
		pPlayerClone->SetPos(Vec2(1920.f * 0.7f, 1080.f * 0.7f));
		CObjectManager::GetInst()->CreateObject(pPlayerClone, GROUP_TYPE::PLAYER);
		// =============================
	*/


	Vec2 vResolution = CCore::GetInst()->GetResolution();
	
	int iEnemyCount = 15;
	float fMoveDistance = 50.f;
	float fObjectScale = 50.f;

	float fTerm = (vResolution.x - ((fMoveDistance + (fObjectScale / 2.f)) * 2)) / static_cast<float>(iEnemyCount - 1);

	for (size_t i = 0; i < iEnemyCount; i++)
	{
		// Enemy 추가
		CEnemy* pEnemy = new CEnemy;
		pEnemy->SetPos(Vec2(fMoveDistance + (fObjectScale / 2.f) + fTerm * i, 50.f));
		pEnemy->SetCenterPos(pEnemy->GetPos());
		pEnemy->SetDistance(fMoveDistance);
		pEnemy->SetScale(Vec2(fObjectScale, fObjectScale));
		CObjectManager::GetInst()->CreateObject(pEnemy, GROUP_TYPE::ENEMY);
	}

	// Camera Setting
	// CCamera::GetInst()->SetObserveObject(pPlayer1);

	// Specify Collision Check
	CCollisionManager::GetInst()->RequestInspection(GROUP_TYPE::PROJECTILE_PLAYER, GROUP_TYPE::ENEMY);
}

void CScene_Entry::SceneOut()
{
	CObjectManager::GetInst()->Reset();

	CCollisionManager::GetInst()->InspectionOff();
}

void CScene_Entry::KeyShortcut()
{
	if (__KEY_TAP(KEY::ENTER))
	{
		CSceneManager::GetInst()->RequestSubstituteScene(SCENE_TYPE::EDITOR);
	}
}

void CScene_Entry::RegisterUI(CUI* _pUI, UI_TYPE _eType)
{
}

void CScene_Entry::update()
{
	// CScene::update();
	__super::update();			// MS 전용 컴파일러에서만 동작
}
