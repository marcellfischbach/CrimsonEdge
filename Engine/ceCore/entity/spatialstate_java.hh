

#ifdef CE_JAVA

#include <jni.h>

namespace ce::java
{


extern "C"
{
  JNIEXPORT void JNICALL Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix2(JNIEnv* env, jclass cls, jlong refId, jfloatArray matrix);
}

}


#endif // CE_JAVA
