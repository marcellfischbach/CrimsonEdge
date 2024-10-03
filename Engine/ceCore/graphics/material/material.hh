

#pragma once


#include <ceCore/coreexport.hh>
#include <ceCore/class.hh>
#include <ceCore/types.hh>
#include <ceCore/graphics/eblendfactor.hh>
#include <ceCore/graphics/edepthmode.hh>
#include <ceCore/graphics/erenderpass.hh>
#include <ceCore/graphics/eshadingmode.hh>
#include <ceCore/graphics/idevice.hh>
#include <ceCore/graphics/itexture.hh>
#include <ceCore/graphics/material/ematerialattributetype.hh>
#include <ceCore/graphics/material/imaterial.hh>
#include <ceCore/math/color4f.hh>
#include <ceCore/math/matrix.hh>
#include <ceCore/math/vector.hh>
#include <string>
#include <array>

namespace cryo
{

struct iShader;
struct iShaderAttribute;
struct iTexture;


CS_CLASS(jclass="org.crimsonedge.core.graphics.material.Material")
class CS_CORE_API Material : public CS_SUPER(iMaterial)
{
  friend class MaterialInstance;
  CS_CLASS_GEN_OBJECT;
public:
  static const Size UndefinedIndex = ~0x00;

  Material();
  ~Material() override;

  bool Bind(iDevice * device, eRenderPass pass) override;

  void SetFillMode (eFillMode fillMode);
  CS_NODISCARD eFillMode GetFillMode () const override;

  void SetRenderQueue(eRenderQueue queue);
  CS_NODISCARD eRenderQueue GetRenderQueue() const override;

  void SetBlending(bool  blending);
  CS_NODISCARD bool IsBlending () const;
  void SetBlendFactor (eBlendFactor srcFactor, eBlendFactor dstFactor);
  void SetBlendFactor (eBlendFactor srcFactorColor, eBlendFactor srcFactorAlpha, eBlendFactor dstFactorColor, eBlendFactor dstFactorAlpha);
  CS_NODISCARD eBlendFactor GetBlendFactorSrcColor () const;
  CS_NODISCARD eBlendFactor GetBlendFactorSrcAlpha () const;
  CS_NODISCARD eBlendFactor GetBlendFactorDstColor () const;
  CS_NODISCARD eBlendFactor GetBlendFactorDstAlpha () const;

  void SetDepthWrite (bool depthWrite);
  CS_NODISCARD bool IsDepthWrite() const;
  void SetDepthTest (bool depthTest);
  CS_NODISCARD bool IsDepthTest() const;
  void SetDepthFunc (eCompareFunc depthFun);
  CS_NODISCARD eCompareFunc GetDepthFunc() const;
  void SetShadingMode (eShadingMode shadingMode);
  CS_NODISCARD eShadingMode GetShadingMode () const override;


  void SetShader(eRenderPass pass, iShader * shader);
  CS_NODISCARD iShader* GetShader(eRenderPass pass);
  CS_NODISCARD const iShader* GetShader(eRenderPass pass) const override;

  void RegisterAttribute(const std::string & attributeName, eMaterialAttributeType attributeType);
  CS_NODISCARD uint16_t GetNumberOfAttributes() const;

  CS_NODISCARD std::vector<std::string> GetAttributeNames() const;

  Size IndexOf(const std::string & attributeName) override;
  void Debug(Size idx) override;

  void Set(Size idx, float value) override;
  void Set(Size idx, const Vector2f & v) override;
  void Set(Size idx, const Vector3f & v) override;
  void Set(Size idx, const Vector4f & v) override;
  void Set(Size idx, const Color4f & v) override;
  void Set(Size idx, int value) override;
  void Set(Size idx, const Matrix3f & m) override;
  void Set(Size idx, const Matrix4f & m) override;
  void Set(Size idx, iTexture * texture) override;


private:
  bool BindShader(iDevice * device, eRenderPass pass) const;
  void BindBlending(iDevice *device) const;
  void BindDepthMode(iDevice *device) const;
  void BindFillMode (iDevice *device) const;
  bool BindAttribute(iDevice * device, eRenderPass pass, size_t idx) const;
  bool BindAttribute(iDevice * device, eRenderPass pass, size_t idx, const std::array<float, 16> &floats, const std::array<int, 4> &ints, iTexture * texture) const;
  static bool BindTexture (iDevice *device, iShaderAttribute *attribute, iTexture *texture);
  void UpdateShaderAttributes(eRenderPass pass);

  struct Attribute
  {
    std::array<iShaderAttribute*, eRP_COUNT> Attributes;
    std::string Name;
    eMaterialAttributeType Type;
    std::array<float, 16> Floats;
    std::array<int, 4> Ints;
    iTexture* Texture;
  };


  std::array<iShader*, eRP_COUNT> m_shader;
  std::vector<Attribute> m_attributes;

  eFillMode m_fillMode = eFillMode::Fill;
  eRenderQueue m_queue = eRenderQueue::Default;

  bool  m_blending = false;
  eBlendFactor m_srcFactorColor = eBlendFactor::One;
  eBlendFactor m_srcFactorAlpha = eBlendFactor::One;
  eBlendFactor m_dstFactorColor = eBlendFactor::Zero;
  eBlendFactor m_dstFactorAlpha = eBlendFactor::Zero;

  bool m_depthWrite = true;
  bool m_depthTest  = true;
  eCompareFunc m_depthFunc = eCF_Less;

  eShadingMode m_shadingMode = eShadingMode::Shaded;
};


}