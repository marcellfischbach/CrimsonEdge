

#pragma once

#ifdef CE_JAVA



#include <ceCore/coreexport.hh>
#include <ceCore/entity/entitystate.hh>


namespace ce
{


CE_CLASS()
class CE_CORE_API JEntityState : public CE_SUPER(EntityState)
{
  CE_CLASS_GEN;
public:
  JEntityState(const std::string & name = std::string(""));
  virtual ~JEntityState();

public:
  virtual void Update(float tpf) override;

  virtual void SetJObject(jobject obj) override;


private:
  jclass m_clsJEntityState;

  jmethodID m_mthdUpdate;

};

}

extern "C"
{

  JNIEXPORT jlong JNICALL  Java_org_crimsonedge_core_entity_JEntityState_createJEntity
  (JNIEnv*, jclass, jobject);

}

#endif // CE_JAVA
