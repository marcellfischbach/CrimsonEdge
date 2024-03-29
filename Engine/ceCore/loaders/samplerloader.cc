

#include <ceCore/loaders/samplerloader.hh>
#include <ceCore/graphics/isampler.hh>
#include <ceCore/graphics/idevice.hh>
#include <ceCore/objectregistry.hh>


namespace ce
{

SamplerLoader::SamplerLoader()
: BaseCEFAssetLoader()
{
  AddValidFile(iSampler::GetStaticClass(), "SAMPLER");
}


#define IF(prefix, name, text) if (std::string(#name) == (text)) return prefix##name

eFilterMode FilterMode(const std::string& filterMode)
{
#define IF_(name) IF(eFM_, name, filterMode)
#define ELSE_IF_(name) else IF(eFM_, name, filterMode)
  IF_(MinMagNearest);
  ELSE_IF_(MinNearestMagLinear);
  ELSE_IF_(MinLinearMagNearest);
  ELSE_IF_(MinMagLinear);
  ELSE_IF_(MinMagMipNearest);
  ELSE_IF_(MinMagNearestMipLinear);
  ELSE_IF_(MinNearestMagLinearMipNearest);
  ELSE_IF_(MinNearestMagMipLinear);
  ELSE_IF_(MinLinearMagMipNearest);
  ELSE_IF_(MinLinearMagNearestMipLinear);
  ELSE_IF_(MinMagLinearMipNearest);
  ELSE_IF_(MinMagMipLinear);
  ELSE_IF_(Anisotropic);
#undef IF_
#undef ELSE_IF_
  return eFM_MinMagNearest;
}


eTextureAddressMode AddressMode(const std::string& addressMode)
{

#define IF_(name) IF(eTAM_, name, addressMode)
#define ELSE_IF_(name) else IF(eTAM_, name, addressMode)
  IF_(Repeat);
  ELSE_IF_(Clamp);
  ELSE_IF_(Mirror);
  ELSE_IF_(MirrorOnce);
#undef IF_
#undef ELSE_IF_
  return eTAM_Repeat;
}

eTextureCompareMode TextureCompareMode(const std::string& compareMode)
{

#define IF_(name) IF(eTCM_, name, compareMode)
#define ELSE_IF_(name) else IF(eTCM_, name, compareMode)
  IF_(CompareToR);
  ELSE_IF_(None);
#undef IF_
#undef ELSE_IF_
  return eTCM_None;
}

eCompareFunc CompareFunc(const std::string& compareFunc)
{

#define IF_(name) IF(eCF_, name, compareFunc)
#define ELSE_IF_(name) else IF(eCF_, name, compareFunc)
  IF_(Less);
  ELSE_IF_(LessOrEqual);
  ELSE_IF_(Greater);
  ELSE_IF_(GreaterOrEqual);
  ELSE_IF_(Equal);
  ELSE_IF_(NotEqual);
  ELSE_IF_(Always);
  ELSE_IF_(Never);
#undef IF_
#undef ELSE_IF_
  return eCF_Always;
}

iObject* SamplerLoader::Load(const CrimsonFile *file, const Class* cls, const ResourceLocator& locator) const
{
  const CrimsonFileElement* samplerElement = file->Root()->GetChild("sampler");
  if (!samplerElement)
  {
    return nullptr;
  }

  eFilterMode filter = FilterMode(samplerElement->GetAttribute("filter", ""));
  int anisotropy = samplerElement->GetAttribute("anisotropy", 1);
  int minLOD = samplerElement->GetAttribute("minLOD", -1000);
  int maxLOD = samplerElement->GetAttribute("maxLOD", 1000);
  eTextureAddressMode addressU = AddressMode(samplerElement->GetAttribute("addressU", ""));
  eTextureAddressMode addressV = AddressMode(samplerElement->GetAttribute("addressV", ""));
  eTextureAddressMode addressW = AddressMode(samplerElement->GetAttribute("addressW", ""));
  std::string borderColor = samplerElement->GetAttribute("borderColor", "#000000");
  eTextureCompareMode compareMode = TextureCompareMode(samplerElement->GetAttribute("textureCompareMode", ""));
  eCompareFunc compareFunc = CompareFunc(samplerElement->GetAttribute("textureCompareFunc", ""));


  iSampler* sampler = ObjectRegistry::Get<iDevice>()->CreateSampler();
  if (sampler)
  {
    sampler->SetFilterMode(filter);
    sampler->SetAnisotropy(anisotropy);
    sampler->SetMinLOD((int16_t)minLOD);
    sampler->SetMaxLOD((int16_t)maxLOD);
    sampler->SetAddressU(addressU);
    sampler->SetAddressV(addressV);
    sampler->SetAddressW(addressW);
    sampler->SetTextureCompareMode(compareMode);
    sampler->SetTextureCompareFunc(compareFunc);


  }
  


  return sampler;
}



}