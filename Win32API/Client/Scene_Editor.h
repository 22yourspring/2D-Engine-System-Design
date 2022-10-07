#pragma once
#include "Scene.h"

class CUI;
class CScene_Editor :
	public CScene
{
public:
	CScene_Editor();
	virtual ~CScene_Editor() override;

public:
	void SetTileIdx();

public:
	virtual void SceneIn() override;
	virtual void SceneOut() override;

	virtual void KeyShortcut() override;
	virtual void RegisterUI(CUI* _pUI, UI_TYPE _eType);

public:
	virtual void update() override;
};

