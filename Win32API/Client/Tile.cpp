#include "pch.h"
#include "Tile.h"

#include "Camera.h"

#include "Texture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImageIdx(0)
	, m_iMaxCol(0)
	, m_iMaxRow(0)
	, m_iCurColIdx(0)
	, m_iCurRowIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

inline void CTile::PrevImageIdx()
{
	if (m_iImageIdx <= 0)
	{
		m_iImageIdx = (m_iMaxCol * m_iMaxRow) - 1;
	}
	else
	{
		m_iImageIdx--;
	}
}

inline void CTile::NextImageIdx()
{
	if (m_iImageIdx < (m_iMaxCol * m_iMaxRow) - 1)
	{
		m_iImageIdx++;
	}
	else
	{
		m_iImageIdx = 0;
	}
}

void CTile::SaveTile(FILE* _pFile)
{
	fwrite(&m_iImageIdx, sizeof(int), 1, _pFile);
}

void CTile::LoadTile(FILE* _pFile)
{
	fread(&m_iImageIdx, sizeof(int), 1, _pFile);
}

void CTile::update()
{
}

void CTile::render(HDC _DC)
{
	if (!m_pTileTex)
		return;

	UINT iWidth = m_pTileTex->GetWidth();
	UINT iHeight = m_pTileTex->GetHeight();

	m_iMaxCol = iWidth / TILE_SIZE;
	m_iMaxRow = iHeight / TILE_SIZE;

	m_iCurColIdx = m_iImageIdx % m_iMaxCol;
	m_iCurRowIdx = m_iImageIdx / m_iMaxCol;


	// Image Index overflow
	if (m_iMaxRow <= m_iCurRowIdx)
		assert(nullptr);


	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_DC 
		, static_cast<int>(vRenderPos.x)
		, static_cast<int>(vRenderPos.y)
		, static_cast<int>(GetScale().x)
		, static_cast<int>(GetScale().y)
		, m_pTileTex->GetDC()
		, m_iCurColIdx * TILE_SIZE
		, m_iCurRowIdx * TILE_SIZE
		, SRCCOPY);
}
