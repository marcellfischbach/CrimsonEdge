
#include <ceBullet/bulletmodule.hh>
#include <ceBullet/bulletsystem.hh>
#include <master.refl.cc>
#include <ceCore/objectregistry.hh>



namespace ce::bullet
{

bool BulletModule::Register(int argc, char** argv, Engine* engine)
{
  register_classes();


  ObjectRegistry::Register<iPhysicsSystem>(new BulletSystem());

  return true;
}

bool BulletModule::Initialize(int argc, char** argv, Engine* engine)
{
  return true;
}


}

CE_DEFINE_LIBRARY(ceBullet)
{
  return new ce::bullet::BulletModule;
}