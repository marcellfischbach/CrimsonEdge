
#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/entity/spatialstate.hh>

#include <ceCore/graphics/camera.hh>
#include <ceCore/graphics/projector.hh>
#include <ceCore/graphics/eclearmode.hh>
#include <ceCore/math/color4f.hh>

namespace cryo
{

class GfxCamera;
struct iRenderTarget2D;
struct iSkyboxRenderer;
class PostProcessing;

CS_CLASS()
class CS_CORE_API CameraState : public CS_SUPER(SpatialState)
{
CS_CLASS_GEN_OBJECT;
public:
  CameraState();
  ~CameraState() override;


  void SetNear(float near);
  float GetNear() const;

  void SetFar(float near);
  float GetFar() const;

  void SetAngle(float angle);
  float GetAngle() const;

  void SetAngleWidthHeight(float angleWidtHeight);
  float GetAngleWidthHeight() const;

  void SetOrder(int order);
  int GetOrder() const;

  void SetRenderTarget(iRenderTarget2D *renderTarget);
  iRenderTarget2D *GetRenderTarget();
  const iRenderTarget2D *GetRenderTarget() const;

  void SetClearMode(eClearMode clearMode);
  eClearMode GetClearMode() const;

  void SetClearColorMode(eClearColorMode clearMode);
  eClearColorMode GetClearColorMode() const;

  void SetClearColor(const Color4f &clearColor);
  const Color4f &GetClearColor() const;

  void SetClearDepth(float clearDepth);
  float GetClearDepth() const;

  void SetRenderShadows(bool renderShadows);
  bool IsRenderShadows() const;

  void SetPostProcessing(PostProcessing *postProcessing);
  PostProcessing *GetPostPRocessing() const;

  void SetSkyboxRenderer(iSkyboxRenderer *skyboxRenderer);
  iSkyboxRenderer *GetSkyboxRenderer() const;

  const Camera &GetCamera() const;
  const Projector &GetProjector() const;

  void Update(u32 width, u32 height);

  void OnAttachedToWorld(World *world) override;
  void OnDetachedFromWorld(World *world) override;

protected:
  void TransformationUpdatedPreChildren() override;

private:
  CS_PROPERTY()
  float m_near;
  CS_PROPERTY()
  float m_far;

  CS_PROPERTY()
  float m_angle;

  CS_PROPERTY()
  float m_angleWidthHeight;

  CS_PROPERTY()
  int m_order;

  CS_PROPERTY()
  iRenderTarget2D *m_renderTarget;

  CS_PROPERTY()
  eClearMode m_clearMode = eClearMode::DepthColor;

  CS_PROPERTY()
  eClearColorMode m_clearColorMode = eClearColorMode::PlainColor;

  CS_PROPERTY()
  Color4f m_clearColor = Color4f();

  CS_PROPERTY()
  float m_clearDepth = 1.0f;

  CS_PROPERTY()
  bool m_renderShadows = true;


  Camera          m_camera;
  Projector       m_projector;
  PostProcessing  *m_postProcessing;
  iSkyboxRenderer *m_skyboxRenderer;

  void UpdateGfxCamera();
  GfxCamera       *m_gfxCamera;


};


}