#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Tile.h"

#include "ObjectManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PathManager.h"


CScene::CScene()
	: m_iTileMaxRow(0)
	, m_iTileMaxCol(0)
	, m_arrUI{}
{
}

CScene::~CScene()
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::COUNT); i++)
	{
		for (size_t j = 0; j < m_arrObject[i].size(); j++)
		{
			delete m_arrObject[i][j];
		}
	}
}

void CScene::AddObject(CObject* _pObject, GROUP_TYPE _eType)
{
	_pObject->SetCollisionChannelInfo(_eType);
	m_arrObject[(UINT)_eType].push_back(_pObject);
}

void CScene::DeleteGroup(GROUP_TYPE _eType)
{
	// Safe_Delete_Vec(m_arrObject[static_cast<UINT>(_eType)]);
	Safe_Delete_Vec<CObject*>(m_arrObject[static_cast<UINT>(_eType)]);
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount, const wstring& _strPath)
{
	if (_strPath.empty())
	{
		MessageBox(nullptr, L"Failed to Load Path", L"Error", MB_OK);
		return;
	}

	CObjectManager::GetInst()->DeleteGroup(GROUP_TYPE::TILE);

	m_strTileResourcePath = _strPath;
	m_strTileResourcePath = CPathManager::GetInst()->GetRelativePath(m_strTileResourcePath);

	m_iTileMaxRow = _iYCount;
	m_iTileMaxCol = _iXCount;

	wstring strKey = CPathManager::GetInst()->GetPathtoKey(_strPath);
	CTexture* pTileTexture = CResourceManager::GetInst()->LoadTexture(strKey, m_strTileResourcePath);

	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTexture);

			CObjectManager::GetInst()->CreateObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::SaveTile(const wstring& _strTilePath)
{
	FILE* pFile;
	_wfopen_s(&pFile, _strTilePath.c_str(), L"wb");

	assert(pFile);

	UINT iXCount = GetTileMaxCol();
	UINT iYCount = GetTileMaxRow();

	fwrite(&iXCount, sizeof(UINT), 1, pFile);
	fwrite(&iYCount, sizeof(UINT), 1, pFile);
	fwrite(m_strTileResourcePath.c_str(), sizeof(WCHAR), PATH_LIMIT, pFile);

	const vector<CObject*> vecTile = GetObjectGroup(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->SaveTile(pFile);
	}

	fclose(pFile);
}

void CScene::LoadTile(const wstring& strRelativePath)
{
	FILE* pFile;
	_wfopen_s(&pFile, strRelativePath.c_str(), L"rb");
	
	assert(pFile);

	UINT iXCount;
	UINT iYCount;

	fread(&iXCount, sizeof(UINT), 1, pFile);
	fread(&iYCount, sizeof(UINT), 1, pFile);

	// wstring으로 해결 X
	WCHAR szResourcePath[PATH_LIMIT] = {};
	fread(szResourcePath, sizeof(WCHAR), PATH_LIMIT, pFile);

	CreateTile(iXCount, iYCount, CPathManager::GetInst()->GetAbsolutePath(szResourcePath));

	const vector<CObject*> vecTile = GetObjectGroup(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->LoadTile(pFile);
	}

	fclose(pFile);
}

void CScene::update()
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::COUNT); i++)
	{
		for (size_t j = 0; j < m_arrObject[i].size(); j++)
		{
			if (m_arrObject[i][j]->IsEnable())
				m_arrObject[i][j]->update();			
		}
	}
}

void CScene::Component_update()
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::COUNT); i++)
	{
		for (size_t j = 0; j < m_arrObject[i].size(); j++)
		{
			m_arrObject[i][j]->Component_update();
		}
	}
}

void CScene::render(HDC _DC)
{
	for (size_t i = 0; i < static_cast<UINT>(GROUP_TYPE::COUNT); i++)
	{
		vector<CObject*>::iterator iter = m_arrObject[i].begin();

		for (; iter < m_arrObject[i].end();)
		{
			if ((*iter)->IsEnable())
			{
				if ((*iter)->IsRender())
				{
					(*iter)->render(_DC);
					(*iter)->Component_render(_DC);
				}

				iter++;
			}
			else
			{
				iter = m_arrObject[i].erase(iter);
			}
		}
	}
}