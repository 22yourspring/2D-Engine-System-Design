#pragma once

union COLLIDER_INFO
{
	struct  
	{
		UINT iLeft_ID;
		UINT iRight_ID;
	};
	ULONGLONG	CollisionID;
};

class CCollider;
class CCollisionManager
{
	SINGLE(CCollisionManager)

private:
	UINT	m_arrCollision[static_cast<UINT>(GROUP_TYPE::COUNT)];		// CollisionChannel Matrix
	map<ULONGLONG, bool> m_mapColInfo;

private:
	inline bool IsInspection(UINT iRow, UINT iCol) { return m_arrCollision[iRow] & (1 << iCol); }
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	void ChannelInspection(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

public:
	void RequestInspection(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	inline void InspectionOff() { ZeroMemory(m_arrCollision, sizeof(UINT) * static_cast<UINT>(GROUP_TYPE::COUNT)); }

public:
	void update();
};

