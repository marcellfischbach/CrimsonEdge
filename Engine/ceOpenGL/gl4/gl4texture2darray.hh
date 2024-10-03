
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/graphics/itexture2darray.hh>
#include <vector>


namespace cryo::opengl
{

CS_CLASS()
class CS_OGL_API GL4Texture2DArray : public CS_SUPER(iTexture2DArray)
{
  CS_CLASS_GEN_OBJECT;
public:
  GL4Texture2DArray();
  ~GL4Texture2DArray();
  CS_NODISCARD uint32_t GetName()
  {
    return m_name;
  }

  CS_NODISCARD eTextureType GetType() const
  {
    return eTextureType::Texture2DArray;
  }

  ePixelFormat GetFormat() const override;

  void SetSampler(iSampler* sampler) override;
  iSampler* GetSampler() override;
  const iSampler* GetSampler() const override;

  void Bind();
  void Unbind();

  bool Initialize(uint16_t width, uint16_t height, uint16_t layer, ePixelFormat format, bool generateMipMaps);


  uint32_t GetWidth() const { return m_width; }
  uint32_t GetHeight() const { return m_height; }
  uint32_t GetLayer() const { return m_layer; }

  void Data(uint16_t layer, const Image * image) override;
  void Data(uint16_t layer, uint16_t level, const Image * image) override;
  void Data(uint16_t layer, uint16_t level, ePixelFormat format, const void* data) override;
  void Data(uint16_t layer, uint16_t level, uint16_t x, uint16_t y, uint16_t width, uint16_t height, ePixelFormat format, const void* data) override;
private:
  uint32_t m_name;
  uint16_t m_width;
  uint16_t m_height;
  uint16_t m_layer;
  ePixelFormat m_format;

  struct Level
  {
    uint16_t Width;
    uint16_t Height;
  };
  std::vector<Level> m_level;
  iSampler* m_sampler;
};

}