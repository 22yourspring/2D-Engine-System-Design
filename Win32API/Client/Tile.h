#pragma once
#include "Object.h"

class CTexture;
class CTile :
    public CObject
{
public:
    CTile();
    virtual ~CTile() override;

public:
	CLONE(CTile);

private:
    CTexture*   m_pTileTex;
    int         m_iImageIdx;

	UINT        m_iMaxCol;
	UINT        m_iMaxRow;
	UINT        m_iCurColIdx;
	UINT        m_iCurRowIdx;

public:
    inline void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }

    inline void PrevImageIdx();
    inline void NextImageIdx();

public:
    virtual void SaveTile(FILE* _pFile);
    virtual void LoadTile(FILE* _pFile);

	virtual void update() override;
    virtual void render(HDC _DC) override;
};

