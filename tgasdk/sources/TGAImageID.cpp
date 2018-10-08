/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGAImageID.h"

TGAImageID::TGAImageID(TGAHeader* pHeader, ITGAStream* pFile)
  : TGAVariable(pHeader, pFile) 
{
  m_offset = GET_IMAGE_ID_OFFSET(m_pHeader);
  m_pFile->seek(GET_IMAGE_ID_OFFSET(m_pHeader), kTGAStremOriginSet);
}

unsigned __int64 TGAImageID::size() const
{
  return GET_IMAGE_ID_SIZE(m_pHeader);
}