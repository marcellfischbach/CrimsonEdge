

#pragma once

#include <ceOpenGL/csOpenGLExport.hh>
#include <ceOpenGL/csOpenglConstants.hh>
#include <ceOpenGL/gl4/pipeline/pointsm/csGL4PointSMRenderer.hh>
#include <ceCore/csTypes.hh>
#include <map>
#include <vector>
#include <array>

namespace cryo
{

struct iDevice;
struct iSampler;
struct iShader;
struct iShaderAttribute;
struct iGfxScene;
struct iTexture2D;
class csSettings;

class csCamera;
class csProjector;

}

namespace cryo::opengl
{

class csGL4Device;
class csGL4PointLight;
class csGL4TextureCube;
class csGL4RenderTarget2D;
class csGL4RenderTargetCube;

class csGL4ForwardPointLightRenderer
{
public:
  csGL4ForwardPointLightRenderer();
  ~csGL4ForwardPointLightRenderer();

  void Initialize();

  void SetDevice(iDevice *device);
  void SetScene(iGfxScene *scene);
  void SetDepthBuffer(iTexture2D *depthBuffer);


  void Clear();
  void Add(csGL4PointLight *pointLight);

  void RenderShadowMaps(const csCamera &camera,
                        const csProjector &projector);

  iTexture2D* GetColorTexture();
  iTexture2D* GetDepthTexture();
private:
  void SortLights();


  void RenderShadow(csGL4PointLight *pointLight, const csCamera &camera, const csProjector &projector, size_t lightIdx);
  void ApplyShadowMapToDevice(csGL4PointLight *pointLight, size_t lightIdx);
  csGL4RenderTarget2D *GetPointLightShadowMap(Size idx);

private:
  csGL4Device *m_device = nullptr;
  iGfxScene   *m_scene  = nullptr;
  iTexture2D *m_depthBuffer = nullptr;

  std::vector<csGL4PointLight *>               m_shadowPointLights;
  std::array<csGL4RenderTarget2D *, MaxLights> m_pointLightShadowMap;

  csGL4PointSMRenderer m_shadowRenderer;



};


}