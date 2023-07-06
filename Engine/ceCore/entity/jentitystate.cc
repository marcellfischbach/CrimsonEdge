
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

void JEntityState::SetJObject(jobject obj)
{
  EntityState::SetJObject(obj);
  JNIEnv *env = ce::java::Env::Get();
  m_clsJEntityState = env->FindClass("org/crimsonedge/core/entity/JEntityState");
  if (!m_clsJEntityState)
  {
    return;
  }

  m_mthdUpdate = env->GetMethodID(m_clsJEntityState, "update", "(F)V");
  if (!m_mthdUpdate)
  {
    return;
  }
}


void JEntityState::Update(float tpf)
{
  JNIEnv* env = java::Env::Get();
  if (env && m_jobject && m_mthdUpdate)
  {
    env->CallVoidMethod(m_jobject, m_mthdUpdate, tpf);
  }
}





}


#endif