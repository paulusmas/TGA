/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once
#include "TGAFile.h"
#include "TGAError.hpp"

#include <vector>

template <class __TAG>
struct TAG
{
  static const size_t size = sizeof(__TAG);
};

class TGAFiler
{
public:
  TGAFiler() { }
  ~TGAFiler() { }

  void read(ITGAStream* pFile)
  {
    std::vector<unsigned __int8> vBuf;
    size_t size = sizeSection();
    if (!size)
      return;
    vBuf.resize(size);
    pFile->seek(beginSection(), kTGAStremOriginSet);
    int r = pFile->read(&vBuf[0], size);
    if (r != size)
      throw TGAError("Bad structure", eTGAResult_BadStructure);
    subRead(&vBuf[0]);
  }
protected:
  virtual size_t  beginSection()  const               = 0;
  virtual size_t  sizeSection()   const               = 0;
  virtual void    subRead(unsigned __int8* pBuffer)   = 0;
};