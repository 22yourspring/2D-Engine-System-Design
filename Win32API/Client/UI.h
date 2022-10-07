#pragma once
#include "Object.h"
class CUI :
    public CObject
{
public:
    CUI(bool _bRenderAffected);
    CUI(const CUI& _Origin);
    virtual ~CUI() override;

	friend class CUIManager;

private:
	vector<CUI*>	m_vecChildUI;
	CUI*			m_pParentUI;
	Vec2			m_vAppliedPos;

	bool			m_bRenderAffected;
	bool			m_bMouseHovered;

	bool			m_bLPressed;
	bool			m_bRPressed;

public:
	inline CUI* GetParent() { return m_pParentUI; }
	inline void AddChildUI(CUI* _pUI);
	inline vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	inline void SetAppliedPos();
	inline Vec2 GetAppliedPos() { return m_vAppliedPos; }

	inline bool IsHovered() { return m_bMouseHovered; }
	inline bool IsLPressed() { return m_bLPressed; }
	inline bool IsRPressed() { return m_bRPressed; }

public:
	void HoveredConfirm();

public:
	virtual void MouseHovered() = 0;
	
	virtual void MouseLPressed() = 0;
	virtual void MouseLReleased() = 0;
	virtual void MouseLClicked() = 0;

	virtual void MouseRPressed() = 0;
	virtual void MouseRReleased() = 0;
	virtual void MouseRClicked() = 0;

private:
	void update_UI();
	void render_UI(HDC _DC);
	void Component_update_UI();

public:
	virtual CUI* Clone() = 0;

public:
	virtual void update() override;
	virtual void render(HDC _DC) override;
	virtual void Component_update() override;
};

