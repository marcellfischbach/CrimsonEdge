
#pragma once


#ifdef CE_JAVA

#include <jni.h>
#include <ceCore/coreexport.hh>


namespace ce::java
{

class CE_CORE_API Env
{
public:
  static JNIEnv* Get();
  static void Set(JNIEnv* env);

private:
  Env();

  static JNIEnv* s_env;
};

}

#endif // CE_JAVA
