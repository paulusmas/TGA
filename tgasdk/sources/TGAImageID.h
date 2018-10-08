/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

#include "TGAVariable.h"
#include "TGAExports.h"

class TGAImageID : public TGAVariable
{
public:
  TGAImageID(TGAHeader* pHeader, ITGAStream* pFile);

  unsigned __int64 size() const;
};