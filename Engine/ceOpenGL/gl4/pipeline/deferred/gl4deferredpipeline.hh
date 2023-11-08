
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceOpenGL/gl4/pipeline/deferred/gl4deferreddirectionallightrenderer.hh>
#include <ceCore/graphics/irenderpipeline.hh>
#include <ceCore/graphics/scene/gfxscenecollector.hh>

namespace ce
{

class Camera;
class Projector;
class GBuffer;
struct iClipper;
struct iDirectionalLight;

namespace opengl
{

class GL4DeferredDirectionalLightRenderer;

CE_CLASS()
class CE_OGL_API GL4DeferredPipeline : public CE_SUPER(iRenderPipeline)
{
CE_CLASS_GEN_OBJECT;
public:
  GL4DeferredPipeline();
  ~GL4DeferredPipeline() noexcept override;


  void Initialize() override;

  void Render(iRenderTarget2D *target, const GfxCamera *camera, iDevice *device, iGfxScene *scene) override;

  void SetRenderMode(int mode)
  { m_renderMode = mode; }
  int GetRenderMode() const
  { return m_renderMode; }

  void IncRenderMode()
  { m_renderMode = m_renderMode == 3 ? 0 : m_renderMode + 1; }
  void DecRenderMode()
  { m_renderMode = m_renderMode == 0 ? 3 : m_renderMode - 1; }

private:

  void RenderGBuffer(uint16_t width, uint16_t height);
  void RenderLights();
  void RenderDirectionalLight(const GL4DirectionalLight *directionalLight);


  void SetupVariables(iRenderTarget2D *target, const GfxCamera *camera, iDevice *device, iGfxScene *scene);
  void UpdateIntermediate();
  void ScanVisibleMeshes(iClipper *clipper);
  void BindCamera();

  GBuffer *m_gBuffer;

  iDevice         *m_device;
  const GfxCamera *m_gfxCamera;
  const Camera    *m_camera;
  const Projector *m_projector;
  iGfxScene       *m_scene;
  iRenderTarget2D *m_intermediate;
  iRenderTarget2D *m_target;

  GfxSceneCollector      m_collector;
  std::vector<GfxMesh *> m_shadedMeshes;
  std::vector<GfxMesh *> m_transparentMeshes;
  std::vector<GfxMesh *> m_unshadedMeshes;

  GL4DeferredDirectionalLightRenderer m_directionalLightRenderer;
  int m_renderMode;
};


}

}