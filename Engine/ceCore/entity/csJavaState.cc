
#include <ceCore/entity/csJavaState.hh>
#include <ceCore/csJava.hh>
#include <ceCore/csJavaCalls.hh>
#include <ceCore/entity/csWorld.hh>

#define THIS_CLASS_NAME  "org/crimsonedge/core/entity/JavaState"

namespace cryo
{


csJavaState::csJavaState()
: csEntityState()
{
  SetNeedUpdate(true);
}

void csJavaState::OnAttachedToWorld(cryo::csWorld *world)
{
  static csJavaCallVoid1<jobject> onAttachedToWorld (csJava::Get(), this, THIS_CLASS_NAME, "onAttachedToWorld", "Lorg/crimsonedge/core/entity/World;");
  onAttachedToWorld.call(csJava::Get(), world->GetJObject());
}


void csJavaState::OnDetachedFromWorld(cryo::csWorld *world)
{
  static csJavaCallVoid1<jobject> onDetachedFromWorld (csJava::Get(), this, THIS_CLASS_NAME, "onDetachedFromWorld", "Lorg/crimsonedge/core/entity/World;");
  onDetachedFromWorld.call(csJava::Get(), world->GetJObject());
}


void csJavaState::Update(float tpf)
{
  static csJavaCallVoid1<jfloat> update (csJava::Get(), this, THIS_CLASS_NAME, "update", JAVA_FLOAT);
  update.call(csJava::Get(), tpf);
}

}