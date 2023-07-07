
#ifdef CE_JAVA

#include <ceCore/resource/assetmanager.hh>
#include <ceCore/coremodule_java_bindings.hh>
#include <ceCore/entity/entity.hh>
#include <ceCore/entity/spatialstate.hh>
#include <ceCore/entity/staticmeshstate.hh>
#include <ceCore/entity/jentitystate.hh>
#include <ceCore/entity/world.hh>
#include <ceCore/graphics/mesh.hh>

#include <ceCore/classregistry.hh>





jobject Java_org_crimsonedge_core_resource_AssetManager_nGet(JNIEnv* env, jclass cls, jstring ceClass, jstring jlocator)
{
  const char* cstrClass = env->GetStringUTFChars(ceClass, 0);
  const ce::Class* ceCls = ce::ClassRegistry::Get()->GetClass(cstrClass);
  env->ReleaseStringUTFChars(ceClass, cstrClass);
  if (!ceCls)
  {
    return nullptr;
  }

  const char* cstrLocator = env->GetStringUTFChars(jlocator, 0);

  ce::iObject* object = ce::AssetManager::Get()->Get(ceCls, ce::ResourceLocator(cstrLocator));

  env->ReleaseStringUTFChars(jlocator, cstrLocator);


  return object
    ? object->GetJObject()
    : nullptr;
}

jobject  Java_org_crimsonedge_core_CoreObject_nNew(JNIEnv* env, jclass, jstring ceClass)
{
  const char* cstrClass = env->GetStringUTFChars(ceClass, 0);
  const ce::Class* ceCls = ce::ClassRegistry::Get()->GetClass(cstrClass);
  env->ReleaseStringUTFChars(ceClass, cstrClass);
  if (!ceCls)
  {
    return nullptr;
  }

  ce::iObject* object = ceCls->CreateInstance();

  if (!object)
  {
    return nullptr;
  }

  return object->GetJObject();
}

void  Java_org_crimsonedge_core_entity_Entity_nSetName(JNIEnv* env, jclass, jlong ref, jstring name)
{
  auto* entity = reinterpret_cast<ce::Entity*>(ref);

  const char *cstrName = env->GetStringUTFChars(name, 0);
  if (entity && cstrName)
  {
    entity->SetName(cstrName);
  }
  env->ReleaseStringUTFChars(name, cstrName);
}

jstring  Java_org_crimsonedge_core_entity_Entity_nGetName(JNIEnv* env, jclass, jlong ref)
{
  auto* entity = reinterpret_cast<ce::Entity*>(ref);
  if (entity)
  {
    return env->NewStringUTF(entity->GetName().c_str());
  }
  return nullptr;
}

jboolean  Java_org_crimsonedge_core_entity_Entity_nAttach(JNIEnv* env, jclass, jlong thisRef, jlong entityRef, jlong parentStateRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  auto* entity = reinterpret_cast<ce::Entity*>(entityRef);
  auto* parentSpatialState = reinterpret_cast<ce::SpatialState*>(parentStateRef);
  return thisEntity->Attach(entity, parentSpatialState);

}

jboolean  Java_org_crimsonedge_core_entity_Entity_nDetach(JNIEnv* env, jclass, jlong thisRef, jlong entityRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  auto* entity = reinterpret_cast<ce::Entity*>(entityRef);
  return thisEntity->Detach(entity);
}


jboolean  Java_org_crimsonedge_core_entity_Entity_nAttachState(JNIEnv* env, jclass, jlong thisRef, jlong entityStateRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  auto* entityState = reinterpret_cast<ce::EntityState*>(entityStateRef);
  if (thisEntity && entityState)
  {
    return thisEntity->Attach(entityState);
  }
  return false;
}

jboolean  Java_org_crimsonedge_core_entity_Entity_nDetachState(JNIEnv* env, jclass, jlong thisRef, jlong entityStateRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  auto* entityState = reinterpret_cast<ce::EntityState*>(entityStateRef);
  if (thisEntity && entityState)
  {
    return thisEntity->Detach(entityState);
  }
  return false;
}

void Java_org_crimsonedge_core_entity_Entity_nSetRoot(JNIEnv* env, jclass, jlong thisRef, jlong spatialStateRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  auto* spatialState = reinterpret_cast<ce::SpatialState*>(spatialStateRef);
  if (thisEntity && spatialState)
  {
    thisEntity->SetRoot(spatialState);
  }
}

jobject Java_org_crimsonedge_core_entity_Entity_nGetRoot(JNIEnv* env, jclass, jlong thisRef)
{
  auto* thisEntity = reinterpret_cast<ce::Entity*>(thisRef);
  if (!thisEntity)
  {
    return nullptr;
  }
  auto* root = thisEntity->GetRoot();
  if (!root)
  {
    return nullptr;
  }
  return root->GetJObject();
}


jobject Java_org_crimsonedge_core_entity_EntityState_nGetRoot(JNIEnv*, jclass, jlong ref)
{
  auto* entityState = reinterpret_cast<ce::EntityState*>(ref);
  if (!entityState)
  {
    return nullptr;
  }

  ce::SpatialState* root = entityState->GetRoot();
  if (!root)
  {
    return nullptr;
  }

  return root->GetJObject();
}


void  Java_org_crimsonedge_core_entity_EntityState_nSetName(JNIEnv* env, jclass, jlong ref, jstring name)
{
  auto* entity = reinterpret_cast<ce::EntityState*>(ref);

  const char *cstrName = env->GetStringUTFChars(name, 0);
  if (entity && cstrName)
  {
    entity->SetName(cstrName);
  }
  env->ReleaseStringUTFChars(name, cstrName);
}

jstring  Java_org_crimsonedge_core_entity_EntityState_nGetName(JNIEnv* env, jclass, jlong ref)
{
  auto* entity = reinterpret_cast<ce::EntityState*>(ref);
  if (entity)
  {
    return env->NewStringUTF(entity->GetName().c_str());
  }
  return nullptr;
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

void  Java_org_crimsonedge_core_entity_StaticMeshState_nSetMesh(JNIEnv* env, jclass, jlong ref, jlong meshRef)
{
  auto* staticMeshState = reinterpret_cast<ce::StaticMeshState*>(ref);
  auto* mesh = reinterpret_cast<ce::Mesh*>(meshRef);

  if (staticMeshState && mesh)
  {
    staticMeshState->SetMesh(mesh);
  }
}

jobject  Java_org_crimsonedge_core_entity_StaticMeshState_nGetMesh(JNIEnv* env, jclass, jlong ref)
{
  auto* staticMeshState = reinterpret_cast<ce::StaticMeshState*>(ref);
  if (!staticMeshState)
  {
    return nullptr;
  }


  auto *mesh = staticMeshState->GetMesh();
  if (!mesh)
  {
    return nullptr;
  }

  return mesh->GetJObject();
}


void  Java_org_crimsonedge_core_entity_World_nAttach(JNIEnv*, jclass, jlong worldRef, jlong entityRef)
{
  auto* world = reinterpret_cast<ce::World*>(worldRef);
  auto* entity = reinterpret_cast<ce::Entity*>(entityRef);

  if (world && entity)
  {
    world->Attach(entity);
  }
}

void  Java_org_crimsonedge_core_entity_World_nDetach(JNIEnv*, jclass, jlong worldRef, jlong entityRef)
{
  auto* world = reinterpret_cast<ce::World*>(worldRef);
  auto* entity = reinterpret_cast<ce::Entity*>(entityRef);

  if (world && entity)
  {
    world->Detach(entity);
  }
}


#endif