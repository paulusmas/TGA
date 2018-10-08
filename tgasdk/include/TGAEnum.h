/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

enum TGAResult : int
{
  eTGAResult_Ok,
  eTGAResult_BadStructure,
  eTGAResult_NULLObject,
  eTGAResult_ReadBlockFail
};

enum ImageType : unsigned __int8
{
  kNoImageDataIncluded = 0,
  kUncompressedColorMapped,
  kUncompressedTrueColor,
  kUncompressedGrayscale,
  kRunLengthEncodedColorMapped = 9,
  kRunLengthEncodedTrueColor,
  kRunLengthEncodedGrayscale
};