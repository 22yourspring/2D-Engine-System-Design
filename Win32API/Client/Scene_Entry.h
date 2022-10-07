#pragma once
#include "Scene.h"

class CScene_Entry :
	public CScene
{
public:
	CScene_Entry();
	virtual ~CScene_Entry() override;

public:
	virtual void SceneIn() override;
	virtual void SceneOut() override;

	virtual void KeyShortcut() override;
	virtual void RegisterUI(CUI* _pUI, UI_TYPE _eType);

public:
	virtual void update() override;
};

