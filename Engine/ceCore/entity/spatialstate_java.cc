
#include <ceCore/entity/spatialstate.hh>

#define CE_SPATIAL_STATE(ref) reinterpret_cast<ce::SpatialState*>(ref)

extern "C"
{


JNIEXPORT void
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nSetStatic(JNIEnv *env, jclass cls, jlong ref, jboolean _static)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  spatialState->SetStatic(_static);

}

JNIEXPORT jboolean
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nIsStatic(JNIEnv *env, jclass cls, jlong ref)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  return spatialState->IsStatic();
}

JNIEXPORT jboolean
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nAttach(JNIEnv *env, jclass cls, jlong ref, jlong childRef)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  auto child        = CE_SPATIAL_STATE(childRef);
  return spatialState->Attach(child);
}

JNIEXPORT jboolean
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nDetachSelf(JNIEnv *env, jclass cls, jlong ref)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  return spatialState->DetachSelf();
}

JNIEXPORT jboolean
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nDetach(JNIEnv *env, jclass cls, jlong ref, jlong childRef)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  auto child        = CE_SPATIAL_STATE(childRef);
  return spatialState->Detach(child);

}

JNIEXPORT jobject
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nGetParent(JNIEnv *env, jclass cls, jlong ref)
{
  auto             spatialState = CE_SPATIAL_STATE(ref);
  ce::SpatialState *pState      = spatialState->GetParent();
  return pState ? pState->CreateJObject() : nullptr;
}

JNIEXPORT jint
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nGetNumberOfChildren(JNIEnv *env, jclass cls, jlong ref)
{
  auto spatialState = CE_SPATIAL_STATE(ref);
  return spatialState->GetNumberOfChildren();
}

JNIEXPORT jobject
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nGetChild(JNIEnv *env, jclass cls, jlong ref, jint idx)
{
  auto             spatialState = CE_SPATIAL_STATE(ref);
  ce::SpatialState *pState      = spatialState->GetChild(idx);
  return pState ? pState->GetJObject() : nullptr;

}

JNIEXPORT void
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nGetGlobalMatrix(JNIEnv *env,
                                                                       jclass cls,
                                                                       jlong ref,
                                                                       jfloatArray mArray)
{
  jfloat *m = env->GetFloatArrayElements(mArray, 0);
  auto spatialState = CE_SPATIAL_STATE(ref);
  const ce::Matrix4f &f = spatialState->GetGlobalMatrix();
  memcpy (m, &f, sizeof(ce::Matrix4f));
  env->ReleaseFloatArrayElements(mArray, m, 0);
}


JNIEXPORT void
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nGetLocalMatrix(JNIEnv *env,
                                                                       jclass cls,
                                                                       jlong ref,
                                                                       jfloatArray mArray)
{
  jfloat *m = env->GetFloatArrayElements(mArray, 0);
  auto spatialState = CE_SPATIAL_STATE(ref);
  const ce::Matrix4f &f = spatialState->GetLocalMatrix();
  memcpy (m, &f, sizeof(ce::Matrix4f));
  env->ReleaseFloatArrayElements(mArray, m, 0);
}



JNIEXPORT void
JNICALL Java_org_crimsonedge_core_entity_SpatialState_nSetLocalMatrix(JNIEnv *env,
                                                                       jclass cls,
                                                                       jlong ref,
                                                                       jfloatArray mArray)
{
  jfloat *m = env->GetFloatArrayElements(mArray, 0);

  auto spatialState = CE_SPATIAL_STATE(ref);
  spatialState->SetLocalMatrix(*reinterpret_cast<const ce::Matrix4f *>(m));
  env->ReleaseFloatArrayElements(mArray, m, 0);
}

}