
#pragma  once


#include <csCore/csCoreExport.hh>
#include <csCore/entity/csSpatialState.hh>
#include <csCore/graphics/eLightType.hh>
#include <csCore/math/csColor4f.hh>
#include <csCore/math/csVector3f.hh>

namespace cryo
{

struct iLight;
struct iPointLight;
struct iDirectionalLight;
class csGfxLight;
class csWorld;

CS_CLASS()
class CS_CORE_API csLightState : public CS_SUPER(csSpatialState)
{
  CS_CLASS_GEN_OBJECT;

public:
  csLightState(const std::string &name);
  ~csLightState() override;

  void SetType(eLightType type);
  CS_NODISCARD eLightType GetType() const;

  void SetCastShadow(bool castShadow);
  CS_NODISCARD bool IsCastShadow() const;

  void SetShadowMapBias(float bias);
  CS_NODISCARD float GetShadowMapBias() const;

  void SetColor(const csColor4f &color);
  CS_NODISCARD const csColor4f &GetColor() const;

  void SetRange(float range);
  CS_NODISCARD float GetRange() const;


  void OnAttachedToWorld(csWorld * world) override;
  void OnDetachedFromWorld(csWorld * world) override;

protected:
  void TransformationUpdatedPreChildren() override;

private:
  iLight *CreateLight();
  void AddToScene(csWorld *world);
  void RemoveFromScene(csWorld * world);

  void UpdateValues();


  iLight* m_light;
  iPointLight* m_pointLight;
  iDirectionalLight* m_directionalLight;

  csGfxLight *m_gfxLight;

  eLightType m_lightType;

  bool m_castShadow;
  float     m_shadowBias;
  csColor4f m_color;
  float     m_range;
};

}

