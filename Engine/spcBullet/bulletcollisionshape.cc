
#include <spcBullet/bulletcollisionshape.hh>


namespace spc::bullet
{



BulletCollisionShape::BulletCollisionShape(btCollisionShape* shape)
  : iCollisionShape()
  , m_shape(shape)
{

}


BulletCollisionShape::~BulletCollisionShape()
{
  delete m_shape;
}

btCollisionShape* BulletCollisionShape::GetShape()
{
  return m_shape;
}

const btCollisionShape* BulletCollisionShape::GetShape() const
{
  return m_shape;
}


}