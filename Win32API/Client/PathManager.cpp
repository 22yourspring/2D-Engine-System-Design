#include "pch.h"
#include "PathManager.h"

#include "Core.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Scene_Editor.h"

CPathManager::CPathManager()
	: m_szContentPath{}
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::init()
{
	GetCurrentDirectory(PATH_LIMIT, m_szContentPath);
	
	int iLen = static_cast<int>(wcslen(m_szContentPath));

	for (int i = iLen - 1; 0 <= i; i--)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, PATH_LIMIT, L"\\bin\\Content\\");
}

wstring CPathManager::GetPathtoKey(const wstring& _strAbsolutePath)
{
	wstring strKey = _strAbsolutePath;

	int iLen = static_cast<int>(wcslen(_strAbsolutePath.c_str()));

	for (int i = iLen - 1; 0 <= i; i--)
	{
		if (strKey[i] == '.')
		{
			strKey[i] = '\0';
			break;
		}
	}

	wstring::iterator iter = strKey.end() - 1;
	for (; iter != strKey.begin(); iter--)
	{
		if (*iter == '\\')
		{
			strKey.erase(strKey.begin(), iter + 1);
			break;
		}
	}

	return strKey;
}

wstring CPathManager::GetRelativePath(const wstring& _strAbsolutePath)
{
	wstring strRelativePath = _strAbsolutePath;

	assert(strRelativePath.find(L"Content\\") != wstring::npos);

	int iIdx = strRelativePath.find(L"Content\\");
	iIdx += wstring(L"Content\\").length();

	strRelativePath.erase(0, iIdx);

	// 우클릭 경로복사
	if (strRelativePath.c_str()[strRelativePath.length() - 1] == L'\"')
	{
		strRelativePath.erase(strRelativePath.length() - 1);
	}

	return strRelativePath;
}

wstring CPathManager::GetAbsolutePath(const wstring& _strRelativePath)
{
	wstring strContentPath = GetContentPath();
	return strContentPath + _strRelativePath;
}
