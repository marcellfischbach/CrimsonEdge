
#include <ceOpenGL/gl4/pipeline/forward/gl4forwardpipeline.hh>
#include <ceOpenGL/gl4/pipeline/forward/gl4forwardmeshsorter.hh>
#include <ceOpenGL/gl4/gl4device.hh>
#include <ceOpenGL/gl4/gl4directionallight.hh>
#include <ceOpenGL/gl4/gl4pointlight.hh>
#include <ceOpenGL/gl4/gl4rendertargetcube.hh>
#include <ceOpenGL/glerror.hh>
#include <ceCore/graphics/camera.hh>
#include <ceCore/graphics/projector.hh>
#include <ceCore/graphics/scene/gfxcamera.hh>
#include <ceCore/graphics/scene/igfxscene.hh>
#include <ceCore/graphics/irendertarget2d.hh>
#include <ceCore/graphics/irendertargetcube.hh>
#include <ceCore/graphics/isampler.hh>
#include <ceCore/math/clipper/boxclipper.hh>
#include <ceCore/math/clipper/cameraclipper.hh>
#include <ceCore/math/clipper/multiplaneclipper.hh>
#include <ceCore/math/clipper/sphereclipper.hh>
#include <ceCore/settings.hh>
#include <algorithm>
#include <array>
#include <GL/glew.h>
namespace ce::opengl
{

const float MinLightInfluence = 0.0f;

GL4ForwardPipeline::GL4ForwardPipeline()
  : m_frame(0), m_device(nullptr), m_scene(nullptr), m_target(nullptr)
{
  CE_CLASS_GEN_CONSTR;

}

void GL4ForwardPipeline::Initialize()
{
  Settings settings(ResourceLocator("file:///config/graphics.config"));
  m_pointLightRenderer.Initialize(settings);
  m_directionalLightRenderer.Initialize(settings);

}

GL4ForwardPipeline::~GL4ForwardPipeline() noexcept
{

}

bool transparent_mesh_compare_less(const GfxMesh* mesh0, const GfxMesh* mesh1)
{
  return false;
}

void GL4ForwardPipeline::Render(iRenderTarget2D* target,
                                const GfxCamera* camera,
                                iDevice* device,
                                iGfxScene* scene
)
{
  CE_GL_ERROR();
  ++m_frame;
  SetupVariables(target, camera, device, scene);


  CameraClipper clppr(*m_camera, *m_projector);

  ScanVisibleMeshes(&clppr);

  BindCamera();
  RenderDepthToTarget();
  ApplyDepthBufferToLightRenderers ();


  CollectLightsAndShadows(&clppr);
  RenderShadowMaps();

  BindCamera();
  RenderForwardToTarget();

  RenderDebugToTarget ();
  Cleanup();


  CE_GL_ERROR();

}

void GL4ForwardPipeline::SetupVariables(iRenderTarget2D* target,
                                        const GfxCamera* camera,
                                        iDevice* device,
                                        iGfxScene* scene)
{
  m_device    = device;
  m_gfxCamera = camera;
  m_camera    = camera->GetCamera();
  m_projector = camera->GetProjector();
  m_scene     = scene;
  m_target    = target;

  m_pointLightRenderer.SetDevice(device);
  m_pointLightRenderer.SetScene(scene);
  m_pointLightRenderer.Clear();
  m_directionalLightRenderer.SetDevice(device);
  m_directionalLightRenderer.SetScene(scene);
  m_directionalLightRenderer.Clear();

}

void GL4ForwardPipeline::CollectLightsAndShadows(iClipper* clipper)
{
  m_dynamicLights.clear();
  m_staticLights.clear();
  m_staticLightsNew.clear();

  size_t lightOffset = 0;
  m_scene->ScanLights(clipper, iGfxScene::eSM_Global,
                      [this, &lightOffset](GfxLight* light)
                      {

                        if (lightOffset >= MaxLights)
                        {
                          return false;
                        }
                        m_renderLights[lightOffset] = light;
                        lightOffset++;
                        CollectShadowLights(light);
                        return true;
                      }
  );

  CE_GL_ERROR();

  //
  // collect the "normal" static and dynamic lights

  m_scene->ScanLights(clipper, iGfxScene::eSM_Dynamic | iGfxScene::eSM_Static,
                      [this](GfxLight* light)
                      {
                        LightScanned(light);
                        CollectShadowLights(light);
                        return true;
                      }
  );

  for (size_t i = lightOffset; i < MaxLights; i++)
  {
    m_renderLights[i] = nullptr;
  }
  m_numberOfFixedLights = lightOffset;
}

void GL4ForwardPipeline::ScanVisibleMeshes(iClipper* clipper)
{
  m_collector.Clear();
  m_scene->ScanMeshes(clipper, m_collector);

  std::vector<GfxMesh*>& defaultMeshes     = m_collector.GetMeshes(eRenderQueue::Default);
  std::vector<GfxMesh*>& transparentMeshes = m_collector.GetMeshes(eRenderQueue::Transparency);

  std::sort(defaultMeshes.begin(), defaultMeshes.end(), material_shader_compare_less_forward);
  std::sort(transparentMeshes.begin(), transparentMeshes.end(), transparent_mesh_compare_less);
}

void GL4ForwardPipeline::BindCamera()
{
  m_camera->Bind(m_device);
  m_projector->Bind(m_device);

}

void GL4ForwardPipeline::RenderDepthToTarget()
{
  m_device->SetRenderTarget(m_target);
  eClearMode mode = m_gfxCamera->GetClearMode();
  m_device->SetColorWrite(true, true, true, true);
  m_device->SetDepthWrite(true);
  m_device->Clear(mode == eClearMode::Color || mode == eClearMode::DepthColor,
                  m_gfxCamera->GetClearColor(),
                  mode == eClearMode::Depth || mode == eClearMode::DepthColor,
                  m_gfxCamera->GetClearDepth(),
                  false,
                  0
  );

  m_device->SetColorWrite(false, false, false, false);
  m_device->SetDepthTest(true);
  m_device->SetDepthWrite(true);
  m_device->SetDepthFunc(eCF_LessOrEqual);
  const std::vector<GfxMesh*>& defaultMeshes = m_collector.GetMeshes(eRenderQueue::Default);
  for (auto            & mesh : defaultMeshes)
  {
      RenderUnlitDepthMesh(mesh);
  }
  m_device->SetRenderTarget(nullptr);
}


void GL4ForwardPipeline::RenderForwardToTarget()
{
  m_device->SetRenderTarget(m_target);



  m_device->SetColorWrite(true, true, true, true);
  m_device->SetDepthTest(true);
  m_device->SetDepthWrite(false);
  m_device->SetDepthFunc(eCF_LessOrEqual);

  std::vector<GfxMesh*>& defaultMeshes = m_collector.GetMeshes(eRenderQueue::Default);
  for (auto            & mesh : defaultMeshes)
  {
    auto material = mesh->GetMaterial();
    if (material->GetShadingMode() == eShadingMode::Shaded)
    {
      RenderMesh(mesh, m_renderLights, m_numberOfFixedLights);
    }
    else
    {
      RenderUnlitForwardMesh(mesh);
    }
  }


  m_device->SetDepthWrite(false);
  m_device->SetDepthFunc(eCF_LessOrEqual);

  std::vector<GfxMesh*>& transparentMeshes = m_collector.GetMeshes(eRenderQueue::Transparency);
  for (auto            & mesh : m_transparentMeshes)
  {
    auto material = mesh->GetMaterial();
    if (material->GetShadingMode() == eShadingMode::Shaded)
    {
      RenderMesh(mesh, m_renderLights, m_numberOfFixedLights);
    }
    else
    {
      RenderUnlitForwardMesh(mesh);
    }
  }
  m_device->SetRenderTarget(nullptr);
}

void GL4ForwardPipeline::RenderDebugToTarget()
{
  m_device->SetRenderTarget(m_target);
  m_device->SetDepthWrite(false);
  m_device->SetDepthTest(false);
  m_device->SetColorWrite(true, true, true, true);
  m_device->RenderFullscreen(m_directionalLightRenderer.GetColorTexture());
}

void GL4ForwardPipeline::ApplyDepthBufferToLightRenderers()
{
  m_directionalLightRenderer.SetDepthBuffer(m_target->GetDepthTexture());
}

void GL4ForwardPipeline::Cleanup()
{
  m_device->BindMaterial(nullptr, eRP_COUNT);

  m_device->SetBlending(false);
  m_device->SetDepthWrite(true);
  m_device->SetDepthTest(true);

  m_device    = nullptr;
  m_gfxCamera = nullptr;
  m_camera    = nullptr;
  m_projector = nullptr;
  m_scene     = nullptr;
  m_target    = nullptr;

}

void GL4ForwardPipeline::LightScanned(GfxLight* light)
{
  if (light->IsStatic())
  {
    m_staticLights.push_back(light);
    if (light->GetFrame() == 0)
    {
      m_staticLightsNew.push_back(light);
      light->SetFrame(m_frame);
    }
  }
  else
  {
    m_dynamicLights.push_back(light);
  }
}

void GL4ForwardPipeline::RenderUnlitDepthMesh(GfxMesh* mesh)
{
  mesh->RenderUnlit(m_device, eRP_Depth);
}

void GL4ForwardPipeline::RenderUnlitForwardMesh(GfxMesh* mesh)
{
  mesh->RenderUnlit(m_device, eRP_Forward);
}

void GL4ForwardPipeline::RenderMesh(GfxMesh* mesh, std::array<const GfxLight*, MaxLights>& lights, Size offset)
{
  if (mesh->IsStatic())
  {
    if (mesh->IsLightingDirty())
    {
      mesh->ClearLights();
      AppendLights(mesh, m_staticLights);
      mesh->SetLightingDirty(false);
    }
    else
    {
      AppendLights(mesh, m_staticLightsNew);
    }

    auto dynamicLights = CalcMeshLightInfluences(mesh, m_dynamicLights, true);
    Size numLights     = AssignLights(
      mesh->GetLights(),
      dynamicLights,
      lights,
      offset
    );
    CE_GL_ERROR();
    mesh->RenderForward(m_device, eRP_Forward, lights.data(), numLights);
    CE_GL_ERROR();
  }
  else
  {
    auto staticLights  = CalcMeshLightInfluences(mesh, m_staticLights, true);
    auto dynamicLights = CalcMeshLightInfluences(mesh, m_dynamicLights, true);
    Size numLights     = AssignLights(
      staticLights,
      dynamicLights,
      lights,
      offset
    );
    CE_GL_ERROR();
    mesh->RenderForward(m_device, eRP_Forward, lights.data(), numLights);
    CE_GL_ERROR();
  }

  //printf("  RenderUnlitForwardMesh - done\n");
}

void GL4ForwardPipeline::CollectShadowLights(GfxLight* light)
{
  if (!light)
  {
    return;
  }
  auto lght = light->GetLight();
  if (!lght->IsCastShadow())
  {
    return;
  }
  switch (lght->GetType())
  {
  case eLT_Point:
    m_pointLightRenderer.Add(static_cast<GL4PointLight*>(light->GetLight()));
    break;

  case eLT_Directional:
    m_directionalLightRenderer.Add(static_cast<GL4DirectionalLight*>(light->GetLight()));
    break;

  default:
    break;
  }
}

void GL4ForwardPipeline::RenderShadowMaps()
{
  if (m_gfxCamera->IsRenderShadows())
  {
    m_device->ClearShadowMaps();

    m_directionalLightRenderer.RenderShadowMaps(*m_camera, *m_projector);
    m_pointLightRenderer.RenderShadowMaps(0);
  }
}

Size GL4ForwardPipeline::AssignLights(
  const std::vector<GfxMesh::Light>& static_lights,
  const std::vector<GfxMesh::Light>& dynamic_lights,
  std::array<const GfxLight*, MaxLights>& lights,
  Size offset
)
{
  for (Size s = 0, d = 0, sn = static_lights.size(), dn = dynamic_lights.size();
       offset < MaxLights && (s < sn || d < dn); offset++)
  {
    if (s < sn && d < dn)
    {
      if (static_lights[s].Influence >= dynamic_lights[d].Influence)
      {
        lights[offset] = static_lights[s++].Light;
      }
      else
      {
        lights[offset] = dynamic_lights[d++].Light;
      }
    }
    else if (s < sn)
    {
      lights[offset] = static_lights[s++].Light;
    }
    else if (d < dn)
    {
      lights[offset] = dynamic_lights[d++].Light;
    }
    else
    {
      break;
    }
  }

  return offset;
}

float GL4ForwardPipeline::CalcMeshLightInfluence(const GfxLight* light, const GfxMesh* mesh) const
{
  if (!light || !mesh)
  {
    return 0.0f;
  }


  // TODO: Take the power of the light from the light ... currently there is no power in the light
  float lightPower          = 1.0f;
  float lightDistanceFactor = 0.0f;
  switch (light->GetLight()->GetType())
  {
  case eLT_Directional:
    lightDistanceFactor = 1.0f;
    break;
  case eLT_Point:
    auto     pointLight = light->GetLight()->Query<iPointLight>();
    Vector3f lightPos   = pointLight->GetPosition();
    Vector3f meshPos    = mesh->GetModelMatrix().GetTranslation();
    Vector3f delta      = lightPos - meshPos;
    float    halfSize   = mesh->GetMesh()->GetBoundingBox().GetDiagonal() / 2.0f;
    float    distance   = delta.Length();
    float    overlap    = pointLight->GetRange() + halfSize - distance;
    if (overlap > 0.0f)
    {
      lightDistanceFactor = overlap / pointLight->GetRange();
    }
    break;

  }
  return lightPower * lightDistanceFactor;
}

std::vector<GfxMesh::Light> GL4ForwardPipeline::CalcMeshLightInfluences(const GfxMesh* mesh,
                                                                        const std::vector<GfxLight*>& lights,
                                                                        bool sorted
) const
{
  std::vector<GfxMesh::Light> influences;
  for (GfxLight               * light : lights)
  {
    float influence = CalcMeshLightInfluence(light, mesh);
    if (influence <= MinLightInfluence)
    {
      continue;
    }
    GfxMesh::Light l{};
    l.Light     = light;
    l.Influence = influence;
    influences.push_back(l);
  }

  if (sorted)
  {
    std::sort(influences.begin(),
              influences.end(),
              [](GfxMesh::Light& l0, GfxMesh::Light& l1)
              { return l0.Influence > l1.Influence; }
    );
  }


  return influences;
}

void GL4ForwardPipeline::AppendLights(GfxMesh* mesh, const std::vector<GfxLight*>& lights) const
{
  if (lights.empty())
  {
    return;
  }

  auto     meshLights = CalcMeshLightInfluences(mesh, lights, false);
  for (auto& meshLight : meshLights)
  {
    mesh->AddLight(meshLight.Light, meshLight.Influence);
  }
  mesh->SortAndLimitLights(MaxLights);
}

}