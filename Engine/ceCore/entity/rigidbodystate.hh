
#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/entity/spatialstate.hh>

namespace ce
{
struct iCollisionShape;
struct iDynamicCollider;
struct iPhysicsSystem;
struct iPhysicsWorld;

CE_CLASS()
class CE_CORE_API RigidBodyState : public CE_SUPER(SpatialState)
{
  CE_CLASS_GEN;

public:
  RigidBodyState(const std::string &name = std::string(""));
  ~RigidBodyState() override;

protected:
  void OnAttachedToWorld(World * world) override;
  void OnDetachedFromWorld(World * world) override;

  void TransformationUpdatedPreChildren() override;


private:
  void AcquireEmptyDynamicCollider(iPhysicsSystem *physSystem);
  void DetachCurrentShapes();

  iDynamicCollider *m_dynamicCollider;
  std::vector<iCollisionShape*> m_shapes;
};

}