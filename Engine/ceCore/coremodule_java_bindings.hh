
#include <jni.h>


extern "C"
{


JNIEXPORT jobject JNICALL Java_org_crimsonedge_core_resource_AssetManager_nGet(JNIEnv *, jclass, jstring, jstring);


JNIEXPORT jobject JNICALL  Java_org_crimsonedge_core_entity_Entity_nNew(JNIEnv *, jclass, jstring);
JNIEXPORT void JNICALL  Java_org_crimsonedge_core_entity_Entity_nSetName(JNIEnv *, jclass, jlong, jstring);
JNIEXPORT jstring JNICALL  Java_org_crimsonedge_core_entity_Entity_nGetName(JNIEnv *, jclass, jlong);
JNIEXPORT jboolean  JNICALL Java_org_crimsonedge_core_entity_Entity_nAttach(JNIEnv*, jclass, jlong, jlong, jlong);
JNIEXPORT jboolean  JNICALL Java_org_crimsonedge_core_entity_Entity_nDetach(JNIEnv*, jclass, jlong, jlong);


JNIEXPORT jobject JNICALL  Java_org_crimsonedge_core_entity_EntityState_nGetRoot(JNIEnv*, jclass, jlong);
JNIEXPORT void JNICALL  Java_org_crimsonedge_core_entity_EntityState_nSetName(JNIEnv *, jclass, jlong, jstring);
JNIEXPORT jstring JNICALL  Java_org_crimsonedge_core_entity_EntityState_nGetName(JNIEnv *, jclass, jlong);

JNIEXPORT jlong JNICALL  Java_org_crimsonedge_core_entity_JEntityState_createJEntity(JNIEnv *, jclass, jobject);

JNIEXPORT void JNICALL  Java_org_crimsonedge_core_entity_World_nAttach(JNIEnv *, jclass, jlong, jlong);
JNIEXPORT void JNICALL  Java_org_crimsonedge_core_entity_World_nDetach(JNIEnv *, jclass, jlong, jlong);

JNIEXPORT void JNICALL Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix(JNIEnv *, jclass, jlong, jfloatArray);


}
