
#pragma once

#include <ceAssimpLoader/assimpexport.hh>

namespace ce::assimp
{

class CE_ASSIMP_API AssimpLoaderModule
{
public:
  static bool Register(int argc, char** argv);
  static bool Initialize(int argc, char** argv);

private:
  AssimpLoaderModule() { }
};

}