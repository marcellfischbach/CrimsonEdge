
#pragma once

#include <ceAssimpLoader/assimpexport.hh>
#include <ceCore/resource/iassetloader.hh>
#include <ceCore/math/matrix4f.hh>

struct aiMesh;
struct aiNode;
struct aiMaterial;

namespace ce
{
struct iMaterial;
}

namespace ce::assimp
{

struct StaticLoaderData;

CE_CLASS()
class CE_ASSIMP_API AssimpMeshLoader : public CE_SUPER(iAssetLoader)
{
  CE_CLASS_GEN_OBJECT;
public:
  AssimpMeshLoader();
  virtual ~AssimpMeshLoader() { }

  virtual bool CanLoad(const Class * cls, const ResourceLocator & locator) const;

  virtual iObject* Load(const Class * cls, const ResourceLocator & locator) const;

private:
  void ReadNode(aiNode* node, const Matrix4f &parentMatrix, StaticLoaderData& d) const;

};


}