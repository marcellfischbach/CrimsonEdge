#include <ceCore/coremodule.hh>
#include <master.refl.cc>
#include <ceCore/objectregistry.hh>
#include <ceCore/graphics/defaultframerenderer.hh>
#include <ceCore/resource/assetmanager.hh>
#include <ceCore/loaders/materialloader.hh>
#include <ceCore/loaders/samplerloader.hh>
#include <ceCore/loaders/terrainlayerloader.hh>
#include <ceCore/loaders/textureloader.hh>
#include <cstring>

#ifdef CE_JAVA

#include <ceCore/cejava.hh>

#endif

namespace ce
{

bool CoreModule::Register(int argc, char **argv)
{
  register_classes();

  ObjectRegistry::Register<iFrameRenderer>(new DefaultFrameRenderer);
  AssetManager::Set(new AssetManager());
  AssetManager *assetMan = AssetManager::Get();
  assetMan->RegisterLoader(new SamplerLoader());
  assetMan->RegisterLoader(new MaterialLoader());
  assetMan->RegisterLoader(new TerrainLayerLoader());
  assetMan->RegisterLoader(new TerrainLayerMaskLoader());
  assetMan->RegisterLoader(new TextureLoader());

  return true;
}

#ifdef CE_JAVA
void initialize_java_methods ();
#endif

bool CoreModule::Initialize(int argc, char **argv)
{
#ifdef CE_JAVA
  bool javaInitialized = java::Env::Initialize();
  if (!javaInitialized)
  {
    return false;
  }

  initialize_java_methods();
#endif
  return true;
}

#ifdef CE_JAVA
JNINativeMethod create_method(const char *name, const char *signature, void *fnPtr)
{
  JNINativeMethod method;
  memset(&method, 0, sizeof(method));
  method.name = _strdup(name);
  method.signature = _strdup(signature);
  method.fnPtr = fnPtr;
  return method;
}

#include <ceCore/entity/jentitystate.hh>
void register_java_jentity_state()
{
  JNIEnv *jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/JEntityState");
  if (cls)
  {
    auto methods = new JNINativeMethod[]{
        create_method("nCreateEntity",
                      "(Lorg/crimsonedge/core/entity/JEntityState;)J",
                      (void *) &Java_org_crimsonedge_core_entity_JEntityState_createJEntity),
    };
    jniEnv->RegisterNatives(cls, methods, 1);
  }
}

#include <ceCore/entity/entitystate.hh>

void register_java_entity_state()
{
  JNIEnv *jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/EntityState");
  if (cls)
  {
    auto methods = new JNINativeMethod[]{
        create_method("nGetRoot",
                      "(J)Lorg/crimsonedge/core/entity/SpatialState;",
                      (void *) &Java_org_crimsonedge_core_entity_JEntityState_createJEntity),
    };
    jniEnv->RegisterNatives(cls, methods, 1);
  }
}


#include <ceCore/entity/spatialstate.hh>

void register_java_spatial_state()
{
  JNIEnv *jniEnv = java::Env::Get();
  jclass cls = jniEnv->FindClass("org/crimsonedge/core/entity/SpatialState");
  if (cls)
  {
    auto methods = new JNINativeMethod[]{
        create_method("nSetLocalMatrix",
                      "(J[F)V",
                      (void *) &Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix),
    };
    jniEnv->RegisterNatives(cls, methods, 1);
  }
}


void initialize_java_methods ()
{
  register_java_jentity_state();
  register_java_entity_state();
  register_java_spatial_state();
}
#endif

}
