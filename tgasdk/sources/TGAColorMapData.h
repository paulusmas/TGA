/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

#include "TGAVariable.h"
#include "TGAExports.h"

class TGAColorMapData : public TGAVariable
{
public:
  TGAColorMapData(TGAHeader* pHeader, ITGAStream* pFile);

  unsigned __int64 size() const;
};