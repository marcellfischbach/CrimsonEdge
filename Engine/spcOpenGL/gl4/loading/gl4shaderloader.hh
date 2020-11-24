 
#pragma once

#include <spcOpenGL/openglexport.hh>
#include <spcCore/resource/iassetloader.hh>

namespace spc
{

SPC_CLASS()
class GL4ShaderLoader : public SPC_SUPER(iAssetLoader)
{
  SPC_CLASS_GEN_OBJECT;
public:
  GL4ShaderLoader();
  virtual ~GL4ShaderLoader()
  {

  }

  virtual bool CanLoad(const ResourceLocator& locator) const;

  virtual iObject* Load(const ResourceLocator& locator) const;
};



}