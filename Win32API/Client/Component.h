#pragma once
class CObject;
class CComponent
{
public:
	CComponent();
	virtual ~CComponent();

	friend class CObject;

private:
	CObject*	m_pOwner;

public:
	CObject*	Object() const { return m_pOwner; }
	void		SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }

public:
	virtual void Component_update() {}
	virtual void Component_render(HDC _DC) {}
};

