
#include <csCore/graphics/scene/csGfxOctreeScene.hh>


namespace cryo
{

csGfxOctreeScene::csGfxOctreeScene()
{

}

void csGfxOctreeScene::Add(csGfxCamera *camera)
{

}

void csGfxOctreeScene::Remove(csGfxCamera *camera)
{

}

void csGfxOctreeScene::Add(csGfxMesh *sceneMesh)
{

}

void csGfxOctreeScene::Remove(csGfxMesh *sceneMesh)
{

}

void csGfxOctreeScene::Add(csGfxLight *light)
{

}

void csGfxOctreeScene::Remove(csGfxLight *light)
{

}

const std::vector<csGfxCamera *> &csGfxOctreeScene::GetCameras() const
{
  return m_cameras;
}

void csGfxOctreeScene::ScanMeshes(const iClipper *clipper,
                                  uint32_t scanMask,
                                  const std::function<void(csGfxMesh *)> &callback
                                 ) const
{

}

void csGfxOctreeScene::ScanLights(const iClipper *clipper,
                                  uint32_t scanMask,
                                  const std::function<bool(csGfxLight *)> &callback
                                 ) const
{

}

void csGfxOctreeScene::ScanMeshes(const iClipper *clipper, csGfxSceneCollector &collector) const
{

}

void csGfxOctreeScene::ScanMeshes(const iClipper *clipper, uint32_t scanMask, csGfxSceneCollector &collector) const
{

}

}