#include "pch.h"
#include "ButtonUI.h"

CButtonUI::CButtonUI(bool _bRenderAffected)
	: CUI(_bRenderAffected)
	, m_pLFunc{}
	, m_pRFunc{}
	, m_eLEnable(ENABLE_FUNC::DISABLE)
	, m_eREnable(ENABLE_FUNC::DISABLE)
{
	// __AddDynamic_MULTICAST_SET_CALLBACK_0PARAM(this, std::bind(&CButtonUI::MouseRReleased, this));
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::SetCallBack_0Param(__FUNCTION_PTR_0PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton)
{
	switch (_eButton)
	{
	case FUNCTION_REGISTER_BUTTON::LBUTTON:
		m_pLFunc.pFuncPtr_0Param = _pFunc;

		m_eLEnable = ENABLE_FUNC::NULL_PARAM;
		break;
	case FUNCTION_REGISTER_BUTTON::RBUTTON:
		m_pRFunc.pFuncPtr_0Param = _pFunc;

		m_eREnable = ENABLE_FUNC::NULL_PARAM;
		break;
	}
}

void CButtonUI::SetCallBack_1Param(__FUNCTION_PTR_1PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1)
{
	switch (_eButton)
	{
	case FUNCTION_REGISTER_BUTTON::LBUTTON:
		m_pLFunc.pFuncPtr_1Param = _pFunc;
		m_pLFunc.param1 = _param1;

		m_eLEnable = ENABLE_FUNC::ONE_PARAM;
		break;
	case FUNCTION_REGISTER_BUTTON::RBUTTON:
		m_pRFunc.pFuncPtr_1Param = _pFunc;
		m_pRFunc.param1 = _param1;

		m_eREnable = ENABLE_FUNC::ONE_PARAM;
		break;
	}
}

void CButtonUI::SetCallBack_2Param(__FUNCTION_PTR_2PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1, DWORD_PTR _param2)
{
	switch (_eButton)
	{
	case FUNCTION_REGISTER_BUTTON::LBUTTON:
		m_pLFunc.pFuncPtr_2Param = _pFunc;
		m_pLFunc.param1 = _param1;
		m_pLFunc.param2 = _param2;

		m_eLEnable = ENABLE_FUNC::TWO_PARAM;
		break;
	case FUNCTION_REGISTER_BUTTON::RBUTTON:
		m_pRFunc.pFuncPtr_2Param = _pFunc;
		m_pRFunc.param1 = _param1;
		m_pRFunc.param2 = _param2;

		m_eREnable = ENABLE_FUNC::TWO_PARAM;
		break;
	}
}

void CButtonUI::SetCallBack_3Param(__FUNCTION_PTR_3PARAM _pFunc, FUNCTION_REGISTER_BUTTON _eButton, DWORD_PTR _param1, DWORD_PTR _param2, DWORD_PTR _param3)
{
	switch (_eButton)
	{
	case FUNCTION_REGISTER_BUTTON::LBUTTON:
		m_pLFunc.pFuncPtr_3Param = _pFunc;
		m_pLFunc.param1 = _param1;
		m_pLFunc.param2 = _param2;
		m_pLFunc.param3 = _param3;

		m_eLEnable = ENABLE_FUNC::THREE_PARAM;
		break;
	case FUNCTION_REGISTER_BUTTON::RBUTTON:
		m_pRFunc.pFuncPtr_3Param = _pFunc;
		m_pRFunc.param1 = _param1;
		m_pRFunc.param2 = _param2;
		m_pRFunc.param3 = _param3;

		m_eREnable = ENABLE_FUNC::THREE_PARAM;
		break;
	}
}

void CButtonUI::MouseHovered()
{
}

void CButtonUI::MouseLPressed()
{
}

void CButtonUI::MouseLReleased()
{
}

void CButtonUI::MouseLClicked()
{
	switch (m_eLEnable)
	{
	case ENABLE_FUNC::NULL_PARAM:
		m_pLFunc.pFuncPtr_0Param();
		break;
	case ENABLE_FUNC::ONE_PARAM:
		m_pLFunc.pFuncPtr_1Param(m_pLFunc.param1);
		break;
	case ENABLE_FUNC::TWO_PARAM:
		m_pLFunc.pFuncPtr_2Param(m_pLFunc.param1, m_pLFunc.param2);
		break;
	case ENABLE_FUNC::THREE_PARAM:
		m_pLFunc.pFuncPtr_3Param(m_pLFunc.param1, m_pLFunc.param2, m_pLFunc.param3);
		break;
	}

	// __DELEGATE_SINGLECAST();
	// __DELEGATE_MULTICAST();
}

void CButtonUI::MouseRPressed()
{
}

void CButtonUI::MouseRReleased()
{
}

void CButtonUI::MouseRClicked()
{
	switch (m_eREnable)
	{
	case ENABLE_FUNC::NULL_PARAM:
		m_pRFunc.pFuncPtr_0Param();
		break;
	case ENABLE_FUNC::ONE_PARAM:
		m_pRFunc.pFuncPtr_1Param(m_pRFunc.param1);
		break;
	case ENABLE_FUNC::TWO_PARAM:
		m_pRFunc.pFuncPtr_2Param(m_pRFunc.param1, m_pRFunc.param2);
		break;
	case ENABLE_FUNC::THREE_PARAM:
		m_pRFunc.pFuncPtr_3Param(m_pRFunc.param1, m_pRFunc.param2, m_pRFunc.param3);
		break;
	}
}
