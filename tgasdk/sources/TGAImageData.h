/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

#include "TGAVariable.h"

class TGAImageData : protected TGAVariable
{
public:
  TGAImageData(TGAHeader* pHeader, ITGAStream* pFile);

  unsigned __int64 size() const;

  void read(void* pBuf);

protected:
  void readRLE(void* pBuf);
};