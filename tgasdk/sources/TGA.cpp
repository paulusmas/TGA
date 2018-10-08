/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#include "TGA.h"
#include "TGAImageID.h"
#include "TGAColorMapData.h"
#include "TGAImageData.h"

#include <vector>

class TGA::TGAImpl
{
public:
  ITGAStream  *m_pFile;
  TGAHeader   m_header;
  TGAVariable *m_imageID;
  TGAVariable *m_colorMapData;
  TGAImageData *m_imageData;
public:
  TGAImpl(ITGAStream* pFile)
  {
    m_pFile = pFile;
    m_imageID = 0;
    m_colorMapData = 0;
    m_imageData = 0;
  }
  ~TGAImpl()
  {
    m_pFile = 0;
    delete m_imageID;
    delete m_colorMapData;
    delete m_imageData;
  }
public:
  void read()
  {
    m_header.read(m_pFile);
    m_imageID = new TGAImageID(&m_header, m_pFile);
    m_colorMapData = new TGAColorMapData(&m_header, m_pFile);
    m_imageData = new TGAImageData(&m_header, m_pFile);
  }

  template<class T_TVariable>
  void read_variable_section(std::vector<unsigned __int8>& data)
  {
    T_TVariable varSection(&m_header, m_pFile);
    unsigned __int64 size = varSection.size();
    if (!size)
      return;
    data.resize(size);
    varSection.read(&data[0], size);
  }
};

TGA::TGA(ITGAStream* pFile)
  : m_pImpl(new TGAImpl(pFile))
{

}

TGA::~TGA()
{
  delete m_pImpl;
}

void TGA::read()
{
  m_pImpl->read();
}

const TGAHeader& TGA::header() const
{
  return m_pImpl->m_header;
}

TGAHeader& TGA::header()
{
  return m_pImpl->m_header;
}

void TGA::image_id(void *pBuf) const
{
  image_id(pBuf, m_pImpl->m_imageID->size());
}
void TGA::image_id(void *pBuf, unsigned __int64 sizeChunk) const
{
  if (m_pImpl->m_imageID)
    m_pImpl->m_imageID->read(pBuf, sizeChunk);
}
unsigned __int64 TGA::image_id_size() const
{
  return m_pImpl->m_imageID->size();
}

void TGA::color_map_data(void *pBuf) const
{
  color_map_data(pBuf, m_pImpl->m_colorMapData->size());
}
void TGA::color_map_data(void *pBuf, unsigned __int64 sizeChunk) const
{
  if (m_pImpl->m_colorMapData)
    m_pImpl->m_colorMapData->read(pBuf, sizeChunk);
}
unsigned __int64 TGA::color_map_data_size() const
{
  return m_pImpl->m_colorMapData->size();
}

void TGA::image_data(void *pBuf) const
{
  m_pImpl->m_imageData->read(pBuf);
}
unsigned __int64 TGA::image_data_size() const
{
  return m_pImpl->m_imageData->size();
}
