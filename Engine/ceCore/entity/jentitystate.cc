
#include <ceCore/entity/jentitystate.hh>

#ifdef CE_JAVA


namespace ce
{

JEntityState::JEntityState(const std::string& name)
  : EntityState(name)
  , m_clsJEntityState(nullptr)
  , m_mthdUpdate(nullptr)
{
  SetNeedUpdate(true);

}

JEntityState::~JEntityState()
{

}

void JEntityState::SetJObject(JNIEnv* env, jobject obj)
{
  EntityState::SetJObject(env, obj);
  m_clsJEntityState = m_jenv->FindClass("org/crimsonedge/core/entity/JEntityState");
  if (!m_clsJEntityState)
  {
    return;
  }

  m_mthdUpdate = m_jenv->GetMethodID(m_clsJEntityState, "update", "(F)V");
  if (!m_mthdUpdate)
  {
    return;
  }
}


void JEntityState::Update(float tpf)
{
  if (m_jenv && m_jobject && m_mthdUpdate)
  {
    m_jenv->CallVoidMethod(m_jobject, m_mthdUpdate, tpf);
  }
}





}

jlong Java_org_crimsonedge_core_entity_JEntityState_createJEntity(JNIEnv* env, jclass, jobject entityState)
{
  printf("Java_org_crimsonedge_core_entity_JEntityState_createJEntity\n");
  ce::JEntityState* jes = new ce::JEntityState("");
  jes->SetJObject(env, entityState);

  jlong lng = reinterpret_cast<jlong>(jes);
  printf("Java_org_crimsonedge_core_entity_JEntityState_createJEntity 0x%08x\n", lng);

  return lng;
}


#endif