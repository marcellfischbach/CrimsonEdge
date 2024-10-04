#pragma once

#include <ceCore/csCoreExport.hh>
#include <ceCore/csClass.hh>
#include <ceCore/graphics/eClearMode.hh>
#include <ceCore/math/csColor4f.hh>

namespace cryo
{

class csCamera;
class csProjector;
struct iRenderTarget2D;
struct iTextureCube;
struct iSkyboxRenderer;
class csPostProcessing;

CS_CLASS()
class CS_CORE_API csGfxCamera : public CS_SUPER(iObject)
{
CS_CLASS_GEN_OBJECT;
public:
  csGfxCamera();
  ~csGfxCamera() override;

  void SetCamera(csCamera *camera);
  const csCamera *GetCamera() const;
  csCamera *GetCamera();

  void SetProjector(csProjector *projector);
  const csProjector *GetProjector() const;
  csProjector *GetProjector();

  eClearMode GetClearMode() const;
  eClearColorMode GetClearColorMode() const;
  const csColor4f &GetClearColor() const;
  float GetClearDepth() const;

  void SetRenderTarget(iRenderTarget2D *renderTarget);
  iRenderTarget2D *GetRenderTarget();
  const iRenderTarget2D *GetRenderTarget() const;

  void SetOrder(int order);
  int GetOrder() const;

  void SetRenderShadows(bool renderShadows);
  bool IsRenderShadows() const;

  void SetPostProcessing(csPostProcessing *postProcessing);
  csPostProcessing *GetPostProcessing() const;

  void SetSkyboxRenderer(iSkyboxRenderer *skyboxRenderer);
  iSkyboxRenderer* GetSkyboxRenderer() const;

  void UpdateData(float near, float far, float angle, float angleWidthHeight);

  void UpdateClear(eClearMode mode, eClearColorMode clearColorMode, const csColor4f &color, iSkyboxRenderer *skybox, float depth);

  void UpdateProjector(uint32_t width, uint32_t height);

private:

  float m_near;
  float m_far;
  float m_angle;
  float m_angleWidthHeight;


  eClearMode      m_clearMode;
  eClearColorMode m_clearColorMode;

  csColor4f m_clearColor;
  float     m_clearDepth;

  csCamera    *m_camera;
  csProjector *m_projector;

  iSkyboxRenderer *m_skyboxRenderer;

  iRenderTarget2D *m_renderTarget;
  int             m_order;
  bool            m_renderShadows;

  csPostProcessing *m_postProcessing;
};


}

