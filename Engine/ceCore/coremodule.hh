#ifndef COREMODULE_HH
#define COREMODULE_HH

#include <ceCore/coreexport.hh>
#include <cecore/imodule.hh>

namespace ce
{
class CE_CORE_API CoreModule : public iModule
{
public:
  bool Register(const std::vector<std::string> &args, Engine *engine);
  bool Initialize(const std::vector<std::string> &args, Engine *engine);
};

}

CE_DECLARE_LIBRARY(ceCore);


#endif // COREMODULE_HH
