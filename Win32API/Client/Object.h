#pragma once

class CComponent;
class CCollider;
class CAnimator;
class CObject
{
public:
	CObject();
	explicit CObject(const CObject& _Origin);
	virtual ~CObject();

	friend class CEventManager;

private:
	wstring			m_strName;

	Vec2			m_vPos;
	Vec2			m_vScale;

	bool			m_bEnabled;
	bool			m_bRender;
	GROUP_TYPE		m_eColChannelInfo;

	CComponent* m_pComponentArray[static_cast<UINT>(COMPONENT_TYPE::COUNT)];

private:
	void SetEnable(bool _Set) { m_bEnabled = _Set; }

public:
	bool IsEnable() { return m_bEnabled; }
	bool IsRender() { return m_bRender; }
	void SetRender(bool _bRender) { m_bRender = _bRender; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	Vec2 GetPos() const { return m_vPos; }

	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetScale() const { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CComponent* GetComponent(COMPONENT_TYPE _eType) { return m_pComponentArray[static_cast<UINT>(_eType)]; }
	CCollider* GetCollider() { return (CCollider*)m_pComponentArray[(UINT)COMPONENT_TYPE::COLLIDER]; }
	CAnimator* GetAnimator() { return (CAnimator*)m_pComponentArray[(UINT)COMPONENT_TYPE::ANIMATOR]; }

public:
	void SetCollisionChannelInfo(GROUP_TYPE _eType) { m_eColChannelInfo = _eType; }
	GROUP_TYPE	GetCollisionChannelInfo() { return m_eColChannelInfo; }

protected:
	virtual CObject* Clone() = 0;

public:
	void AddComponent(COMPONENT_TYPE _eType);

public:
	virtual inline void OnCollisionIn(CCollider* _pOther) {}
	virtual inline void OnCollision(CCollider* _pOther) {}
	virtual inline void OnCollisionOut(CCollider* _pOther) {}

public:
	virtual void update() = 0;
	virtual void render(HDC _DC) = 0;

	virtual void Component_update();
	void Component_render(HDC _DC);
};

