#pragma once
class CPathManager
{
	SINGLE(CPathManager);

private:
	wchar_t		m_szContentPath[PATH_LIMIT];

public:
	wstring GetPathtoKey(const wstring& _strAbsolutePath);

	wstring GetRelativePath(const wstring& _strAbsolutePath);
	wstring GetAbsolutePath(const wstring& _strRelativePath);

	const wchar_t* GetContentPath() { return m_szContentPath; }

public:
	void init();
};

