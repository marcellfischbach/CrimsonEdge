
#pragma once


#ifdef CE_JAVA

#include <ceCore/coreexport.hh>
#include <jni.h>


namespace ce::java
{

CE_CORE_API bool initialize_java_vm();
CE_CORE_API void initialize_java_env(JNIEnv *env);
CE_CORE_API void initialize_java_bindings();

}

#endif