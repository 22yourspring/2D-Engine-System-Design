#include "pch.h"
#include "Object.h"

#include "Collider.h"
#include "Animator.h"
#include "Camera.h"

CObject::CObject()
	: m_vPos()
	, m_vScale()
	, m_pComponentArray{}
	, m_bEnabled(true)
	, m_bRender(true)
	, m_eColChannelInfo(GROUP_TYPE::DEFAULT)
{
}

CObject::CObject(const CObject& _Origin)
	: m_strName(_Origin.m_strName)
	, m_vPos(_Origin.m_vPos)
	, m_vScale(_Origin.m_vScale)
	, m_pComponentArray{}
	, m_eColChannelInfo(_Origin.m_eColChannelInfo)
	, m_bEnabled(true)
	, m_bRender(true)
{
	for (size_t i = 0; i < (UINT)COMPONENT_TYPE::COUNT; i++)
	{
		if (_Origin.m_pComponentArray[i])
		{
			switch (static_cast<COMPONENT_TYPE>(i))
			{
			case COMPONENT_TYPE::COLLIDER:
				m_pComponentArray[(UINT)COMPONENT_TYPE::COLLIDER] =
					new CCollider(*static_cast<CCollider*>(_Origin.m_pComponentArray[(UINT)COMPONENT_TYPE::COLLIDER]));

				m_pComponentArray[(UINT)COMPONENT_TYPE::COLLIDER]->SetOwner(this);
				break;
			case COMPONENT_TYPE::ANIMATOR:
				m_pComponentArray[(UINT)COMPONENT_TYPE::ANIMATOR] =
					new CAnimator(*static_cast<CAnimator*>(_Origin.m_pComponentArray[(UINT)COMPONENT_TYPE::ANIMATOR]));

				m_pComponentArray[(UINT)COMPONENT_TYPE::ANIMATOR]->SetOwner(this);
				break;
			}
		}
	}
}

CObject::~CObject()
{
	for (size_t i = 0; i < static_cast<UINT>(COMPONENT_TYPE::COUNT); i++)
	{
		if (m_pComponentArray[i])
			delete m_pComponentArray[i];
	}
}

void CObject::AddComponent(COMPONENT_TYPE _eType)
{
	switch (_eType)
	{
	case COMPONENT_TYPE::COLLIDER:
		m_pComponentArray[static_cast<UINT>(_eType)] = new CCollider(this);
		break;
	case COMPONENT_TYPE::ANIMATOR:
		m_pComponentArray[static_cast<UINT>(_eType)] = new CAnimator();
		break;
	}

	m_pComponentArray[static_cast<UINT>(_eType)]->m_pOwner = this;
}

void CObject::Component_update()
{
	for (size_t i = 0; i < static_cast<UINT>(COMPONENT_TYPE::COUNT); i++)
	{
		if (m_pComponentArray[i])
			m_pComponentArray[i]->Component_update();
	}
}

void CObject::render(HDC _DC)
{
}

void CObject::Component_render(HDC _DC)
{
	for (size_t i = 0; i < (UINT)COMPONENT_TYPE::COUNT; i++)
	{
		if (m_pComponentArray[i])
			m_pComponentArray[i]->Component_render(_DC);
	}
}
