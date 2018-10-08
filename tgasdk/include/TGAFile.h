/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

enum TGAStremOrigin
{
  kTGAStremOriginSet = 0,
  kTGAStremOriginCur = 1,
  kTGAStremOriginEnd = 2
};
struct ITGAStream
{
  virtual int read(void* pBuffer,
    int sizeBlock) = 0;

  virtual int seek(__int64 offset,
    TGAStremOrigin SeekMethod) = 0;

  virtual unsigned __int64 tell() = 0;

  virtual unsigned __int64 size() const = 0;
};
