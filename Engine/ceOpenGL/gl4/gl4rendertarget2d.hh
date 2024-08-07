
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/graphics/irendertarget2d.hh>
#include <ceCore/graphics/ecubeface.hh>

namespace ce::opengl
{

class GL4Texture2D;

CE_CLASS()
class CE_OGL_API GL4RenderTarget2D : public CE_SUPER(iRenderTarget2D)
{
  CE_CLASS_GEN_OBJECT;
public:
  GL4RenderTarget2D();
  virtual ~GL4RenderTarget2D() override;

  void Bind();

  bool Initialize (uint16_t width, uint16_t height);

  uint16_t GetWidth() const override;
  uint16_t GetHeight() const override;

  void SetDepthTexture(iTexture2D* depthTexture) override;
  void SetDepthTexture(iTexture2DArray* depthTexture, size_t layer) override;
  void SetDepthTexture(iTextureCube* depthTexture, eCubeFace face) override;
  void SetDepthBuffer(ePixelFormat format) override;

  void AddColorTexture(iTexture2D* colorTexture) override;
  void AddColorTexture(iTexture2DArray *colorTexture, size_t layer) override;
  void AddColorTexture(iTextureCube* colorTexture, eCubeFace face) override;

  CE_NODISCARD  eTextureType GetType() const override;

  bool Compile() override;
  std::string GetCompileLog() const override;

  iTexture2D* GetDepthTexture() override;
  iTextureCube* GetDepthTextureCube() override;
  eCubeFace GetDepthTextureCubeFace() const override;

  const iTexture2D* GetDepthTexture() const override;
  const iTextureCube* GetDepthTextureCube() const override;

  Size GetNumberOfColorTextures() const override;
  iTexture2D* GetColorTexture(Size idx) override;
  iTextureCube* GetColorTextureCube(Size idx) override;
  const iTexture2D* GetColorTexture(Size idx) const override;
  const iTextureCube* GetColorTextureCube(Size idx) const override;
  eCubeFace GetColorTextureCubeFace(Size idx) const override;

private:
  uint32_t m_name;
  uint16_t m_width;
  uint16_t m_height;

  uint32_t  m_depthBuffer;

  struct TextureBind
  {
    iTexture2D *texture = nullptr;
    iTexture2DArray *textureArray = nullptr;
    iTextureCube *textureCube = nullptr;
    size_t textureArrayLayer = 0;
    eCubeFace textureCubeFace = eCubeFace::eCF_PosX;

  };

  TextureBind m_depthTexture;

  std::vector<TextureBind> m_colorTextures;

  std::string m_log;
};

}
