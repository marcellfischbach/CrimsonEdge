#pragma  once

#include <ceCore/coreexport.hh>
#include <ceCore/class.hh>
#include <ceCore/resource/ifile.hh>

namespace cryo
{

class ResourceLocator;

CS_CLASS()
struct CS_CORE_API iArchive : public CS_SUPER(iObject)
{
  CS_CLASS_GEN;
  ~iArchive() override = default;

  CS_NODISCARD virtual const std::string &GetName () const = 0;
  CS_NODISCARD virtual int GetPriority () const = 0;
  CS_NODISCARD virtual iFile* Open (const std::string &locator, eAccessMode accessMode, eOpenMode openMode) = 0;
};


}