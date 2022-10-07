#pragma once
#include "UI.h"
class CCanvasUI :
    public CUI
{
public:
	CCanvasUI(bool _bRenderAffected = false);
    virtual ~CCanvasUI() override;

public:
	CLONE(CCanvasUI);

private:
	Vec2	m_vDragPos;

public:
	virtual void MouseHovered() override;

	virtual void MouseLPressed() override;
	virtual void MouseLReleased() override;
	virtual void MouseLClicked() override;

	virtual void MouseRPressed() override;
	virtual void MouseRReleased() override;
	virtual void MouseRClicked() override;
};

