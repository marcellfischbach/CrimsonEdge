
#include <ceCore/entity/lightstate.hh>
#include <ceCore/entity/world.hh>
#include <ceCore/graphics/ilight.hh>
#include <ceCore/graphics/ipointlight.hh>
#include <ceCore/graphics/idirectionallight.hh>
#include <ceCore/graphics/idevice.hh>
#include <ceCore/graphics/scene/gfxlight.hh>
#include <ceCore/graphics/scene/igfxscene.hh>
#include <ceCore/objectregistry.hh>

namespace ce
{


LightState::LightState(const std::string& name)
  : SpatialState(name)
  , m_light(nullptr)
  , m_directionalLight(nullptr)
  , m_pointLight(nullptr)
  , m_gfxLight(nullptr)
  , m_lightType(eLT_Point)
  , m_castShadow(false)
  , m_shadowBias(0.001f)
  , m_color(1.0f, 1.0f, 1.0f, 1.0f)
  , m_range (100.0f)
{
  CE_CLASS_GEN_CONSTR;
}

LightState::~LightState() noexcept
{
  RemoveFromScene(GetWorld());
  CE_RELEASE(m_light);
  CE_RELEASE(m_gfxLight);
}

void LightState::SetType(eLightType type)
{
  if (m_lightType != type)
  {
    World* world = GetWorld();
    RemoveFromScene(world);
    m_lightType = type;
    AddToScene(world);
  }
}

void LightState::OnAttachedToWorld(World* world)
{
  AddToScene(world);
}


void LightState::OnDetachedFromWorld(World* world)
{
  RemoveFromScene(world);
}


void LightState::TransformationUpdatedPreChildren()
{
  if (m_pointLight)
  {
    const Matrix4f& mat = GetGlobalMatrix();

    m_pointLight->SetPosition(mat.GetTranslation());
  }
  if (m_directionalLight)
  {
    const Matrix4f& mat = GetGlobalMatrix();
    m_directionalLight->SetDirection(mat.GetZAxis());
  }
}

eLightType LightState::GetType() const
{
  return m_lightType;
}


iLight* LightState::CreateLight()
{
  iDevice* device = ObjectRegistry::Get<iDevice>();
  switch (m_lightType)
  {
  case eLT_Point: return device->CreatePointLight();
  case eLT_Directional: return device->CreateDirectionalLight();
  }
  return nullptr;
}

void LightState::UpdateValues()
{
  if (m_light)
  {
    m_light->SetCastShadow(m_castShadow);
    m_light->SetShadowMapBias(m_shadowBias);
    m_light->SetColor(m_color);
    m_light->SetChangeMode(eLCM_Dynamic);

    if (m_pointLight)
    {
      m_pointLight->SetRange(m_range);
    }

    TransformationUpdatedPreChildren();
  }
}

void LightState::AddToScene(World* world)
{
  if (!m_light)
  {
    m_light = CreateLight();
    m_pointLight = m_light->Query<iPointLight>();
    m_directionalLight = m_light->Query<iDirectionalLight>();
    UpdateValues();
  }
  if (world)
  {
    iGfxScene * scene = world->GetScene();
    if (m_gfxLight)
    {
      m_gfxLight->Release();
    }
    m_gfxLight = new GfxLight();
    m_gfxLight->SetStatic(IsStatic());
    m_gfxLight->SetLight(m_light);

    scene->Add(m_gfxLight);
  }
}


void LightState::RemoveFromScene(World* world)
{
  if (m_gfxLight && world)
  {
    world->GetScene()->Remove(m_gfxLight);
  }

  CE_RELEASE(m_light);
  CE_RELEASE(m_gfxLight);
  m_gfxLight = nullptr;
  m_light = nullptr;
  m_pointLight = nullptr;
  m_directionalLight = nullptr;
}

void LightState::SetColor(const Color4f& color)
{
  m_color = color;
  UpdateValues();
}

const Color4f& LightState::GetColor() const
{
  return m_color;
}

void LightState::SetCastShadow(bool castShadow)
{
  m_castShadow = castShadow;
  UpdateValues();
}

bool LightState::IsCastShadow() const
{
  return m_castShadow;
}

void LightState::SetShadowMapBias(float bias)
{
  m_shadowBias = bias;
  UpdateValues();
}

float LightState::GetShadowMapBias() const
{
  return m_shadowBias;
}

void LightState::SetRange(float range)
{
  m_range = range;
  UpdateValues();
}

float LightState::GetRange() const
{
  return m_range;
}




}