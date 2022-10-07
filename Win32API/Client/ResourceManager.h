#pragma once

class CRes;
class CTexture;
class CSound;
class CResourceManager
{
	SINGLE(CResourceManager);

private:
	map<wstring, CRes*>		m_mapTexture;
	map<wstring, CRes*>		m_mapSound;

public:
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture*	FindTexture(const wstring& _strKey);

	CSound*		LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound*		FindSound(const wstring& _strKey);

public:
	inline void ClearResource();
};

