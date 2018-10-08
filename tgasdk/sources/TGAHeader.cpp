/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGAHeader.h"
#include "TGAFiler.hpp"

#include <vector>

class FieldFiler : public TGAFiler
{
  TGAField& m_field;
public:
  FieldFiler(TGAField& field)
    : m_field(field) { }
private:
  size_t beginSection() const { return 0; }
  size_t sizeSection()  const { return TAG<TGAField>::size; }

  void subRead(unsigned __int8* pBuffer)
  {
    m_field.id_length       = pBuffer[0];
    m_field.color_map_type  = pBuffer[1];
    m_field.image_type      = (ImageType)pBuffer[2];
  }
};

class ColorMapSpecificationFiler : public TGAFiler
{
  ColorMapSpecification& m_color_map_specification;
public:
  ColorMapSpecificationFiler(ColorMapSpecification& color_map_specification)
    : m_color_map_specification(color_map_specification) { }
private:
  size_t beginSection() const { return TAG<TGAField>::size; }
  size_t sizeSection()  const { return TAG<ColorMapSpecification>::size; }

  void subRead(unsigned __int8* pBuffer)
  {
    m_color_map_specification.first_entry_index     = pBuffer[0] | pBuffer[1] << 8;
    m_color_map_specification.color_map_length      = pBuffer[2] | pBuffer[3] << 8;
    m_color_map_specification.color_map_entry_size  = pBuffer[4]; 
  }
};

class ImageSpecificationFiler : public TGAFiler
{
  ImageSpecification& m_image_specification;
public:
  ImageSpecificationFiler(ImageSpecification& image_specification)
    : m_image_specification(image_specification) { }
private:
  size_t beginSection() const { return TAG<TGAField>::size + TAG<ColorMapSpecification>::size; }
  size_t sizeSection()  const { return TAG<ImageSpecification>::size; }

  void subRead(unsigned __int8* pBuffer)
  {
    m_image_specification.x_origin          = pBuffer[0] | pBuffer[1] << 8;
    m_image_specification.y_origin          = pBuffer[2] | pBuffer[3] << 8;
    m_image_specification.width             = pBuffer[4] | pBuffer[5] << 8;
    m_image_specification.height            = pBuffer[6] | pBuffer[7] << 8;
    m_image_specification.pixel_depth       = pBuffer[8];
    m_image_specification.image_descriptor  = pBuffer[9];
  }
};


struct TGAHeader::HEADERImpl
{
  TGAField              m_field;
  ColorMapSpecification m_color_map_specification;
  ImageSpecification    m_image_specification;

  void read(ITGAStream* pFile)
  {
    FieldFiler(m_field).read(pFile);
    ColorMapSpecificationFiler(m_color_map_specification).read(pFile);
    ImageSpecificationFiler(m_image_specification).read(pFile);
  }

  size_t size() const
  {
    return sizeof(HEADERImpl);
  }
};

TGAHeader::TGAHeader()
  : m_pImpl(new HEADERImpl)
{
}

TGAHeader::~TGAHeader()
{
  delete m_pImpl;
}

size_t TGAHeader::size() const
{
  return m_pImpl->size();
}

void TGAHeader::read(ITGAStream* pFile)
{
  m_pImpl->read(pFile);
}

const TGAField& TGAHeader::field() const
{
  return m_pImpl->m_field;
}
TGAField& TGAHeader::field()
{
  return m_pImpl->m_field;
}

const ColorMapSpecification& TGAHeader::color_map_specification() const
{
  return m_pImpl->m_color_map_specification;
}
ColorMapSpecification& TGAHeader::color_map_specification()
{
  return m_pImpl->m_color_map_specification;
}

const ImageSpecification& TGAHeader::image_specification() const
{
  return m_pImpl->m_image_specification;
}
ImageSpecification& TGAHeader::image_specification()
{
  return m_pImpl->m_image_specification;
}