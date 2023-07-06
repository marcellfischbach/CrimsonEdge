
#include <ceCore/entity/spatialstate_java.hh>
#include <ceCore/entity/spatialstate.hh>

#ifdef  CE_JAVA

namespace ce::java
{



void Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix2(JNIEnv* env, jclass cls, jlong refId, jfloatArray matrix)
{
  jfloat* buf = env->GetFloatArrayElements(matrix, 0);
  ce::iObject* obj = reinterpret_cast<ce::iObject*>(refId);

  ce::SpatialState* spatialState = obj->Query<ce::SpatialState>();
  ce::Matrix4f mat = ce::Matrix4f((const float*)buf);

  spatialState->SetLocalMatrix(mat);

  env->ReleaseFloatArrayElements(matrix, buf, 0);
}

}

#endif //  CE_JAVA


