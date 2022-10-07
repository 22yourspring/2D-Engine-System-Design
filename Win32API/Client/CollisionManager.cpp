#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Object.h"
#include "Collider.h"

CCollisionManager::CCollisionManager()
	: m_arrCollision{}
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::update()
{
	for (size_t iRow = 0; iRow < static_cast<UINT>(GROUP_TYPE::COUNT); iRow++)
	{
		for (size_t iCol = iRow; iCol < static_cast<UINT>(GROUP_TYPE::COUNT); iCol++)
		{
			if (IsInspection(iRow, iCol))
			{
				ChannelInspection(static_cast<GROUP_TYPE>(iRow), static_cast<GROUP_TYPE>(iCol));
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetPos();
	Vec2 vLeftScale = _pLeft->GetScale();

	Vec2 vRightPos = _pRight->GetPos();
	Vec2 vRightScale = _pRight->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::ChannelInspection(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetCollisionChannel(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetCollisionChannel(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->GetComponent(COMPONENT_TYPE::COLLIDER) == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (vecRight[j]->GetComponent(COMPONENT_TYPE::COLLIDER) == nullptr)
				continue;
			
			else if (vecLeft[i] == vecRight[j])
				continue;

			// Create Collder Left, Right
			CCollider* pLeft = ((CCollider*)vecLeft[i]->GetComponent(COMPONENT_TYPE::COLLIDER));
			CCollider* pRight = ((CCollider*)vecRight[j]->GetComponent(COMPONENT_TYPE::COLLIDER));


			// Create Collision Info
			COLLIDER_INFO Info;
			Info.iLeft_ID = pLeft->GetID();
			Info.iRight_ID = pRight->GetID();

			iter = m_mapColInfo.find(Info.CollisionID);

			// First Check
			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(Info.CollisionID, false));
				iter = m_mapColInfo.find(Info.CollisionID);
			}
			
			// Current Collision
			if (IsCollision(pLeft, pRight))
			{	
				// Prev Collision
				if (iter->second)
				{
					// Disable Object Exception
					if (!vecLeft[i]->IsEnable() || !vecRight[j]->IsEnable())
					{
						pLeft->OnCollisionOut(pRight);
						pRight->OnCollisionOut(pLeft);

						iter->second = false;
					}
					else
					{
						pLeft->OnCollision(pRight);
						pRight->OnCollision(pLeft);
					}					
				}
				// Prev NonCollision
				else
				{
					// Disable Object Exception
					if (vecLeft[i]->IsEnable() && vecRight[j]->IsEnable())
					{
						pLeft->OnCollisionIn(pRight);
						pRight->OnCollisionIn(pLeft);

						iter->second = true;
					}
				}
			}
			// Current NonCollision
			else
			{		
				// Prev Collision
				if (iter->second)
				{
					pLeft->OnCollisionOut(pRight);
					pRight->OnCollisionOut(pLeft);

					iter->second = false;
				}
			}
			
		}
	}
}

void CCollisionManager::RequestInspection(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow, iCol;

	if (_eLeft < _eRight)
	{
		iRow = static_cast<UINT>(_eLeft);
		iCol = static_cast<UINT>(_eRight);
	}
	else
	{
		iRow = static_cast<UINT>(_eRight);
		iCol = static_cast<UINT>(_eLeft);
	}
	
	if (m_arrCollision[iRow] & (1 << iCol))
		m_arrCollision[iRow] &= ~(1 << iCol);

	else
		m_arrCollision[iRow] |= (1 << iCol);
}