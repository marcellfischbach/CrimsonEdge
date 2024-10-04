#pragma  once

#include <ceCore/csCoreExport.hh>
#include <ceCore/csClass.hh>
#include <ceCore/graphics/eTextureType.hh>

namespace cryo
{

struct iTexture;

CS_CLASS()
struct CS_CORE_API iRenderTarget : public CS_SUPER(iObject)
{
  CS_CLASS_GEN;
  ~iRenderTarget() override = default;

  virtual eTextureType GetType() const = 0;

  CS_NODISCARD virtual bool Compile() = 0;
  CS_NODISCARD virtual std::string GetCompileLog() const = 0;
};


}