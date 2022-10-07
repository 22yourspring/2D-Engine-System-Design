#pragma once

class CScene;
class CSceneManager final
{
	SINGLE(CSceneManager);

	friend class CEventManager;

private:
	CScene* m_arrScene[static_cast<UINT>(SCENE_TYPE::COUNT)];
	CScene* m_pCurScene;

public:
	inline CScene* GetCurScene() { return m_pCurScene; }
	
	template <typename T>
	inline void RequestSubstituteScene(T _eType);

private:
	void	SubstituteScene(SCENE_TYPE _eNextScene);

public:
	void init();
	void update();
	void render(HDC	_DC);
};
#include "SceneManager.inl"