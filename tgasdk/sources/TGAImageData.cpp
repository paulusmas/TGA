/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGAImageData.h"

#include <vector>

TGAImageData::TGAImageData(TGAHeader* pHeader, ITGAStream* pFile)
  : TGAVariable(pHeader, pFile)
{
  m_offset = GET_IMAGE_DATA_OFFSET(m_pHeader);
  m_pFile->seek(GET_IMAGE_DATA_OFFSET(m_pHeader), kTGAStremOriginSet);
}

unsigned __int64 TGAImageData::size() const
{
  return GET_IMAGE_DATA_SIZE(m_pHeader);
}

void TGAImageData::read(void* pBuf)
{
  if (m_pHeader->field().isEncoded())
    return readRLE(pBuf);
  __super::read(pBuf, size());
}

/////////////////////////////////////////////////////////////////////
//code below like TGA library (libtga) 2001-2002, Matthias Brueckner
//
void TGAImageData::readRLE(void* pBuf)
{
  unsigned __int8 head;
  unsigned __int8 vBlock[4];
  unsigned __int8 repeat = 0, direct = 0, sizeBlock = m_pHeader->image_specification().pixel_depth / 8;

  unsigned __int8* buf = (unsigned __int8*)pBuf;
  

  for (unsigned i = 0, n = (unsigned)m_pHeader->image_specification().width * m_pHeader->image_specification().height; i < n; ++i)
  {
    if (repeat == 0 && direct == 0)
    {
      int r = m_pFile->read(&head, 1);
      if (r != 1) 
        throw TGAError("readRLE has been fail", eTGAResult_BadStructure);
      if (head >= 128) 
      {
        repeat = head - 127;
        int r = m_pFile->read(vBlock, sizeBlock);
        if (r != sizeBlock)
          throw("readRLE has been fail", eTGAResult_BadStructure);
      }
      else
      {
        direct = head + 1;
      }
    }
    if (repeat > 0)
    {
      memcpy(buf, vBlock, sizeBlock);
      --repeat;
    }
    else
    {
      int r = m_pFile->read(buf, sizeBlock);
      if (r != sizeBlock)
        throw("readRLE has been fail", eTGAResult_BadStructure);
      --direct;
    }
    buf += sizeBlock;
  }
}