#include "pch.h"
#include "Destructible.h"

CDestructible::CDestructible()
	: m_iHP(0)
{
}

CDestructible::~CDestructible()
{
}

void CDestructible::Component_update()
{
	// CObject::Component_update();
	__super::Component_update();
}
