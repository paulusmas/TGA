#include "TGA.h"

#include "TGAFile.h"

#include <stdio.h>

class TGAFileImpl : public ITGAStream
{
  FILE* m_hFile;
  size_t      m_size;
public:
  TGAFileImpl(const char* file)
    : m_hFile(0)
  {
    m_hFile = fopen(file, "r");
  }

  int read(void* pBuffer, int sizeBlock)
  {
    return fread(pBuffer, sizeof(unsigned __int8), sizeBlock, m_hFile);
  }

  int seek(__int64 offset, TGAStremOrigin SeekMethod)
  {
    return _fseeki64(m_hFile, offset, SeekMethod);
  }

  unsigned __int64 tell()
  {
    return _ftelli64(m_hFile);
  }

  unsigned __int64 size() const
  {
    return m_size;
  }
};



int main(int argc, char *argv[])
{
  if (argc != 2)
    return 0;
  TGAFileImpl tgaFile(argv[1]);

  TGA tga(&tgaFile);
  tga.read();

  const TGAHeader& hdr = tga.header();
  const TGAField& field = hdr.field();
  const ColorMapSpecification& cmap = hdr.color_map_specification();
  const ImageSpecification& image_spec = hdr.image_specification();

  auto sizeHeader = hdr.size();

  std::vector<unsigned __int8> vImageID; vImageID.resize((int)tga.image_id_size());
  std::vector<unsigned __int8> vColorMapData; vColorMapData.resize((int)tga.color_map_data_size());
  std::vector<unsigned __int8> vImageData; vImageData.resize((int)tga.image_data_size());

  tga.image_id(vImageID.data());
  tga.color_map_data(vColorMapData.data());
  tga.image_data(vImageData.data());

  return 0;
}