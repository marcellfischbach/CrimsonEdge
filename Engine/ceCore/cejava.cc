
#include <ceCore/cejava.hh>
#include <string>
#include <cstring>


namespace ce::java
{
#ifdef CE_JAVA

JNIEnv *Env::s_env = nullptr;

Env::Env()
{

}


JNIEnv *Env::Get()
{
  return s_env;
}

bool Env::Initialize()
{
  JavaVM *jvm;
  JNIEnv *jniEnv;

  JavaVMInitArgs args;
  memset(&args, 0, sizeof(JavaVMInitArgs));
  JavaVMOption *options = new JavaVMOption[1];
  options[0].optionString = strdup(
      "-Djava.class.path=D:/DEV/CrimsonEdge/Java/CrimsonEdge/target/crimson3d-1.0-SNAPSHOT.jar");
  args.version = JNI_VERSION_19;
  args.nOptions = 1;
  args.options = options;
  args.ignoreUnrecognized = false;
  printf ("Start JVM\n");
  jint res = JNI_CreateJavaVM(&jvm, (void **) &jniEnv, &args);
  if (res != JNI_OK)
  {
    printf("Unable to create java vm");
    return false;
  }
  printf ("Start JVM - done\n");

  s_env = jniEnv;

  return true;
}


#endif

}