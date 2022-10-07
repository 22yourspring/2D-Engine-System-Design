#pragma once
#include "UI.h"
class CButtonUI :
    public CUI
{
public:
    CButtonUI(bool _bRenderAffected = false);
    virtual ~CButtonUI() override;

public:
	CLONE(CButtonUI);

	// __DECLARE_SINGLECAST_DELEGATE_Param();
	// __DECLARE_MULTICAST_DELEGATE_Param();

public:
	__FUNCTION		m_pLFunc;
	__FUNCTION		m_pRFunc;

	ENABLE_FUNC		m_eLEnable;
	ENABLE_FUNC		m_eREnable;

public:
	void SetCallBack_0Param(__FUNCTION_PTR_0PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton);
	void SetCallBack_1Param(__FUNCTION_PTR_1PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1);
	void SetCallBack_2Param(__FUNCTION_PTR_2PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1, DWORD_PTR _param2);
	void SetCallBack_3Param(__FUNCTION_PTR_3PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1, DWORD_PTR _param2, DWORD_PTR _param3);

public:
	virtual void MouseHovered() override;

	virtual void MouseLPressed() override;
	virtual void MouseLReleased() override;
	virtual void MouseLClicked() override;

	virtual void MouseRPressed() override;
	virtual void MouseRReleased() override;
	virtual void MouseRClicked() override;
};

