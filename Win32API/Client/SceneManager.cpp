#include "pch.h"
#include "SceneManager.h"
#include "Scene_Entry.h"
#include "Scene_Editor.h"

CSceneManager::CSceneManager()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	// Scene
	for (size_t i = 0; i < static_cast<UINT>(SCENE_TYPE::COUNT); i++)
	{
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];		
	}
}

void CSceneManager::SubstituteScene(SCENE_TYPE _eNextScene)
{
	m_pCurScene->SceneOut();
	
	m_pCurScene = m_arrScene[static_cast<UINT>(_eNextScene)];

	m_pCurScene->SceneIn();
}

void CSceneManager::init()
{
	// Create Scene
	m_arrScene[static_cast<UINT>(SCENE_TYPE::ENTRY)] = new CScene_Entry;
	m_arrScene[static_cast<UINT>(SCENE_TYPE::ENTRY)]->SetName(L"Entry Scene");

	m_arrScene[static_cast<UINT>(SCENE_TYPE::EDITOR)] = new CScene_Editor;
	m_arrScene[static_cast<UINT>(SCENE_TYPE::EDITOR)]->SetName(L"Editor Scene");

	//m_arrScene[static_cast<UINT>(SCENE_TYPE::STAGE1)] = new CScene_Stage1;
	//m_arrScene[static_cast<UINT>(SCENE_TYPE::STAGE2)] = new CScene_Stage2;

	// Current Scene Setting
	m_pCurScene = m_arrScene[static_cast<UINT>(SCENE_TYPE::EDITOR)];
	m_pCurScene->SceneIn();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->Component_update();
	m_pCurScene->KeyShortcut();
}

void CSceneManager::render(HDC _DC)
{
	m_pCurScene->render(_DC);
}