/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once
#include "TGAHeader.h"
#include "TGAFile.h"
#include "TGAError.hpp"

class TGAVariable
{
protected:
  TGAHeader         *m_pHeader;
  ITGAStream        *m_pFile;
  unsigned __int64  m_pos;
  unsigned __int64  m_offset;

public:
  virtual ~TGAVariable();

protected:
  TGAVariable(TGAHeader* pHeader, ITGAStream* pFile);

public:
  void read(void* pBuf, unsigned __int64 sizeBlock);

  virtual unsigned __int64 size() const = 0;
};
