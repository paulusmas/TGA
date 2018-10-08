/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 *  
 */

#pragma once

#include "TGAHeader.h"
#include "TGAVersion.h"
#include <vector>

struct ITGAStream;

class TGA_EXPORT TGA
{
  class TGAImpl;
  TGAImpl* m_pImpl;
public:
  TGA(ITGAStream* pFile);
    
  ~TGA();

  void read();

  const TGAHeader& header() const;
  TGAHeader& header();

  void image_id(void *pBuf) const;
  void image_id(void *pBuf, unsigned __int64 sizeChunk) const;
  unsigned __int64 image_id_size() const;

  void color_map_data(void *pBuf) const;
  void color_map_data(void *pBuf, unsigned __int64 sizeChunk) const;
  unsigned __int64 color_map_data_size() const;

  void image_data(void *pBuf) const;
  unsigned __int64 image_data_size() const;
};