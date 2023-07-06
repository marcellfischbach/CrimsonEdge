
#ifdef CE_JAVA


#include <ceCore/coremodule_java.hh>

#include <ceCore/entity/jentitystate.hh>
#include <ceCore/entity/entitystate.hh>
#include <ceCore/entity/spatialstate_java.hh>

#include <ceCore/coremodule_java_bindings.hh>


namespace ce::java
{

JNINativeMethod create_method(const char* name, const char* signature, void* fnPtr)
{
  JNINativeMethod method;
  memset(&method, 0, sizeof(method));
  method.name = _strdup(name);
  method.signature = _strdup(signature);
  method.fnPtr = fnPtr;
  return method;
}


void register_java_assetmanager()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/resource/AssetManager");
  if (cls)
  {
    JNINativeMethod methods[] = {
        create_method("nGet",
                      "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;",
                      (void*)&Java_org_crimsonedge_core_resource_AssetManager_nGet),
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));
    printf("register_java_assetmanager: %d\n", res);

  }
}



void register_java_jentity_state()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/JEntityState");
  if (cls)
  {
    JNINativeMethod methods[] = {
        create_method("nCreateJEntity",
                      "(Lorg/crimsonedge/core/entity/JEntityState;)J",
                      (void*)&Java_org_crimsonedge_core_entity_JEntityState_createJEntity),
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));
    printf("register_java_jentity_state: %d\n", res);
  }
}

void register_java_entity()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/Entity");
  if (cls)
  {

    JNINativeMethod methods[] = {
        create_method("nNew",
                      "(Ljava/lang/String;)Ljava/lang/Object;",
                      (void*)&Java_org_crimsonedge_core_entity_Entity_nNew),
        create_method("nSetName",
                      "(JLjava/lang/String;)V",
                      (void*)&Java_org_crimsonedge_core_entity_Entity_nSetName),
        create_method("nGetName",
                      "(J)Ljava/lang/String;",
                      (void*)&Java_org_crimsonedge_core_entity_Entity_nGetName),
        create_method("nAttach",
                      "(JJJ)Z",
                      (void*)&Java_org_crimsonedge_core_entity_Entity_nAttach),
        create_method("nDetach",
                      "(JJ)Z",
                      (void*)&Java_org_crimsonedge_core_entity_Entity_nDetach)
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));
    printf("register_java_entity: %d\n", res);
  }
}

void register_java_entity_state()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/EntityState");
  if (cls)
  {

    JNINativeMethod methods[] = {
        create_method("nGetRoot",
                      "(J)Lorg/crimsonedge/core/entity/SpatialState;",
                      (void*)&Java_org_crimsonedge_core_entity_EntityState_nGetRoot),
        create_method("nGetName",
                      "(J)Ljava/lang/String;",
                      (void*)&Java_org_crimsonedge_core_entity_EntityState_nGetName),
        create_method("nSetName",
                      "(JLjava/lang/String;)V",
                      (void*)&Java_org_crimsonedge_core_entity_EntityState_nSetName),
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));
    printf("register_java_entity_state: %d\n", res);
  }
}


void register_java_spatial_state()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/SpatialState");
  if (cls)
  {
    JNINativeMethod methods[] = {
        create_method("nSetLocalMatrix",
                      "(J[F)V",
                      (void*)&Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix),
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));

    printf("register_java_spatial_state: %d\n", res);
  }
}
void register_java_world()
{
  JNIEnv* jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/World");
  if (cls)
  {

    JNINativeMethod methods[] = {
        create_method("nAttach",
                      "(JJ)V",
                      (void*)&Java_org_crimsonedge_core_entity_World_nAttach),
        create_method("nDetach",
                      "(JJ)V",
                      (void*)&Java_org_crimsonedge_core_entity_World_nDetach),
    };
    jint res = jniEnv->RegisterNatives(cls, methods, sizeof(methods) / sizeof(JNINativeMethod));
    printf("register_java_world: %d\n", res);
  }
}



bool initialize_java_vm()
{
  return java::Env::Initialize();
}

void initialize_java_env(JNIEnv* env)
{
  java::Env::Set(env);
}


void initialize_java_bindings()
{
  register_java_assetmanager();
  register_java_jentity_state();
  register_java_entity();
  register_java_entity_state();
  register_java_spatial_state();
  register_java_world();
}



}


#endif