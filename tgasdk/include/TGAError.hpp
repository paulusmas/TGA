/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once
#include "TGAEnum.h"

#include <exception>

class TGAError : private std::exception
{
public:
  explicit TGAError(const char * const & msg, TGAResult error) : std::exception(msg)
  {
  }
  TGAResult error;

  const char * msg() const { return __super::what(); }
};
