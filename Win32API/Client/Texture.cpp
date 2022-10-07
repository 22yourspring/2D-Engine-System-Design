#include "pch.h"
#include "Texture.h"
#include "Core.h"

CTexture::CTexture()
	: m_hBit(NULL)
	, m_hDC(NULL)
	, m_tBitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void CTexture::LoadResource(const wstring& _strFilePath)
{
	// Create a bitmap from a loaded file
	m_hBit = static_cast<HBITMAP>(LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_LOADFROMFILE));

	assert(m_hBit);

	// DC to associate with the bitmap
	m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// Connect bitmap and DC
	HBITMAP hPrevBitMap =  static_cast<HBITMAP>(SelectObject(m_hDC, m_hBit));
	DeleteObject(hPrevBitMap);

	// BitMap Info
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitInfo);
}
