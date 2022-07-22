
#include <ceCore/loaders/materialloader.hh>
#include <ceCore/graphics/material/material.hh>
#include <ceCore/graphics/material/materialinstance.hh>
#include <ceCore/graphics/shading/ishader.hh>
#include <ceCore/resource/assetmanager.hh>

namespace ce
{

#define IF(prefix, name, text) if (std::string(#name) == (text)) return prefix##name
#define IF_CLASS(prefix, name, text) if (std::string(#name) == (text)) return prefix::name

bool MaterialLoaderCEF::CanLoad(const Class* cls, const CrimsonFile* file, const ResourceLocator* locator) const
{
  if (file->Root()->GetNumberOfChildren() == 0)
  {
    return false;
  }
  std::string root = file->Root()->GetChild(0)->GetTagName();
  return
    cls->IsAssignableFrom<Material>() && root == std::string("material")
      || cls->IsAssignableFrom<MaterialInstance>() && root == std::string("materialinstance")
      || cls->IsAssignableFrom<iMaterial>() && (
        root == std::string("material")
          || root == std::string("materialinstance")
      );

}

iObject* MaterialLoaderCEF::Load(const Class* cls, const CrimsonFile* file, const ResourceLocator* locator) const
{
  if ((cls->IsAssignableFrom<Material>() || cls->IsAssignableFrom<iMaterial>()) && file->Root()->HasChild("material"))
  {
    return LoadMaterial(cls, file, locator);
  }
  else if ((cls->IsAssignableFrom<MaterialInstance>() || cls->IsAssignableFrom<iMaterial>())
    && file->Root()->HasChild("materialinstance"))
  {
    return LoadMaterialInstance(cls, file, locator);
  }
  return nullptr;
}

Material* MaterialLoaderCEF::LoadMaterial(const Class*, const CrimsonFile* file, const ResourceLocator* locator)
{
  const CrimsonFileElement* root            = file->Root();
  const CrimsonFileElement* materialElement = root->GetChild("material");
  if (!materialElement)
  {
    return nullptr;
  }

  auto material = new Material();

  LoadShading(material, materialElement, locator);
  LoadQueue(material, materialElement, locator);
  LoadBlending(material, materialElement, locator);
  LoadDepth(material, materialElement, locator);

  if (!LoadShaders(material, materialElement, locator))
  {
    CE_RELEASE(material);
    return nullptr;
  }

  if (!LoadAttributes(material, materialElement, locator))
  {
    CE_RELEASE(material);
    return nullptr;
  }


  return material;
}

iObject* MaterialLoaderCEF::LoadMaterialInstance(const Class*, const CrimsonFile* file, const ResourceLocator* locator)
{

  const CrimsonFileElement* root            = file->Root();
  const CrimsonFileElement* materialElement = root->GetChild("materialinstance");
  if (!materialElement)
  {
    return nullptr;
  }

  auto materialInstance = new MaterialInstance();

  if (!LoadReferenceMaterial(materialInstance, materialElement, locator))
  {
    CE_RELEASE(materialInstance);
    return nullptr;
  }

  if (!LoadAttributes(materialInstance, materialElement, locator))
  {
    CE_RELEASE(materialInstance);
    return nullptr;
  }


  return materialInstance;
}
void MaterialLoaderCEF::LoadShading(Material* material,
                                    const CrimsonFileElement* materialElement,
                                    const ResourceLocator* locator)
{
  const CrimsonFileElement* shadingElement = materialElement->GetChild("shading");
  if (!shadingElement)
  {
    return;
  }

  eShadingMode shading     = eShadingMode::Shaded;
  auto         queueString = shadingElement->GetAttribute(0, "Shaded");
  if (queueString == std::string("Unshaded"))
  {
    shading = eShadingMode::Unshaded;
  }

  material->SetShadingMode(shading);
}

void MaterialLoaderCEF::LoadQueue(Material* material,
                                  const CrimsonFileElement* materialElement,
                                  const ResourceLocator* locator)
{
  const CrimsonFileElement* queueElement = materialElement->GetChild("queue");
  if (!queueElement)
  {
    return;
  }

  eRenderQueue queue       = eRenderQueue::Default;
  auto         queueString = queueElement->GetAttribute(0, "Default");
  if (queueString == std::string("Transparency"))
  {
    queue = eRenderQueue::Transparency;
  }

  material->SetRenderQueue(queue);
}

eBlendFactor BlendFactor(const std::string& blendFactor, eBlendFactor defaultFactor)
{
#define IF_(name) IF_CLASS(eBlendFactor, name, blendFactor)
#define ELSE_IF_(name) else IF_CLASS(eBlendFactor, name, blendFactor)
  if (std::string("One") == blendFactor) return eBlendFactor::One;
  IF_(One);
  ELSE_IF_(Zero);
  ELSE_IF_(SrcColor);
  ELSE_IF_(SrcAlpha);
  ELSE_IF_(DstColor);
  ELSE_IF_(DstAlpha);
  ELSE_IF_(OneMinusSrcColor);
  ELSE_IF_(OneMinusSrcAlpha);
  ELSE_IF_(OneMinusDstColor);
  ELSE_IF_(OneMinusDstAlpha);
#undef IF_
#undef ELSE_IF_
  return defaultFactor;
}

void MaterialLoaderCEF::LoadBlending(Material* material,
                                     const CrimsonFileElement* materialElement,
                                     const ResourceLocator* locator)
{
  auto         blendElement = materialElement->GetChild("blend");
  bool         blending     = false;
  eBlendFactor srcColor     = eBlendFactor::One;
  eBlendFactor srcAlpha     = eBlendFactor::One;
  eBlendFactor dstColor     = eBlendFactor::Zero;
  eBlendFactor dstAlpha     = eBlendFactor::Zero;

  if (blendElement)
  {
    if (blendElement->GetNumberOfAttributes() == 2)
    {
      blending = true;
      srcColor = BlendFactor(blendElement->GetAttribute(0, "One"), eBlendFactor::One);
      srcAlpha = srcColor;
      dstColor = BlendFactor(blendElement->GetAttribute(1, "Zero"), eBlendFactor::Zero);
      dstAlpha = dstColor;
    }
    else if (blendElement->GetNumberOfAttributes() == 4)
    {
      blending = true;
      srcColor = BlendFactor(blendElement->GetAttribute(0, "One"), eBlendFactor::One);
      srcAlpha = BlendFactor(blendElement->GetAttribute(1, "One"), eBlendFactor::One);
      dstColor = BlendFactor(blendElement->GetAttribute(2, "Zero"), eBlendFactor::Zero);
      dstAlpha = BlendFactor(blendElement->GetAttribute(3, "Zero"), eBlendFactor::Zero);
    }
  }

  material->SetBlending(blending);
  material->SetBlendFactor(srcColor, srcAlpha, dstColor, dstAlpha);
}

void MaterialLoaderCEF::LoadDepth(Material* material,
                                  const CrimsonFileElement* materialElement,
                                  const ResourceLocator* locator)
{
  auto* depthElement = materialElement->GetChild("depth");
  if (!depthElement)
  {
    return;
  }
  bool     depthTest  = false;
  bool     depthWrite = false;
  for (int i          = 0; i < depthElement->GetNumberOfAttributes(); ++i)
  {
    std::string depthValue = depthElement->GetAttribute(i, std::string());
    if (std::string("Test") == depthValue)
    {
      depthTest = true;
    }
    else if (std::string("Write") == depthValue)
    {
      depthWrite = true;
    }
  }
  material->SetDepthTest(depthTest);
  material->SetDepthWrite(depthWrite);
}

bool MaterialLoaderCEF::LoadShaders(Material* material,
                                    const CrimsonFileElement* materialElement,
                                    const ResourceLocator* locator)
{
  const CrimsonFileElement* shadersElement = materialElement->GetChild("shaders");
  if (!shadersElement)
  {
    return false;
  }

  for (size_t i = 0; i < shadersElement->GetNumberOfChildren(); ++i)
  {
    const CrimsonFileElement* shaderElement = shadersElement->GetChild(i);
    if (shaderElement && shaderElement->GetTagName() == std::string("shader"))
    {
      if (!LoadShader(material, shaderElement, locator))
      {
        return false;
      }
    }
  }
  return true;
}

eRenderPass RenderPass(const std::string& renderPass)
{
#define IF_(name) IF(eRP_, name, renderPass)
#define ELSE_IF_(name) else IF(eRP_, name, renderPass)
  IF_(Depth);
  ELSE_IF_(GBuffer);
  ELSE_IF_(Forward);
  ELSE_IF_(Shadow);
  ELSE_IF_(ShadowPSSM);
  ELSE_IF_(ShadowCube);
#undef IF_
#undef ELSE_IF_
  return eRP_COUNT;
}

bool MaterialLoaderCEF::LoadShader(Material* material,
                                   const CrimsonFileElement* shaderElement,
                                   const ResourceLocator* locator)
{
  if (shaderElement->GetNumberOfAttributes() != 2)
  {
    return false;
  }

  std::string rp        = shaderElement->GetAttribute(0, std::string(""));
  std::string shaderLoc = shaderElement->GetAttribute(1, std::string(""));

  if (rp.empty() || shaderLoc.empty())
  {
    return false;
  }

  eRenderPass renderPass = RenderPass(rp);
  if (renderPass == eRP_COUNT)
  {
    return false;
  }

  ResourceLocator shaderLocator(locator, shaderLoc);
  auto            shader = AssetManager::Get()->Get<iShader>(shaderLocator);
  if (!shader)
  {
    return false;
  }


  material->SetShader(renderPass, shader);

  return true;
}

bool MaterialLoaderCEF::LoadAttributes(Material* material,
                                       const CrimsonFileElement* materialElement,
                                       const ResourceLocator* locator)
{
  const CrimsonFileElement* attributesElement = materialElement->GetChild("attributes");
  if (!attributesElement)
  {
    return true;
  }

  for (size_t i = 0; i < attributesElement->GetNumberOfChildren(); ++i)
  {
    const CrimsonFileElement* attributeElement = attributesElement->GetChild(i);
    if (attributeElement && attributeElement->GetTagName() == std::string("attribute"))
    {
      if (!LoadAttribute(material, attributeElement, locator))
      {
        return false;
      }
    }
  }
  return true;
}

bool MaterialLoaderCEF::LoadAttribute(Material* material,
                                      const CrimsonFileElement* attributeElement,
                                      const ResourceLocator* locator)
{
  if (attributeElement->GetNumberOfAttributes() < 2)
  {
    return false;
  }

  eMaterialAttributeType attributeType = GetAttributeType(attributeElement);
  if (attributeType == eMAT_Undefined)
  {
    return false;
  }

  std::string name = attributeElement->GetAttribute(1, "");
  if (name.empty())
  {
    return false;
  }


  material->RegisterAttribute(name, attributeType);
  size_t idx = material->IndexOf(name);

  if (!LoadAttributeDefault(material, idx, attributeType, attributeElement, locator))
  {
    return false;
  }


  return true;
}

bool MaterialLoaderCEF::LoadReferenceMaterial(MaterialInstance* materialInstance,
                                              const CrimsonFileElement* materialInstanceElement,
                                              const ResourceLocator* locator)
{
  const CrimsonFileElement* materialElement = materialInstanceElement->GetChild("material");
  if (!materialElement)
  {
    return false;
  }

  if (materialElement->GetNumberOfAttributes() < 1)
  {
    return false;
  }

  ResourceLocator materialLocator(locator, materialElement->GetAttribute(0, ""));
  auto            material = AssetManager::Get()->Get<Material>(materialLocator);
  if (!material)
  {
    return false;
  }

  materialInstance->SetMaterial(material);
  return true;
}

bool MaterialLoaderCEF::LoadAttributes(MaterialInstance* materialInstance,
                                       const CrimsonFileElement* materialInstanceElement,
                                       const ResourceLocator* locator)
{
  const CrimsonFileElement* attributesElement = materialInstanceElement->GetChild("attributes");
  if (!attributesElement)
  {
    return true;
  }

  for (size_t i = 0; i < attributesElement->GetNumberOfChildren(); ++i)
  {
    const CrimsonFileElement* attributeElement = attributesElement->GetChild(i);
    if (attributeElement && attributeElement->GetTagName() == std::string("attribute"))
    {
      if (!LoadAttribute(materialInstance, attributeElement, locator))
      {
        return false;
      }
    }
  }
  return true;
}

bool MaterialLoaderCEF::LoadAttribute(MaterialInstance* materialInstance,
                                      const CrimsonFileElement* attributeElement,
                                      const ResourceLocator* locator)
{
  if (attributeElement->GetNumberOfAttributes() < 2)
  {
    return false;
  }

  eMaterialAttributeType attributeType = GetAttributeType(attributeElement);
  if (attributeType == eMAT_Undefined)
  {
    return false;
  }

  std::string name = attributeElement->GetAttribute(1, "");
  if (name.empty())
  {
    return false;
  }


  size_t idx = materialInstance->IndexOf(name);
  if (idx == Material::UndefinedIndex)
  {
    return false;
  }

  if (!LoadAttributeDefault(materialInstance, idx, attributeType, attributeElement, locator))
  {
    return false;
  }


  return true;
}

eMaterialAttributeType MaterialLoaderCEF::GetAttributeType(const CrimsonFileElement* attributeElement)
{
  std::string type = attributeElement->GetAttribute(0, "");
  if (type == "Float")
  {
    return eMAT_Float;
  }
  else if (type == "Vec2")
  {
    return eMAT_Vec2;
  }
  else if (type == "Vec3")
  {
    return eMAT_Vec3;
  }
  else if (type == "Vec4")
  {
    return eMAT_Vec4;
  }
  else if (type == "Color4")
  {
    return eMAT_Vec4;
  }
  else if (type == "Int")
  {
    return eMAT_Int;
  }
  else if (type == "Matrix3")
  {
    return eMAT_Matrix3;
  }
  else if (type == "Matrix4")
  {
    return eMAT_Matrix4;
  }
  else if (type == "Texture")
  {
    return eMAT_Texture;
  }
  return eMAT_Undefined;
}

bool MaterialLoaderCEF::LoadAttributeDefault(iMaterial* material,
                                             size_t attributeIdx,
                                             eMaterialAttributeType attributeType,
                                             const CrimsonFileElement* attributeElement,
                                             const ResourceLocator* locator)
{
  switch (attributeType)
  {
  case eMAT_Float:
    return LoadAttributeFloat(material, attributeIdx, attributeElement);
  case eMAT_Vec2:
    return LoadAttributeVec2(material, attributeIdx, attributeElement);
  case eMAT_Vec3:
    return LoadAttributeVec3(material, attributeIdx, attributeElement);
  case eMAT_Vec4:
    return LoadAttributeVec4(material, attributeIdx, attributeElement);
  case eMAT_Int:
    return LoadAttributeInt(material, attributeIdx, attributeElement);

  case eMAT_Matrix3:
    return LoadAttributeMatrix3(material, attributeIdx, attributeElement);
  case eMAT_Matrix4:
    return LoadAttributeMatrix4(material, attributeIdx, attributeElement);

  case eMAT_Texture:
    return LoadAttributeTexture(material, attributeIdx, attributeElement, locator);
  default:
    break;
  }
  return false;
}

bool MaterialLoaderCEF::LoadAttributeFloat(iMaterial* material,
                                           size_t attributeIdx,
                                           const CrimsonFileElement* attributeElement)
{
  if (attributeElement->GetNumberOfAttributes() < 3)
  {
    return false;
  }

  auto v0 = (float)attributeElement->GetAttribute(2, 0.0);
  material->Set(attributeIdx, (float)v0);
  return true;
}

bool MaterialLoaderCEF::LoadAttributeVec2(iMaterial* material,
                                          size_t attributeIdx,
                                          const CrimsonFileElement* attributeElement)
{
  if (attributeElement->GetNumberOfAttributes() < 4)
  {
    return false;
  }

  auto v0 = (float)attributeElement->GetAttribute(2, 0.0);
  auto v1 = (float)attributeElement->GetAttribute(3, 0.0);
  material->Set(attributeIdx, Vector2f(v0, v1));
  return true;
}

bool MaterialLoaderCEF::LoadAttributeVec3(iMaterial* material,
                                          size_t attributeIdx,
                                          const CrimsonFileElement* attributeElement)
{
  if (attributeElement->GetNumberOfAttributes() < 5)
  {
    return false;
  }

  auto v0 = (float)attributeElement->GetAttribute(2, 0.0);
  auto v1 = (float)attributeElement->GetAttribute(3, 0.0);
  auto v2 = (float)attributeElement->GetAttribute(4, 0.0);
  material->Set(attributeIdx, Vector3f(v0, v1, v2));
  return true;
}

bool MaterialLoaderCEF::LoadAttributeVec4(iMaterial* material,
                                          size_t attributeIdx,
                                          const CrimsonFileElement* attributeElement)
{
  if (attributeElement->GetNumberOfAttributes() < 6)
  {
    return false;
  }

  auto v0 = (float)attributeElement->GetAttribute(2, 0.0);
  auto v1 = (float)attributeElement->GetAttribute(3, 0.0);
  auto v2 = (float)attributeElement->GetAttribute(4, 0.0);
  auto v3 = (float)attributeElement->GetAttribute(5, 0.0);
  material->Set(attributeIdx, Vector4f(v0, v1, v2, v3));
  return true;
}

bool MaterialLoaderCEF::LoadAttributeInt(iMaterial* material,
                                         size_t attributeIdx,
                                         const CrimsonFileElement* attributeElement)
{
  if (attributeElement->GetNumberOfAttributes() < 3)
  {
    return false;
  }

  int v0 = attributeElement->GetAttribute(2, 0);
  material->Set(attributeIdx, v0);
  return true;
}

bool MaterialLoaderCEF::LoadAttributeMatrix3(iMaterial* material,
                                             size_t attributeIdx,
                                             const CrimsonFileElement* attributeElement)
{
  if (!attributeElement->HasAttribute("m00")
    || !attributeElement->HasAttribute("m01")
    || !attributeElement->HasAttribute("m02")
    || !attributeElement->HasAttribute("m10")
    || !attributeElement->HasAttribute("m11")
    || !attributeElement->HasAttribute("m12")
    || !attributeElement->HasAttribute("m20")
    || !attributeElement->HasAttribute("m21")
    || !attributeElement->HasAttribute("m22")
    )
  {
    return false;
  }

  auto m00 = (float)attributeElement->GetAttribute("m00", 1.0);
  auto m01 = (float)attributeElement->GetAttribute("m01", 0.0);
  auto m02 = (float)attributeElement->GetAttribute("m02", 0.0);
  auto m10 = (float)attributeElement->GetAttribute("m10", 0.0);
  auto m11 = (float)attributeElement->GetAttribute("m11", 1.0);
  auto m12 = (float)attributeElement->GetAttribute("m12", 0.0);
  auto m20 = (float)attributeElement->GetAttribute("m20", 0.0);
  auto m21 = (float)attributeElement->GetAttribute("m21", 0.0);
  auto m22 = (float)attributeElement->GetAttribute("m22", 1.0);
  material->Set(attributeIdx, Matrix3f(
    m00, m01, m02,
    m10, m11, m12,
    m20, m21, m22
  ));
  return true;
}

bool MaterialLoaderCEF::LoadAttributeMatrix4(iMaterial* material,
                                             size_t attributeIdx,
                                             const CrimsonFileElement* attributeElement)
{
  if (!attributeElement->HasAttribute("m00")
    || !attributeElement->HasAttribute("m01")
    || !attributeElement->HasAttribute("m02")
    || !attributeElement->HasAttribute("m03")
    || !attributeElement->HasAttribute("m10")
    || !attributeElement->HasAttribute("m11")
    || !attributeElement->HasAttribute("m12")
    || !attributeElement->HasAttribute("m13")
    || !attributeElement->HasAttribute("m20")
    || !attributeElement->HasAttribute("m21")
    || !attributeElement->HasAttribute("m22")
    || !attributeElement->HasAttribute("m23")
    || !attributeElement->HasAttribute("m30")
    || !attributeElement->HasAttribute("m31")
    || !attributeElement->HasAttribute("m32")
    || !attributeElement->HasAttribute("m33")
    )
  {
    return false;
  }

  float m00 = (float)attributeElement->GetAttribute("m00", 1.0);
  float m01 = (float)attributeElement->GetAttribute("m01", 0.0);
  float m02 = (float)attributeElement->GetAttribute("m02", 0.0);
  float m03 = (float)attributeElement->GetAttribute("m03", 0.0);
  float m10 = (float)attributeElement->GetAttribute("m10", 0.0);
  float m11 = (float)attributeElement->GetAttribute("m11", 1.0);
  float m12 = (float)attributeElement->GetAttribute("m12", 0.0);
  float m13 = (float)attributeElement->GetAttribute("m13", 0.0);
  float m20 = (float)attributeElement->GetAttribute("m20", 0.0);
  float m21 = (float)attributeElement->GetAttribute("m21", 0.0);
  float m22 = (float)attributeElement->GetAttribute("m22", 1.0);
  float m23 = (float)attributeElement->GetAttribute("m23", 0.0);
  float m30 = (float)attributeElement->GetAttribute("m30", 0.0);
  float m31 = (float)attributeElement->GetAttribute("m31", 0.0);
  float m32 = (float)attributeElement->GetAttribute("m32", 0.0);
  float m33 = (float)attributeElement->GetAttribute("m33", 1.0);
  material->Set(attributeIdx, Matrix4f(
    m00, m01, m02, m03,
    m10, m11, m12, m13,
    m20, m21, m22, m23,
    m30, m31, m32, m33
  ));
  return true;
}

bool MaterialLoaderCEF::LoadAttributeTexture(iMaterial* material,
                                             size_t attributeIdx,
                                             const CrimsonFileElement* attributeElement,
                                             const ResourceLocator* locator)
{
  if (attributeElement->GetNumberOfAttributes() < 3)
  {
    material->Set(attributeIdx, nullptr);
    return true;
  }

  std::string textureLoc = attributeElement->GetAttribute(2, "");
  if (textureLoc.empty())
  {
    material->Set(attributeIdx, nullptr);
    return true;
  }

  auto texture = AssetManager::Get()->Get<iTexture>(ResourceLocator(locator, textureLoc));
  if (!texture)
  {
    return false;
  }

  material->Set(attributeIdx, texture);
  return true;
}

}