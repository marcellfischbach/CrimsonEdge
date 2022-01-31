#pragma once

#include <spcCore/coreexport.hh>
#include <spcCore/class.hh>
#include <spcCore/defs.hh>
#include <functional>

namespace spc
{

class GfxCamera;
class GfxMesh;
class GfxLight;
struct iClipper;

SPC_CLASS()
struct SPC_CORE_API iGfxScene : public SPC_SUPER(iObject)
{
  SPC_CLASS_GEN;


  enum eScanMask
  {
    eSM_Global = 1,
    eSM_Static = 2,
    eSM_Dynamic = 4,
    eSM_Unshaded = 8,
  };


  ~iGfxScene() override = default;


  virtual void Add(GfxCamera *camera) = 0;
  virtual void Remove(GfxCamera *camera) = 0;
  virtual void Add(GfxMesh * sceneMesh) = 0;
  virtual void Remove(GfxMesh * sceneMesh) = 0;
  virtual void Add(GfxLight* light) = 0;
  virtual void Remove(GfxLight* light) = 0;

  SPC_NODISCARD virtual const std::vector<GfxCamera*> &GetCameras () const = 0;


  virtual void ScanMeshes(const iClipper* clipper, uint32_t scanMask, const std::function<void(GfxMesh*)> &callback) const = 0;
  virtual void ScanLights(const iClipper* clipper, uint32_t scanMask, const std::function<bool(GfxLight*)> &callback) const = 0;

};


}