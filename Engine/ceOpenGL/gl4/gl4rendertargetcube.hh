
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/graphics/irendertargetcube.hh>

namespace ce::opengl
{

class GL4TextureCube;

CE_CLASS()
class CE_OGL_API GL4RenderTargetCube : public CE_SUPER(iRenderTargetCube)
{
  CE_CLASS_GEN_OBJECT;
public:
  GL4RenderTargetCube();
  virtual ~GL4RenderTargetCube() override;

  void Bind();

  bool Initialize (uint16_t size);
  bool Initialize (uint32_t name, uint16_t size);

  uint16_t GetSize() const override;

  void SetDepthTexture(iTextureCube* depthTexture) override;
  void AddColorTexture(iTextureCube* colorTexture) override;

  CE_NODISCARD  eTextureType GetType() const override;

  bool Compile() override;
  std::string GetCompileLog() const override;

  iTextureCube* GetDepthTexture() override;
  const iTextureCube* GetDepthTexture() const override;
  Size GetNumberOfColorTextures() const override;
  iTextureCube* GetColorTexture(Size idx) override;
  const iTextureCube* GetColorTexture(Size idx) const override;

private:
  uint32_t m_name;
  uint16_t m_size;
  bool m_external;

  iTextureCube *m_depthTexture;
  std::vector<GL4TextureCube*> m_colorTextures;

  std::string m_log;

};

}
