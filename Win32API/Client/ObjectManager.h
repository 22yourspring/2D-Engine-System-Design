#pragma once
class CObject;
class CScene;
class CObjectManager final
{
	SINGLE(CObjectManager);

private:
	CScene*		m_pScene;

public:
	void CreateObject(CObject* _pObject, GROUP_TYPE _eType);
	void DeleteGroup(GROUP_TYPE _eType);
	void Reset();

public:
	void RequestCreate(CObject* _pObject, GROUP_TYPE _eGroup);
	void RequestDelete(CObject* _pObject);
};

