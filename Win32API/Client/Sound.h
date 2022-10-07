#pragma once
#include "Res.h"
class CSound :
    public CRes
{
private:
    CSound();
    virtual ~CSound() override;

	virtual void LoadResource(const wstring& _strFilePath) override;
};

