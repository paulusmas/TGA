/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGAColorMapData.h"

TGAColorMapData::TGAColorMapData(TGAHeader* pHeader, ITGAStream* pFile)
  : TGAVariable(pHeader, pFile)
{
  m_offset = GET_COLOR_MAP_DATA_OFFSET(m_pHeader);
  m_pFile->seek(GET_COLOR_MAP_DATA_OFFSET(m_pHeader), kTGAStremOriginSet);
}

unsigned __int64 TGAColorMapData::size() const
{
  return GET_COLOR_MAP_DATA_SIZE(m_pHeader);
}