
#pragma once

#include <ceBullet/bulletexport.hh>
#include <ceCore/physics/icollider.hh>
#include <set>
#include <btBulletDynamicsCommon.h>

class btRigidBody;
class btCompoundShape;

namespace cryo::bullet
{

class BulletCollisionShape;
class BulletWorld;

CS_CLASS()
class BulletDynamicCollider : public CS_SUPER(iDynamicCollider)
{
  CS_CLASS_GEN_OBJECT;
public:
  BulletDynamicCollider();
  ~BulletDynamicCollider() override;

  void Attach(iCollisionShape * shape) override;
  void Detach(iCollisionShape * shape) override;

  void SetTransform(const Matrix4f & transform) override;
  const Matrix4f &GetTransform() const override;


  void SetUserData(csSpatialState * spatialState) override;
  csSpatialState* GetUserData() const override;

  btRigidBody* GetRigidBody();

  void SetWorld(BulletWorld * world);

private:

  btRigidBody* m_rigidBody;

  btCompoundShape* m_compoundShape;
  std::set<BulletCollisionShape*> m_shapes;

  struct MotionState : public btMotionState
  {
    BulletDynamicCollider* priv;
    void getWorldTransform(btTransform& worldTrans) const override;

    void setWorldTransform(const btTransform& worldTrans) override;
  } m_motionState;

  Matrix4f m_transform;


  BulletWorld* m_world;

  csSpatialState * m_userData;
};


}
