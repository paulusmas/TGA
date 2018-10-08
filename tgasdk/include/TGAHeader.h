/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once

#include "TGAExports.h"
#include "TGAEnum.h"

#define GET_IMAGE_ID_SIZE(pHeader) pHeader->field().id_length
#define GET_IMAGE_ID_OFFSET(pHeader) pHeader->size()

#define GET_COLOR_MAP_DATA_SIZE(pHeader) pHeader->color_map_specification().color_map_length * pHeader->color_map_specification().color_map_entry_size / 8
#define GET_COLOR_MAP_DATA_OFFSET(pHeader) (GET_IMAGE_ID_OFFSET(pHeader) + GET_IMAGE_ID_SIZE(pHeader))

#define GET_IMAGE_DATA_SIZE(pHeader) pHeader->image_specification().height * pHeader->image_specification().width * pHeader->image_specification().pixel_depth / 8
#define GET_IMAGE_DATA_OFFSET(pHeader) (GET_COLOR_MAP_DATA_OFFSET(pHeader) + GET_COLOR_MAP_DATA_SIZE(pHeader))


#pragma pack (push, 1)
struct __tagColorMapSpecification
{
  unsigned __int16  first_entry_index;
  unsigned __int16  color_map_length;
  unsigned __int8   color_map_entry_size;

  __tagColorMapSpecification() { init(); }

protected:
  void init()
  {
    first_entry_index     = 0;
    color_map_length      = 0;
    color_map_entry_size  = 0;
  }
};
typedef __tagColorMapSpecification ColorMapSpecification;

struct __tagImageSpecification
{
  unsigned __int16  x_origin;
  unsigned __int16  y_origin;
  unsigned __int16  width;
  unsigned __int16  height;
  unsigned __int8   pixel_depth;
  unsigned __int8   image_descriptor;

  __tagImageSpecification() { init(); }

protected:
  void init()
  {
    x_origin = 0;
    y_origin = 0;
    width = 0;
    height = 0;
    pixel_depth = 0;
    image_descriptor = 0;
  }
};
typedef __tagImageSpecification ImageSpecification;

struct __tagField
{
  unsigned __int8       id_length;
  unsigned __int8       color_map_type;
  ImageType             image_type;

  bool  isEncoded() const { return 8 < (unsigned __int8)image_type && (unsigned __int8)image_type < 12; }
};
typedef __tagField TGAField;

#pragma pack (pop)


struct ITGAStream;

class TGA_EXPORT TGAHeader
{
  struct HEADERImpl;
  HEADERImpl* m_pImpl;
public:
  TGAHeader();
  ~TGAHeader();

  size_t size() const;

  void read(ITGAStream* pFile);

  const TGAField& field() const;
  TGAField& field();

  const ColorMapSpecification& color_map_specification() const;
  ColorMapSpecification& color_map_specification();

  const ImageSpecification& image_specification() const;
  ImageSpecification& image_specification();
};