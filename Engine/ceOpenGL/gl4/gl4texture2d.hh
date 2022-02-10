
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/graphics/itexture2d.hh>
#include <vector>


namespace ce::opengl
{

CE_CLASS()
class CE_OGL_API GL4Texture2D : public CE_SUPER(iTexture2D)
{
  CE_CLASS_GEN_OBJECT;
public:
  GL4Texture2D();
  ~GL4Texture2D();
  CE_NODISCARD uint32_t GetName()
  {
    return m_name;
  }

  CE_NODISCARD eTextureType GetType() const
  {
    return eTT_Texture2D;
  }

  ePixelFormat GetFormat() const override;

  void SetSampler(iSampler* sampler) override;
  iSampler* GetSampler() override;
  const iSampler* GetSampler() const override;

  void Bind();

  bool Initialize(uint16_t width, uint16_t height, ePixelFormat format, bool generateMipMaps);

  void Data(const Image * image) override;
  void Data(uint16_t level, const Image * image) override;
  void Data(uint16_t level, ePixelFormat format, const void* data) override;
  void Data(uint16_t level, uint16_t x, uint16_t y, uint16_t width, uint16_t height, ePixelFormat format, const void* data) override;
private:
  uint32_t m_name;
  uint16_t m_width;
  uint16_t m_height;
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