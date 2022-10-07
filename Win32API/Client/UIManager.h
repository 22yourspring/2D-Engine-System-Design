#pragma once
class CUI;
class CUIManager
{
	SINGLE(CUIManager);

private:
	CUI* m_pFocusedUI;

public:
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetPickedUI(CUI* _pParentUI);

private:
	void ProcessPickedUI();

public:
	void update();
};

