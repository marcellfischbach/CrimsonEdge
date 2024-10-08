
#include <csImgLoader/csImgLoaderModule.hh>
#include <master.refl.cc>
#include <csImgLoader/csJpegLoader.hh>
#include <csImgLoader/csPngLoader.hh>

#include <csCore/csObjectRegistry.hh>
#include <csCore/resource/csAssetManager.hh>
#include <csCore/graphics/csImage.hh>

namespace cryo::img
{

bool csImgLoaderModule::Register(const std::vector<std::string> &args, csEngine *engine)
{
  register_classes();

  csAssetManager::Get()->RegisterLoader(new csJpegLoader());
  csAssetManager::Get()->RegisterLoader(new csPngLoader());


  return true;
}

bool csImgLoaderModule::Initialize(const std::vector<std::string> &args, csEngine *engine)
{
  return true;
}


}

CS_DEFINE_LIBRARY(csImgLoader)
{
  printf ("Load library: ceImgLoader\n");
  return new cryo::img::csImgLoaderModule;
}