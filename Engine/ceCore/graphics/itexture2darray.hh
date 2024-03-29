

#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/graphics/epixelformat.hh>
#include <ceCore/graphics/itexture.hh>
#include <ceCore/types.hh>

namespace ce
{

class Image;
CE_CLASS()
struct CE_CORE_API iTexture2DArray : public CE_SUPER(iTexture)
{

  struct Descriptor
  {
    ePixelFormat Format;
    uint16_t Width;
    uint16_t Height;
    uint16_t Layers;
    bool MipMaps;
  };


  CE_CLASS_GEN;
  virtual ~iTexture2DArray() { }

  virtual void Data(uint16_t layer, const Image* image) = 0;
  virtual void Data(uint16_t layer, uint16_t level, const Image* image) = 0;
  virtual void Data(uint16_t layer, uint16_t level, ePixelFormat format, const void* data) = 0;
  virtual void Data(uint16_t layer, uint16_t level, uint16_t x, uint16_t y, uint16_t width, uint16_t height, ePixelFormat format, const void* data) = 0;

};


}