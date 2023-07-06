
#ifdef CE_JAVA

#include <ceCore/resource/assetmanager.hh>
#include <ceCore/coremodule_java_bindings.hh>
#include <ceCore/entity/spatialstate.hh>
#include <ceCore/entity/jentitystate.hh>
#include <ceCore/classregistry.hh>





jobject Java_org_crimsonedge_core_resource_AssetManager_nGet(JNIEnv* env, jclass cls, jstring ceClass, jstring jlocator)
{
  const char* cstrLocator = env->GetStringUTFChars(jlocator, 0);
  const char* cstrClass = env->GetStringUTFChars(ceClass, 0);

  const ce::Class* ceCls = ce::ClassRegistry::Get()->GetClass(cstrClass);
  if (!cls)
  {
    return nullptr;
  }


  ce::iObject* object = ce::AssetManager::Get()->Get(ceCls, ce::ResourceLocator(cstrLocator));

  env->ReleaseStringUTFChars(jlocator, cstrLocator);
  env->ReleaseStringUTFChars(ceClass, cstrClass);


  return object
    ? object->GetJObject()
    : nullptr;
}



jlong Java_org_crimsonedge_core_entity_JEntityState_createJEntity(JNIEnv* env, jclass, jobject entityState)
{
  ce::JEntityState* jes = new ce::JEntityState("");
  jes->SetJObject(entityState);

  ce::iObject* iObj = jes->Query<ce::iObject>();
  return reinterpret_cast<jlong>(iObj);
}



void Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix(JNIEnv* env, jclass cls, jlong refId, jfloatArray matrix)
{
  jfloat* buf = env->GetFloatArrayElements(matrix, 0);
  ce::iObject* obj = reinterpret_cast<ce::iObject*>(refId);

  ce::SpatialState* spatialState = obj->Query<ce::SpatialState>();
  ce::Matrix4f mat = ce::Matrix4f((const float*)buf);

  spatialState->SetLocalMatrix(mat);

  env->ReleaseFloatArrayElements(matrix, buf, 0);
}


#endif