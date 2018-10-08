/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGAVariable.h"

TGAVariable::TGAVariable(TGAHeader* pHeader, ITGAStream* pFile)
  : m_pHeader(pHeader)
  , m_pFile(pFile)
{
  if (!m_pHeader)
      throw TGAError("Header is NULL", eTGAResult_NULLObject);
  if (!m_pFile)
    throw TGAError("File is NULL", eTGAResult_NULLObject);
  m_pos = 0;
  m_offset = 0;
}

TGAVariable::~TGAVariable()
{
  m_pHeader = 0;
  m_pFile = 0;
  m_pos = 0;
  m_offset = 0;
}

void TGAVariable::read(void* pBuf, unsigned __int64 sizeBlock)
{
  unsigned __int64 curPos_f = m_pFile->tell();
  unsigned __int64 curPos_varable = m_offset + m_pos;

  if (curPos_f != curPos_varable)
    m_pFile->seek(curPos_varable, kTGAStremOriginSet);

  unsigned __int64 chunk = size() - m_pos;
  if (sizeBlock > chunk)
    throw TGAError("sizeBlock out of range", eTGAResult_ReadBlockFail);
  int read = m_pFile->read(pBuf, sizeBlock);
  if (read != sizeBlock)
    throw TGAError("TAGVariable::read has been failed", eTGAResult_ReadBlockFail);
  m_pos += sizeBlock;

  if (curPos_f != curPos_varable)
    m_pFile->seek(curPos_f, kTGAStremOriginSet);
}
