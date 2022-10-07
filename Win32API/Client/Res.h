#pragma once
class CRes
{
public:
	CRes();
	virtual ~CRes();

private:
	wstring		m_strKey;				// Resource Key
	wstring		m_strRelativePath;		// 절대경로(Absolute path) X		상대경로(Relative path) O

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }

	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	virtual void LoadResource(const wstring& _strFilePath) = 0;
};

