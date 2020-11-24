
#pragma once

#include <spcCore/coreexport.hh>
#include <spcCore/class.hh>
#include <spcCore/types.hh>
#include <spcCore/resource/resourcelocator.hh>

namespace spc
{

const Int16 DefaultPriority = 0;

SPC_CLASS()
struct SPC_CORE_API iAssetLoader : public iObject
{
  SPC_CLASS_GEN;
  virtual ~iAssetLoader()
  {

  }

  virtual Int16 Priority() const
  {
    return DefaultPriority;
  }

  virtual bool CanLoad(const ResourceLocator& locator) const = 0;

  virtual iObject* Load(const ResourceLocator& locator) const = 0;

};

}