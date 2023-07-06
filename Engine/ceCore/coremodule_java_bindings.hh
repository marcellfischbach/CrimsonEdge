
#include <jni.h>



extern "C"
{



  JNIEXPORT jobject JNICALL Java_org_crimsonedge_core_resource_AssetManager_nGet(JNIEnv* env, jclass cls, jstring ceClass, jstring locator);


  JNIEXPORT jlong JNICALL  Java_org_crimsonedge_core_entity_JEntityState_createJEntity(JNIEnv*, jclass, jobject);

  JNIEXPORT void JNICALL Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix(JNIEnv* env, jclass cls, jlong refId, jfloatArray matrix);





}
