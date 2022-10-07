#include "pch.h"
#include "ResourceManager.h"

#include "PathManager.h"
#include "Texture.h"
#include "Sound.h"

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
    ClearResource();
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTexture = FindTexture(_strKey);

    if (pTexture)
        return pTexture;
    

    wstring strFilePath = CPathManager::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    pTexture = new CTexture;
    pTexture->LoadResource(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    m_mapTexture.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
    map<wstring, CRes*>::iterator iter = m_mapTexture.find(_strKey);

    if (iter == m_mapTexture.end())
        return nullptr;

    return dynamic_cast<CTexture*>(iter->second);
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    return nullptr;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
    return nullptr;
}

inline void CResourceManager::ClearResource()
{
	/*
    	map<wstring, CTexture*>::iterator Texture_iter = m_mapTexture.begin();
		for (; Texture_iter != m_mapTexture.end(); Texture_iter++)
		{
			delete Texture_iter->second;
		}

		map<wstring, CSound*>::iterator Sound_iter = m_mapSound.begin();
		for (; Sound_iter != m_mapSound.end(); Sound_iter++)
		{
			delete Sound_iter->second;
		}
    */    

    /*
	    Safe_Delete_Map(m_mapTexture);
	    Safe_Delete_Map(m_mapSound);
    */

    Safe_Delete_Map<wstring, CRes*>(m_mapTexture);
    Safe_Delete_Map<wstring, CRes*>(m_mapSound);
}
