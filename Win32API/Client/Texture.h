#pragma once
#include "Res.h"
class CTexture :
    public CRes
{
private:
    CTexture();
    virtual ~CTexture() override;

	friend class CResourceManager;

private:
    HDC         m_hDC;
    HBITMAP     m_hBit;
    BITMAP      m_tBitInfo;

public:
    UINT GetWidth() { return m_tBitInfo.bmWidth; }
    UINT GetHeight() { return m_tBitInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }

public:
	virtual void LoadResource(const wstring& _strFilePath) override;
};